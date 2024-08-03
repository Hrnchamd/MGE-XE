#pragma once

#include "ipc/bridge.h"

#include <cstddef>
#include <type_traits>

#ifdef MGE64_HOST
#define ARCH(n) n##64
#else
#define ARCH(n) n##32
#endif

namespace IPC {
	// the various D3DX classes aren't considered trivial because they have user-declared constructors and assignment
	// operators, so we can't use is_trivial, even though the implementation of those operators is (or at least, is
	// able to be) trivial in practice. so, we'll go with this abridged version that only checks the triviality of
	// the destructor.
	template<typename T>
	constexpr bool is_vec_safe_v = std::is_trivially_destructible_v<T> && std::is_standard_layout_v<T>;

	class VecBase {
	protected:
#pragma pack(push, 4)
		struct VecShare {
			volatile std::uint32_t size;
			std::uint32_t committedBytes;
			HANDLE64 clientProcess;
			HANDLE64 sharedMem64;
			union {
				struct {
					HANDLE64 updateEvent64;
					HANDLE64 completeEvent64;
				};
				HANDLE64 waitHandles64[2];
			};
			std::uint32_t users;
			HANDLE32 sharedMem32;
			union {
				struct {
					HANDLE32 updateEvent32;
					HANDLE32 completeEvent32;
				};
				HANDLE32 waitHandles32[2];
			};
			ptr32<VecShare> header32;
			bool reading32;
			bool reading64;
		};
#pragma pack(pop)

		std::uint32_t m_headerBytes;
		std::uint32_t m_windowSize;
		std::uint32_t m_windowBytes;
		std::uint32_t m_maxSize;
		std::uint32_t m_reservedBytes;
		VecShare* m_shared;
		VecId m_id;
		bool m_writing;

		VecBase(VecId id, VecShare* shared, std::uint32_t windowElements, std::uint32_t windowBytes, std::uint32_t maxElements, std::uint32_t reservedBytes, std::uint32_t headerBytes);
		void wait_read(DWORD ms = MaxWait);

	public:
		~VecBase();
		VecBase(const VecBase&) = delete;
		VecBase& operator=(const VecBase&) = delete;

		std::uint32_t size() const;
		std::uint32_t max_size() const noexcept;
		std::uint32_t capacity() const;
		bool empty() const;

		void start_write();
		bool update();
		bool complete();
		WakeReason await_update(DWORD ms = MaxWait) const;
		bool end_write();

		void start_read();
		void end_read();

		void clear();

		VecId id() const;
	};
}