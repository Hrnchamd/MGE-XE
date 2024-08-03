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
		static_assert(is_vec_safe_v<T>, "Vec does not call constructors or destructors and is not safe for complex types");

		std::uint32_t m_elementBytes;
		char* m_buffer;

		Vec(VecId id, VecShare* shared, std::uint32_t maxElements, std::uint32_t windowElements, std::uint32_t elementBytes = static_cast<std::uint32_t>(sizeof(T)));
		bool init(HANDLE clientProcess, AllocVecParameters& params);
		bool extend();
		void release();

		friend class Server;

	public:
		class iterator {
			Vec<T>* m_source;
			T* m_element;
			std::uint32_t m_windowSize;
			std::uint32_t m_windowPadding;
			std::uint32_t m_prevWindow;
			std::uint32_t m_nextWindow;
			std::uint32_t m_index;

		public:
			using iterator_category = std::random_access_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			iterator(Vec<T>* source, T* buffer, std::uint32_t i, std::uint32_t windowSize, std::uint32_t windowBytes);
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
			bool operator>(const iterator& other) const;
			bool operator<=(const iterator& other) const;
			bool operator>=(const iterator& other) const;

			iterator operator+(difference_type count) const;
			difference_type operator-(const iterator& other) const;
			iterator operator-(difference_type count) const;

			iterator& operator+=(difference_type count);
			iterator& operator-=(difference_type count);

			bool at_end();
		};

		~Vec();
		Vec(Vec&&) noexcept; // for whatever reason, Visual Studio wants noexcept on this specific constructor
		Vec(const Vec&);
		Vec& operator=(const Vec&);

		bool reserve(std::uint32_t numElements);
		bool can_free() const;
		void truncate(std::uint32_t numElements);

		T& operator[](std::uint32_t i) const;
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