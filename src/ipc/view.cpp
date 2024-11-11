#pragma once

#define _IPC_VIEW_CPP

#ifndef _IPC_VIEW_H
#include "ipc/view.h"
#endif
#include "support/log.h"

#include <cassert>

namespace IPC {
	template<typename T>
	VecView<T>::VecView() :
		VecBase(InvalidVector, nullptr, 0, 0, 0, 0, 0),
		m_nextWindowIndex(0),
		m_currentWindow(0),
		m_currentWindowIndex(0),
		m_index(0),
		m_subIndex(0),
		m_buffer(nullptr)
	{

	}

	template<typename T>
	VecView<T>::VecView(VecId id, VecShare* shared, std::uint32_t windowElements, std::uint32_t windowBytes, std::uint32_t maxElements, std::uint32_t reservedBytes, std::uint32_t headerBytes) :
		VecBase(id, shared, windowElements, windowBytes, maxElements, reservedBytes, headerBytes),
		m_nextWindowIndex(windowElements),
		m_currentWindow(0),
		m_currentWindowIndex(0),
		m_index(0),
		m_subIndex(0),
		m_buffer(nullptr)
	{
		InterlockedIncrement(&m_shared->users);
	}

	template<typename T>
	VecView<T>::VecView(const VecView<T>& other) :
		VecBase(other.m_id, other.m_shared, other.m_windowSize, other.m_windowBytes, other.m_maxSize, other.m_reservedBytes, other.m_headerBytes),
		m_currentWindow(other.m_currentWindow),
		m_nextWindowIndex(other.m_nextWindowIndex),
		m_currentWindowIndex(other.m_currentWindowIndex),
		m_index(other.m_index),
		m_subIndex(other.m_subIndex),
		m_buffer(nullptr)
	{
		InterlockedIncrement(&m_shared->users);

		init();
	}

	template<typename T>
	VecView<T>::VecView(VecView<T>&& other) noexcept :
		VecBase(other.m_id, other.m_shared, other.m_windowSize, other.m_windowBytes, other.m_maxSize, other.m_reservedBytes, other.m_headerBytes),
		m_currentWindow(other.m_currentWindow),
		m_currentWindowIndex(other.m_currentWindowIndex),
		m_nextWindowIndex(other.m_nextWindowIndex),
		m_index(other.m_index),
		m_subIndex(other.m_subIndex),
		m_buffer(other.m_buffer)
	{
		other.m_buffer = nullptr;
		other.m_shared = nullptr;
	}

	template<typename T>
	VecView<T>& VecView<T>::operator=(const VecView<T>& other) {
		// if we're being assigned to ourselves, do nothing
		if (this == &other) {
			return *this;
		}

		// if we're being assigned a different view of the same
		// vec, take the fast path
		if (m_shared == other.m_shared) {
			m_index = other.m_index;
			m_subIndex = other.m_subIndex;
			m_currentWindowIndex = other.m_currentWindowIndex;
			m_nextWindowIndex = other.m_nextWindowIndex;
			slide_window(other.m_currentWindow);
			return *this;
		}

		// we're being assigned a view of a different vec, so free
		// all our old stuff first
		if (m_buffer != nullptr) {
			UnmapViewOfFile(m_buffer);
			VirtualFree(m_buffer, 0, MEM_RELEASE);
			m_buffer = nullptr;
		}

		if (m_shared != nullptr) {
			InterlockedDecrement(&m_shared->users);
		}

		m_id = other.m_id;
		m_shared = other.m_shared;
		m_index = other.m_index;
		m_subIndex = other.m_subIndex;
		m_nextWindowIndex = other.m_nextWindowIndex;
		m_currentWindowIndex = other.m_currentWindowIndex;
		m_currentWindow = other.m_currentWindow;
		m_windowBytes = other.m_windowBytes;
		m_windowSize = other.m_windowSize;
		m_maxSize = other.m_maxSize;
		m_reservedBytes = other.m_reservedBytes;
		m_headerBytes = other.m_headerBytes;
		// only one view should be writing at a time
		m_writing = false;

		InterlockedIncrement(&m_shared->users);

		init();

		return *this;
	}

