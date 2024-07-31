#pragma once

#define _IPC_VEC_CPP

#ifndef _IPC_VEC_H
#include "ipc/vec.h"
#endif
#include "support/log.h"

namespace IPC {
	// Vec::iterator
	template<typename T>
	Vec<T>::iterator::iterator(Vec<T>* source, T* buffer, std::size_t i, std::size_t windowSize, std::size_t windowBytes) :
		m_source(source),
		m_element(buffer),
		m_windowSize(windowSize),
		m_prevWindow(i - i % windowSize),
		m_nextWindow((i + windowSize - 1) / windowSize),
		m_windowPadding(windowBytes - sizeof(T) * windowSize),
		m_index(i)
	{ }

	template<typename T>
	Vec<T>::iterator::iterator(const Vec<T>::iterator& other) :
		m_source(other.m_source),
		m_element(other.m_element),
		m_windowSize(other.m_windowSize),
		m_prevWindow(other.m_prevWindow),
		m_nextWindow(other.m_nextWindow),
		m_windowPadding(other.m_windowPadding),
		m_index(other.m_index)
	{}

	template<typename T>
	typename Vec<T>::iterator& Vec<T>::iterator::operator=(const Vec<T>::iterator& other) {
		m_source = other.m_source;
		m_element = other.m_element;
		m_windowSize = other.m_windowSize;
		m_prevWindow = other.m_prevWindow;
		m_nextWindow = other.m_nextWindow;
		m_windowPadding = other.m_windowPadding;
		m_index = other.m_index;
		return *this;
	}

	template<typename T>
	typename Vec<T>::iterator::reference Vec<T>::iterator::operator*() const {
		return *m_element;
	}

	template<typename T>
	typename Vec<T>::iterator::pointer Vec<T>::iterator::operator->() const {
		return m_element;
	}

	template<typename T>
	typename Vec<T>::iterator& Vec<T>::iterator::operator++() {
		m_element++;
		m_index++;
		if (m_index >= m_source->size()) {
			m_source->wait_read();
		}

		if (m_index == m_nextWindow) {
			m_element = reinterpret_cast<T*>(reinterpret_cast<char*>(m_element) + m_windowPadding);
			m_prevWindow = m_nextWindow;
			m_nextWindow += m_windowSize;
		}

		return *this;
	}

	template<typename T>
	typename Vec<T>::iterator Vec<T>::iterator::operator++(int) {
		auto beforeIncrement = *this;
		++(*this);
		return beforeIncrement;
	}

	template<typename T>
	typename Vec<T>::iterator& Vec<T>::iterator::operator--() {
		m_element--;
		m_index--;
		if (m_index < m_prevWindow) {
			m_element = reinterpret_cast<T*>(reinterpret_cast<char*>(m_element) - m_windowPadding);
			m_nextWindow = m_prevWindow;
			m_prevWindow -= m_windowSize;
		}

		return *this;
	}

	template<typename T>
	typename Vec<T>::iterator Vec<T>::iterator::operator--(int) {
		auto beforeDecrement = *this;
		--(*this);
		return beforeDecrement;
	}

	template<typename T>
	bool Vec<T>::iterator::operator==(const Vec<T>::iterator& other) const {
		return m_element == other.m_element;
	}

	template<typename T>
	bool Vec<T>::iterator::operator!=(const Vec<T>::iterator& other) const {
		return m_element != other.m_element;
	}

	template<typename T>
	bool Vec<T>::iterator::operator<(const Vec<T>::iterator& other) const {
		return m_element < other.m_element;
	}

	template<typename T>
	typename Vec<T>::iterator Vec<T>::iterator::operator+(Vec<T>::iterator::difference_type count) const {
		std::size_t newIndex = m_index + count;
		return Vec<T>::iterator(m_source, &(*m_source)[newIndex], newIndex, m_windowSize, m_windowSize * sizeof(T) + m_windowPadding);
	}

