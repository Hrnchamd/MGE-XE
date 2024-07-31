#pragma once

#define _IPC_VIEW_H

#include "ipc/vecbase.h"
#include "support/winheader.h"

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <optional>

namespace IPC {
	template<typename T>
	class VecView: public VecBase {
		T* m_buffer;
		std::size_t m_currentWindow;
		std::size_t m_currentWindowIndex;
		std::size_t m_nextWindowIndex;
		std::size_t m_index;
		std::size_t m_subIndex;

		VecView(VecId id, VecShare* shared, std::size_t windowElements, std::size_t windowBytes, std::size_t maxElements, std::size_t reservedBytes, std::size_t headerBytes);
		bool init();
		bool slide_window(std::size_t i, bool isAppend = false);

		friend class Client;

	public:
		// this type is its own iterator because only a portion of the vector is mapped
		// at any given time, so a separate iterator object wouldn't be able to freely
		// traverse the elements. this class already has all the logic for adjusting
		// the view window, which is what the iterator would need to do, so we might
		// as well use this as the iterator directly.
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		typedef VecView<T> iterator;

		VecView();
		~VecView();
		VecView(const VecView&);
		VecView(VecView&&) noexcept;
		VecView& operator=(const VecView&);

		// iterator methods
		reference operator*() const;
		pointer operator->() const;

		VecView& operator++();
		VecView operator++(int);

		VecView& operator--();
		VecView operator--(int);

		bool operator==(const VecView&) const;
		bool operator!=(const VecView&) const;

		// these methods are slow because they have to duplicate handles and reserve/map
		// shared memory. it's probably better in most cases to iterate using the view
		// you already have and checking the isAtEnd method.
		VecView begin() const;
		VecView end() const;

		// iterator extensions
		bool set_index(std::size_t i);
		bool at_end() const;

		// container methods
		T& operator[](std::size_t i);
		T& front();
		T& back();
		void truncate(std::size_t numElements);

		bool push_back(const T& value);
		bool push_back(T&& value);
		std::optional<T> pop_back();

		bool reserve(std::size_t count);
	};
}

#ifndef _IPC_VIEW_CPP
#include "ipc/view.cpp"
#endif