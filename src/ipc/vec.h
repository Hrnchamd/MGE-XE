#pragma once

#define _IPC_VEC_H

#include "ipc/vecbase.h"
#include "support/winheader.h"

#include <cstddef>
#include <iterator>
#include <optional>

namespace IPC {
	template<typename T>
	class Vec: public VecBase {
		std::size_t m_elementBytes;
		char* m_buffer;

		Vec(VecId id, VecShare* shared, std::size_t maxElements, std::size_t windowElements, std::size_t elementBytes = sizeof(T));
		bool init(HANDLE clientProcess, AllocVecParameters& params);
		bool extend();
		void release();

		friend class Server;

	public:
		class iterator {
			Vec<T>* m_source;
			T* m_element;
			std::size_t m_windowSize;
			std::size_t m_windowPadding;
			std::size_t m_prevWindow;
			std::size_t m_nextWindow;
			std::size_t m_index;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			iterator(Vec<T>* source, T* buffer, std::size_t i, std::size_t windowSize, std::size_t windowBytes);
			iterator(const iterator& other);

			iterator& operator=(const iterator& other);

			reference operator*() const;
			pointer operator->() const;

			iterator& operator++();
			iterator operator++(int);

			iterator& operator--();
			iterator operator--(int);

			bool operator==(const iterator& other) const;
			bool operator!=(const iterator& other) const;
			bool operator<(const iterator& other) const;

			iterator operator+(difference_type count) const;
			difference_type operator-(const iterator& other) const;
			iterator operator-(difference_type count) const;

			bool at_end();
		};

		~Vec();
		Vec(Vec&&) noexcept; // for whatever reason, Visual Studio wants noexcept on this specific constructor
		Vec(const Vec&);
		Vec& operator=(const Vec&);

		bool reserve(std::size_t numElements);
		bool can_free() const;
		void truncate(std::size_t numElements);

		T& operator[](std::size_t i) const;
		T& front() const;
		T& back() const;

		bool push_back(const T& value);
		bool push_back(T&& value);
		std::optional<T> pop_back();

		iterator begin();
		iterator end();
	};
}

#ifndef _IPC_VEC_CPP
#include "ipc/vec.cpp"
#endif