	template<typename T>
	typename Vec<T>::iterator::difference_type Vec<T>::iterator::operator-(const Vec<T>::iterator& other) const {
		return m_index - other.m_index;
	}

	template<typename T>
	typename Vec<T>::iterator Vec<T>::iterator::operator-(Vec<T>::iterator::difference_type count) const {
		return *this + -count;
	}

	template<typename T>
	bool Vec<T>::iterator::at_end() {
		if (m_index >= m_source->size()) {
			m_source->wait_read();
		}
		return m_index >= m_source->size();
	}

	// Vec
	template<typename T>
	Vec<T>::Vec(VecId id, VecShare* shared, std::size_t maxElements, std::size_t windowElements, std::size_t elementBytes) :
		VecBase(id, shared, windowElements, elementBytes * windowElements, maxElements, elementBytes * maxElements, sizeof(VecShare)),
		m_elementBytes(elementBytes),
		m_buffer(nullptr)
	{
		// round up to a multiple of the allocation granularity
		SYSTEM_INFO sysInfo = {};
		GetSystemInfo(&sysInfo);
		auto allocationGranularity = static_cast<std::size_t>(sysInfo.dwAllocationGranularity);
		auto bytesOver = m_reservedBytes % allocationGranularity;
		if (bytesOver > 0) {
			m_reservedBytes += allocationGranularity - bytesOver;
			m_maxSize = m_reservedBytes / m_elementBytes;
		}

		bytesOver = m_windowBytes % allocationGranularity;
		if (bytesOver > 0) {
			m_windowBytes += allocationGranularity - bytesOver;
			m_windowSize = m_windowBytes / m_elementBytes;
		}

		bytesOver = m_headerBytes % allocationGranularity;
		if (bytesOver > 0) {
			m_headerBytes += allocationGranularity - bytesOver;
		}

		m_shared->committedBytes = 0;
		m_shared->size = 0;
	}

	template<typename T>
	Vec<T>::Vec(const Vec<T>& other) :
		VecBase(other.m_id, other.m_shared, other.m_windowSize, other.m_windowBytes, other.m_maxSize, other.m_reservedBytes, other.m_headerBytes),
		m_elementBytes(other.m_elementBytes),
		m_buffer(other.m_buffer)
	{
		if (m_shared != nullptr) {
			InterlockedIncrement(&m_shared->users);
		}
	}

	template<typename T>
	Vec<T>::Vec(Vec<T>&& other) noexcept :
		VecBase(other.m_id, other.m_shared, other.m_windowSize, other.m_windowBytes, other.m_maxSize, other.m_reservedBytes, other.m_headerBytes),
		m_elementBytes(other.m_elementBytes),
		m_buffer(other.m_buffer)
	{
		other.m_shared = nullptr;
		other.m_buffer = nullptr;
	}

	template<typename T>
	Vec<T>& Vec<T>::operator=(const Vec<T>& other) {
		if (m_shared == other.m_shared) {
			// if we're pointing to the same allocation, we shouldn't need to do anything
			return *this;
		}

		release();

		m_id = other.m_id;
		m_shared = other.m_shared;
		m_maxSize = other.m_maxSize;
		m_reservedBytes = other.m_reservedBytes;
		m_windowSize = other.m_windowSize;
		m_windowBytes = other.m_windowBytes;
		m_headerBytes = other.m_headerBytes;
		m_elementBytes = other.m_elementBytes;
		m_buffer = other.m_buffer;

		return *this;
	}

	template<typename T>
	bool Vec<T>::init(HANDLE clientProcess, AllocVecParameters& params) {
		HANDLE dummy = INVALID_HANDLE_VALUE;
		HANDLE sharedMem32 = INVALID_HANDLE_VALUE;
		HANDLE updateEvent32 = INVALID_HANDLE_VALUE;
		HANDLE completeEvent32 = INVALID_HANDLE_VALUE;

		HANDLE sharedMem = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE | SEC_RESERVE, static_cast<DWORD>(m_reservedBytes >> 32), static_cast<DWORD>(m_reservedBytes), NULL);
		if (sharedMem == NULL) {
			LOG::winerror("Failed to reserve %zu bytes of shared memory for vector %llu", m_reservedBytes, m_id);
			goto failedOnReserve;
		}

