#pragma once

#define _IPC_VIEW_H

#include "ipc/vecbase.h"
#include "support/winheader.h"

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <optional>

namespace IPC {
	/**
	* @class VecView
	* @brief A client-side view of a shared vector.
	* 
	* VecView is the client-side view of a shared vector. A VecView is obtained after allocating a shared vector via
	* RPC to the server (@ref Client::allocVec). Because shared memory can't be resized, the maximum size of the
	* vector must be specified up-front. However, memory is only reserved and not committed until it's needed, so
	* you can specify an arbitrarily large maximum size without immediately allocating all the memory. The amount of
	* memory to reserve will be rounded up to a multiple of the system allocation granularity (typically 64K), and
	* the maximum size of the vector will likewise be rounded up the number of elements that can fit in that amount
	* of memory.
	* 
	* The client view keeps only a fixed-size window of the vector mapped at any one time. The size of this window
	* must be specified up-front, and will also be rounded up to a multiple of the allocation granularity. To avoid
	* requirng the client to map multiple windows, elements are not stored at locations that would span multiple
	* windows. This means that elements are not contiguous in memory (unless the allocation granularity is a
	* multiple of the element size or the entire vector fits in one window). The window is unmapped and re-mapped
	* as necessary to make requested elements available. This means that, while VecView supports random access,
	* sequential access is most efficient. Also, pointers to elements only remain valid until the window is re-mapped
	* (i.e. when an element in a different window is requested).
	* 
	* Because VecView owns the window into the shared vector, and the window must be re-mapped to view different
	* elements, a VecView is its own iterator. A VecView may be copied, and each copy holds its own window into the
	* vector. This allows for multiple iterators over the vector pointing at different elements. However, setting
	* up the new window involves reserving and mapping memory, so copying a VecView is a non-trivial operation.
	* To support efficient iteration, the at_end method allows checking if the VecView is pointing to the last
	* element in the vector without having to construct an end iterator. Finally, the fact that each VecView maps
	* its own view into the vector means that pointers to the same element obtained from different VecViews will
	* not compare equal. However, two VecViews pointed to the same element of the same vector will compare equal.
	* 
	* VecView does NOT support thread-safe writing. Only one thread/process should write to the shared vector at any
	* given time. It is possible to have one side read elements from the vector as the other side populates them
	* using the start_write/end_write and start_read/end_read methods. When the reader reaches the current end
	* of the vector, it will stop and wait for an update signal from the writer. The writer will signal the reader
	* each time a window's worth of elements has been added to the vector. When end_write is called, the writer will
	* signal to the reader that the operation is complete and it should not expect any more elements. Generally,
	* waiting for updates as the reader is handled automatically by iterator methods and signaling updates as the
	* writer is handled automatically by push_back. However, the reader can explicitly wait by calling wait_read and
	* the writer can explicitly update by calling update_write.
	* 
	* VecView does not call constructors or destructors on elements and is suitable only for storing POD data types.
	* Ensure that the size and layout of elements is consistent between both the 32-bit process and 64-bit process.
	* 
	* Each shared vector has an ID number of type VecId that uniquely identifies that vector across the IPC boundary.
	* All VecViews that view the same vector will have the same ID number.
	* 
	* The vector keeps a reference count of the total number of views of it (both client and server). All resources
	* for the shared vector (other than the window mapping in each VecView) are owned by the server. To free the
	* vector, you must make an RPC to the server. However, the server will not free the vector if the reference count
	* is not zero, so all client-side views must be destroyed prior to the RPC.
	*/
	template<typename T>
	class VecView: public VecBase {
		static_assert(is_vec_safe_v<T>, "VecView does not call constructors or destructors and is not safe for complex types");

		T* m_buffer;
		std::uint32_t m_currentWindow;
		std::uint32_t m_currentWindowIndex;
		std::uint32_t m_nextWindowIndex;
		std::uint32_t m_index;
		std::uint32_t m_subIndex;

		VecView(VecId id, VecShare* shared, std::uint32_t windowElements, std::uint32_t windowBytes, std::uint32_t maxElements, std::uint32_t reservedBytes, std::uint32_t headerBytes);
		bool init();
		bool slide_window(std::uint32_t i, bool isAppend = false);

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
		VecView(const VecView<T>&);
		VecView(VecView<T>&&) noexcept;
		VecView<T>& operator=(const VecView<T>&);

		// iterator methods
		reference operator*() const;
		pointer operator->() const;

		VecView& operator++();
		VecView operator++(int);

		VecView& operator--();
		VecView operator--(int);

		bool operator==(const VecView<T>&) const;
		bool operator!=(const VecView<T>&) const;

		// these methods are slow because they have to reserve and map shared memory.
		// it's probably better in most cases to iterate using the view you already
		// have and checking the at_end method.
		VecView<T> begin() const;
		VecView<T> end() const;

		// iterator extensions
		bool set_index(std::uint32_t i);
		bool at_end();
		bool is_valid() const noexcept;

		// container methods
		T& operator[](std::uint32_t i);
		T& front();
		T& back();
		void truncate(std::uint32_t numElements);

		bool push_back(const T& value);
		bool push_back(T&& value);
		std::optional<T> pop_back();

		bool reserve(std::uint32_t count);
	};
}

#ifndef _IPC_VIEW_CPP
#include "ipc/view.cpp"
#endif