	template<typename T>
	bool VecView<T>::init() {
		assert(m_id != InvalidVector);

		// the compiler complains about converting a 32-bit value to a HANDLE on the 64-bit side, but this code is only used on the 32-bit side
#ifndef MGE64_HOST
		m_buffer = static_cast<T*>(VirtualAlloc2(NULL, NULL, m_windowBytes, MEM_RESERVE | MEM_RESERVE_PLACEHOLDER, PAGE_NOACCESS, NULL, 0));
		if (m_buffer == nullptr) {
			LOG::winerror("View of vector %u failed to reserve %u bytes of placeholder memory", m_id, m_windowBytes);
			return false;
		}

		if (MapViewOfFile3(m_shared->sharedMem32, NULL, m_buffer, m_currentWindow * m_windowBytes + m_headerBytes, m_windowBytes, MEM_REPLACE_PLACEHOLDER, PAGE_READWRITE, NULL, 0) == NULL) {
			LOG::winerror("View of vector %u failed to map shared memory", m_id);
			VirtualFree(m_buffer, 0, MEM_RELEASE);
			m_buffer = nullptr;
			return false;
		}

		if (m_shared->committedBytes < m_windowBytes) {
			if (VirtualAlloc(m_buffer, m_windowBytes, MEM_COMMIT, PAGE_READWRITE) == NULL) {
				LOG::winerror("View of vector %u failed to commit from shared memory", m_id);
				UnmapViewOfFile(m_buffer);
				m_buffer = nullptr;
				return false;
			}

			m_shared->committedBytes = m_windowBytes;
		}
#endif

		return true;
	}

	template<typename T>
	bool VecView<T>::slide_window(std::uint32_t i, bool isAppend) {
		// the compiler complains about converting a 32-bit value to a HANDLE on the 64-bit side, but this code is only used on the 32-bit side
#ifndef MGE64_HOST
		if (i == m_currentWindow && m_shared->committedBytes > 0)
			return true;

		if (!UnmapViewOfFileEx(m_buffer, MEM_PRESERVE_PLACEHOLDER)) {
			LOG::winerror("View of vector %u failed to unmap shared memory back to placeholder", m_id);
			return false;
		}

		auto offset = i * m_windowBytes + m_headerBytes;
		auto newEnd = offset + m_windowBytes;
		// commit everything between the current end and the new end
		while (m_shared->committedBytes < newEnd) {
			auto nextOffset = static_cast<ULONG64>(m_shared->committedBytes + m_headerBytes);
			if (MapViewOfFile3(m_shared->sharedMem32, NULL, m_buffer, nextOffset, m_windowBytes, MEM_REPLACE_PLACEHOLDER, PAGE_READWRITE, NULL, 0) == NULL) {
				LOG::winerror("View of vector %u failed to map next window at offset %llu for commit (%u bytes reserved, index %u)", m_id, nextOffset, m_reservedBytes, i);
				m_buffer = nullptr;
				return false;
			}

			if (VirtualAlloc(m_buffer, m_windowBytes, MEM_COMMIT, PAGE_READWRITE) == NULL) {
				LOG::winerror("View of vector %u failed to commit %u bytes of shared memory at address %p", m_id, m_windowBytes, m_buffer);
				UnmapViewOfFile(m_buffer);
				m_buffer = nullptr;
				return false;
			}
			m_shared->committedBytes += m_windowBytes;
			UnmapViewOfFileEx(m_buffer, MEM_PRESERVE_PLACEHOLDER);
		}

		if (MapViewOfFile3(m_shared->sharedMem32, NULL, m_buffer, static_cast<ULONG64>(offset), m_windowBytes, MEM_REPLACE_PLACEHOLDER, PAGE_READWRITE, NULL, 0) == NULL) {
			LOG::winerror("View of vector %u failed to remap %u bytes of shared memory at offset %u", m_id, m_windowBytes, offset);
			m_buffer = nullptr;
			return false;
		}

		m_currentWindow = i;
		m_currentWindowIndex = m_currentWindow * m_windowSize;
		m_nextWindowIndex = m_currentWindowIndex + m_windowSize;

		if (m_writing && isAppend) {
			return update_write();
		}
#endif

		return true;
	}

	template<typename T>
	VecView<T>::~VecView() {
		if (m_shared != nullptr) {
			InterlockedDecrement(&m_shared->users);
			m_shared = nullptr;
		}

		if (m_buffer != nullptr) {
			UnmapViewOfFile(m_buffer);
			VirtualFree(m_buffer, 0, MEM_RELEASE);
			m_buffer = nullptr;
		}
	}