		m_shared = static_cast<VecShare*>(MapViewOfFile(sharedMem, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(VecShare)));
		if (m_shared == nullptr) {
			LOG::winerror("Failed to map shared memory for vector %llu header", m_id);
			goto failedOnInit;
		}

		if (VirtualAlloc(m_shared, sizeof(VecShare), MEM_COMMIT, PAGE_READWRITE) == NULL) {
			LOG::winerror("Failed to commit memory for vector %llu header", m_id);
			goto failedOnCommit;
		}

		m_shared->size = 0;
		m_shared->committedBytes = 0;
		m_shared->users = 1;
		m_shared->clientProcess = clientProcess;
		m_shared->sharedMem64 = sharedMem;
		m_shared->header32 = 0;
		m_shared->reading32 = false;
		m_shared->reading64 = false;

		m_buffer = static_cast<char*>(MapViewOfFile(sharedMem, FILE_MAP_ALL_ACCESS, 0, static_cast<DWORD>(m_headerBytes), m_reservedBytes));
		if (m_buffer == nullptr) {
			LOG::winerror("Failed to map shared memory for vector %llu", m_id);
			goto failedOnBufMap;
		}

		m_shared->updateEvent64 = CreateEventA(NULL, FALSE, FALSE, NULL);
		if (m_shared->updateEvent64 == NULL) {
			LOG::winerror("Failed to create update event for vector %llu", m_id);
			goto failedOnUpdateEvent;
		}

		m_shared->completeEvent64 = CreateEventA(NULL, FALSE, FALSE, NULL);
		if (m_shared->completeEvent64 == NULL) {
			LOG::winerror("Failed to create complete event for vector %llu", m_id);
			goto failedOnCompleteEvent;
		}

