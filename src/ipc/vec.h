#pragma once

#define _IPC_VEC_H

#include "ipc/vecbase.h"
#include "support/winheader.h"

#include <cstddef>
#include <iterator>
#include <optional>

namespace IPC {
	/**
	* @class Vec
	* @brief A server-side view of a shared vector.
	* 
	* Vec is the server-side view of a shared vector. Currently, shared vectors can only be allocated by RPC request
	* from the client. Because shared memory can't be resized, the maximum size of the vector must be specified
	* up-front. However, memory is only reserved and not committed until it's needed, so you can specify an arbitrarily
	* large maximum size without immediately allocating all the memory. The amount of memory to reserve will be rounded
	* up to a multiple of the system allocation granularity (typically 64K), and the maximum size of the Vec will
	* likewise be rounded up the number of elements that can fit in that amount of memory.
	* 
	* The client view keeps only a fixed-size window of the vector mapped at any one time. The size of this window
	* must be specified up-front, and will also be rounded up to a multiple of the allocation granularity. To avoid
	* requirng the client to map multiple windows, elements are not stored at locations that would span multiple
	* windows. This means that elements are not contiguous in memory (unless the allocation granularity is a
	* multiple of the element size or the entire vector fits in one window). By contrast, the server has the entire
	* vector mapped at all times, so it supports efficient random access. Furthermore, because the shared memory
	* region is never reallocated, pointers to elements will remain valid indefinitely unless the element is removed
	* from the vector.
	* 
	* Vec does NOT support thread-safe writing. Only one thread/process should write to the shared vector at any
	* given time. It is possible to have one side read elements from the vector as the other side populates them
	* using the start_write/end_write and start_read/end_read methods. When the reader reaches the current end
	* of the vector, it will stop and wait for an update signal from the writer. The writer will signal the reader
	* each time a window's worth of elements has been added to the vector. When end_write is called, the writer will
	* signal to the reader that the operation is complete and it should not expect any more elements. Generally,
	* waiting for updates as the reader is handled automatically by iterator methods and signaling updates as the
	* writer is handled automatically by push_back. However, the reader can explicitly wait by calling wait_read and
	* the writer can explicitly update by calling update_write.
	* 
	* Vec does not call constructors or destructors on elements and is suitable only for storing POD data types.
	* Ensure that the size and layout of elements is consistent between both the 32-bit process and 64-bit process.
	* 
	* Each shared vector has an ID number of type VecId that uniquely identifies that vector across the IPC boundary.
	* Vecs can be safely copied; each copy will be a view of the same shared vector and will have the same ID number.
	* 
	* Each shared vector reserves space at the beginning of the shared region for a header that shares information
	* between client and server. The space for this header is not charged against the Vec's maximum capacity.
	* 
	* All resources allocated for the shared vector are owned by the server. The vector keeps a reference count of the
	* total number of views of it (both client and server). When a Vec is destroyed, if the reference count reaches zero,
	* all resources associated with the vector will be freed. The vector's ID may then be assigned to another vector in
	* the future.
	*/
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
		bool is_valid() const noexcept;

		T& operator[](std::uint32_t i) const;
		T& front() const;
		T& back() const;

		bool push_back(const T& value);
		std::optional<T> pop_back();

		iterator begin();
		iterator end();
	};
}

#ifndef _IPC_VEC_CPP
#include "ipc/vec.cpp"
#endif