	template<typename T>
	T& VecView<T>::operator*() const {
		return m_buffer[m_subIndex];
	}

	template<typename T>
	T* VecView<T>::operator->() const {
		return &m_buffer[m_subIndex];
	}

	template<typename T>
	VecView<T>& VecView<T>::operator++() {
		m_index++;
		m_subIndex++;
		if (m_index >= m_shared->size) {
			wait_read();
		}

		if (m_index >= m_nextWindowIndex) {
			m_subIndex = 0;
			slide_window(m_currentWindow + 1);
		}

		return *this;
	}

	template<typename T>
	VecView<T> VecView<T>::operator++(int) {
		auto beforeIncrement = *this;
		++(*this);
		return beforeIncrement;
	}

	template<typename T>
	VecView<T>& VecView<T>::operator--() {
		m_index--;
		m_subIndex--;
		if (m_index < m_currentWindowIndex) {
			m_subIndex = m_windowSize - 1;
			slide_window(m_currentWindow - 1);
		}

		return *this;
	}

	template<typename T>
	VecView<T> VecView<T>::operator--(int) {
		auto beforeDecrement = *this;
		--(*this);
		return beforeDecrement;
	}

	template<typename T>
	bool VecView<T>::operator==(const VecView<T>& other) const {
		return m_shared == other.m_shared && m_index == other.m_index;
	}

	template<typename T>
	bool VecView<T>::operator!=(const VecView<T>& other) const {
		return m_shared != other.m_shared || m_index != other.m_index;
	}

	template<typename T>
	VecView<T> VecView<T>::begin() const {
		VecView it(*this);
		it.set_index(0);
		return it;
	}

	template<typename T>
	VecView<T> VecView<T>::end() const {
		VecView it(*this);
		// slight hack to point the view past the end
		it.m_index = m_shared->size;
		it.m_subIndex = it.m_index % m_windowSize;
		it.m_currentWindow = it.m_index / m_windowSize;
		it.m_currentWindowIndex = it.m_index - it.m_subIndex;
		it.m_nextWindowIndex = it.m_currentWindowIndex + m_windowSize;
		return it;
	}

	template<typename T>
	void VecView<T>::truncate(std::uint32_t numElements) {
		if (numElements < m_shared->size) {
			m_shared->size = numElements;
			if (m_index >= numElements) {
				set_index(numElements - 1);
			}
		}
	}

	template<typename T>
	bool VecView<T>::set_index(std::uint32_t i) {
		if (m_index == i)
			return true;

		if (i >= m_shared->size)
			return false;

		m_index = i;
		m_subIndex = i % m_windowSize;
		return slide_window(i / m_windowSize);
	}

	template<typename T>
	bool VecView<T>::at_end() {
		if (m_index >= m_shared->size) {
			wait_read();
		}
		return m_index >= m_shared->size;
	}

	template<typename T>
	bool VecView<T>::is_valid() const noexcept {
		return m_shared != nullptr && m_buffer != nullptr;
	}

	template<typename T>
	T& VecView<T>::operator[](std::uint32_t i) {
		set_index(i);
		return m_buffer[m_subIndex];
	}

	template<typename T>
	T& VecView<T>::front() {
		set_index(0);
		return *m_buffer;
	}

	template<typename T>
	T& VecView<T>::back() {
		return (*this)[m_shared->size - 1];
	}

	template<typename T>
	bool VecView<T>::push_back(const T& value) {
		auto newIndex = m_shared->size;
		auto window = newIndex / m_windowSize;
		m_subIndex = newIndex % m_windowSize;
		if (!slide_window(window, true))
			return false;

		m_buffer[m_subIndex] = value;
		m_index = m_shared->size++;
		return true;
	}

	template<typename T>
	std::optional<T> VecView<T>::pop_back() {
		if (m_shared->size == 0)
			return std::nullopt;

		m_index = --m_shared->size;
		return (*this)[m_index];
	}

	template<typename T>
	bool VecView<T>::reserve(std::uint32_t count) {
		auto windowsNeeded = (count + m_windowSize - 1) / m_windowSize;
		auto bytesNeeded = windowsNeeded * m_windowBytes;
		if (bytesNeeded > m_shared->committedBytes) {
			if (!slide_window(windowsNeeded - 1))
				return false;
			// move back to original window position
			if (!set_index(m_index))
				return false;
		}

		return true;
	}
}