		// to keep things simple, the server will own all resources allocated for each vec, so we'll duplicate handles and map the header for
		// the client process
		if (!DuplicateHandle(GetCurrentProcess(), sharedMem, clientProcess, &sharedMem32, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
			LOG::winerror("Failed to clone shared memory handle to client process for vector %llu", m_id);
			goto failedOnSharedMemClone;
		}

		if (!DuplicateHandle(GetCurrentProcess(), m_shared->updateEvent64, clientProcess, &updateEvent32, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
			LOG::winerror("Failed to clone update event handle to client process for vector %llu", m_id);
			goto failedOnUpdateClone;
		}

		if (!DuplicateHandle(GetCurrentProcess(), m_shared->completeEvent64, clientProcess, &completeEvent32, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
			LOG::winerror("Failed to clone complete event handle to client process for vector %llu", m_id);
			goto failedOnCompleteClone;
		}

		// truncation warnings are unnecessary because these handles and pointers have been allocated for the target process and only have 32 significant bits
#pragma warning(push)
#pragma warning(disable: 4302 4311)
		m_shared->header32 = reinterpret_cast<ptr32<VecBase::VecShare>>(MapViewOfFile2(sharedMem, clientProcess, 0, NULL, sizeof(VecShare), FILE_MAP_ALL_ACCESS, PAGE_READWRITE));
		if (m_shared->header32 == 0) {
			LOG::winerror("Failed to map vector %llu header into client process", m_id);
			goto failedOnClientMap;
		}

		m_shared->sharedMem32 = reinterpret_cast<HANDLE32>(sharedMem32);
		m_shared->updateEvent32 = reinterpret_cast<HANDLE32>(updateEvent32);
		m_shared->completeEvent32 = reinterpret_cast<HANDLE32>(completeEvent32);
#pragma warning(pop)

		params.reservedBytes = m_reservedBytes;
		params.windowBytes = m_windowBytes;
		params.headerBytes = static_cast<std::uint32_t>(m_headerBytes);
		params.header32 = m_shared->header32;
		params.id = m_id;

		return true;

		// failure cleanup
	failedOnClientMap:
		DuplicateHandle(clientProcess, completeEvent32, clientProcess, &dummy, 0, FALSE, DUPLICATE_CLOSE_SOURCE);
	failedOnCompleteClone:
		DuplicateHandle(clientProcess, updateEvent32, clientProcess, &dummy, 0, FALSE, DUPLICATE_CLOSE_SOURCE);
	failedOnUpdateClone:
		DuplicateHandle(clientProcess, sharedMem32, clientProcess, &dummy, 0, FALSE, DUPLICATE_CLOSE_SOURCE);
	failedOnSharedMemClone:
		CloseHandle(m_shared->completeEvent64);
	failedOnCompleteEvent:
		CloseHandle(m_shared->updateEvent64);
	failedOnUpdateEvent:
		UnmapViewOfFile(m_buffer);
		m_buffer = nullptr;
	failedOnBufMap:
		UnmapViewOfFile(m_shared);
	failedOnCommit:
		m_shared = nullptr;
	failedOnInit:
		CloseHandle(sharedMem);
	failedOnReserve:
		return false;
	}

	template<typename T>
	void Vec<T>::release() {
		if (m_shared == nullptr) {
			return;
		}

		auto remainingUsers = InterlockedDecrement(&m_shared->users);
		if (remainingUsers > 0) {
			return;
		}

		if (m_buffer != nullptr) {
			UnmapViewOfFile(m_buffer);
			m_buffer = nullptr;
		}

		CloseHandle(m_shared->updateEvent64);
		CloseHandle(m_shared->completeEvent64);

		HANDLE dummy; // VS complains if we pass NULL for the target handle
		// these are 32-bit handles that we have to cast to 64-bit handles to match the type signature of the function
#pragma warning(push)
#pragma warning(disable: 4312)
		DuplicateHandle(m_shared->clientProcess, reinterpret_cast<HANDLE>(m_shared->updateEvent32), m_shared->clientProcess, &dummy, 0, FALSE, DUPLICATE_CLOSE_SOURCE);
		DuplicateHandle(m_shared->clientProcess, reinterpret_cast<HANDLE>(m_shared->completeEvent32), m_shared->clientProcess, &dummy, 0, FALSE, DUPLICATE_CLOSE_SOURCE);

		UnmapViewOfFile2(m_shared->clientProcess, reinterpret_cast<PVOID>(m_shared->header32), 0);
		DuplicateHandle(m_shared->clientProcess, reinterpret_cast<HANDLE>(m_shared->sharedMem32), m_shared->clientProcess, &dummy, 0, FALSE, DUPLICATE_CLOSE_SOURCE);
#pragma warning(pop)

		auto sharedMem = m_shared->sharedMem64;
		UnmapViewOfFile(m_shared);
		m_shared = nullptr;

		CloseHandle(sharedMem);
	}

	template<typename T>
	Vec<T>::~Vec() {
		release();
	}

	template<typename T>
	bool Vec<T>::reserve(std::size_t numElements) {
		auto capacity = this->capacity();
		if (capacity >= numElements)
			return true;

		if (numElements > m_maxSize)
			return false;

		// to make things easier for the client, we don't place elements that would span multiple windows
		auto numExtraWindows = ((numElements - capacity) + m_windowSize - 1) / m_windowSize;
		auto bytesNeeded = numExtraWindows * m_windowBytes;
		auto currentEnd = m_buffer + m_shared->committedBytes;
		if (VirtualAlloc(currentEnd, bytesNeeded, MEM_COMMIT, PAGE_READWRITE) == NULL) {
			LOG::winerror("Failed to commit %zu additional bytes of shared memory for vector %llu", bytesNeeded, m_id);
			return false;
		}
		m_shared->committedBytes += bytesNeeded;

		return true;
	}

	template<typename T>
	bool Vec<T>::can_free() const {
		return m_shared == nullptr || m_shared->users <= 1;
	}

	template<typename T>
	T& Vec<T>::operator[](std::size_t i) const {
		auto windowIndex = i / m_windowSize;
		auto elementIndex = i % m_windowSize;
		auto windowOffset = windowIndex * m_windowBytes;
		auto window = reinterpret_cast<T*>(m_buffer + windowOffset);
		return window[elementIndex];
	}

	template<typename T>
	T& Vec<T>::front() const {
		return *reinterpret_cast<T*>(m_buffer);
	}

	template<typename T>
	T& Vec<T>::back() const {
		return (*this)[m_shared->size - 1];
	}

	template<typename T>
	void Vec<T>::truncate(std::size_t numElements) {
		if (numElements < m_shared->size) {
			m_shared->size = numElements;
		}
	}

	template<typename T>
	bool Vec<T>::extend() {
		// commit the next window
		if (m_shared->committedBytes + m_windowBytes > m_reservedBytes) {
			LOG::logline("Vector %llu exceeded maximum reserved size of %zu bytes", m_id, m_reservedBytes);
			return false;
		}

		auto currentEnd = m_buffer + m_shared->committedBytes;
		if (VirtualAlloc(currentEnd, m_windowBytes, MEM_COMMIT, PAGE_READWRITE) == NULL) {
			LOG::winerror("Failed to commit %zu additional bytes of shared memory for vector %llu", m_windowBytes, m_id);
			return false;
		}
		m_shared->committedBytes += m_windowBytes;
		return true;
	}

	template<typename T>
	bool Vec<T>::push_back(const T& value) {
		auto oldSize = m_shared->size;
		auto newSize = oldSize + 1;
		auto capacity = (m_shared->committedBytes / m_windowBytes) * m_windowSize;
		std::size_t offset;
		if (newSize > capacity) {
			offset = static_cast<std::size_t>(m_shared->committedBytes);
			if (!extend())
				return false;
		} else {
			offset = static_cast<std::size_t>(m_shared->committedBytes - m_windowBytes);
		}

		auto window = reinterpret_cast<T*>(m_buffer + offset);
		window[oldSize] = value;
		m_shared->size = newSize;

		if (m_writing && newSize % m_windowSize == 0) {
			return update();
		}

		return true;
	}

	template<typename T>
	bool Vec<T>::push_back(T&& value) {
		auto oldSize = m_shared->size;
		auto newSize = oldSize + 1;
		auto capacity = (m_shared->committedBytes / m_windowBytes) * m_windowSize;
		std::size_t offset;
		if (newSize > capacity) {
			offset = static_cast<std::size_t>(m_shared->committedBytes);
			if (!extend())
				return false;
		} else {
			offset = static_cast<std::size_t>(m_shared->committedBytes - m_windowBytes);
		}

		auto window = reinterpret_cast<T*>(m_buffer + offset);
		window[oldSize] = value;
		m_shared->size = newSize;

		if (m_writing && newSize % m_windowSize == 0) {
			return update();
		}

		return true;
	}

	template<typename T>
	std::optional<T> Vec<T>::pop_back() {
		if (m_shared->size == 0)
			return std::nullopt;

		auto i = --m_shared->size;
		return (*this)[i];
	}

	template<typename T>
	typename Vec<T>::iterator Vec<T>::begin() {
		return Vec<T>::iterator(this, reinterpret_cast<T*>(m_buffer), 0, m_windowSize, m_windowBytes);
	}

	template<typename T>
	typename Vec<T>::iterator Vec<T>::end() {
		auto size = m_shared->size;
		auto endWindow = size / m_windowSize;
		auto subIndex = size % m_windowSize;
		auto end = m_buffer + endWindow * m_windowBytes + subIndex * m_elementBytes;
		return Vec<T>::iterator(this, reinterpret_cast<T*>(end), static_cast<std::size_t>(size), m_windowSize, m_windowBytes);
	}
}