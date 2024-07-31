#pragma once

#include "ipc/bridge.h"

#include <cstddef>

#ifdef MGE64_HOST
#define ARCH(n) n##64
#else
#define ARCH(n) n##32
#endif

namespace IPC {
	class VecBase {
	protected:
#pragma pack(push, 4)
		struct VecShare {
			volatile std::uint64_t size;
			std::uint64_t committedBytes;
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

		std::size_t m_headerBytes;
		std::size_t m_windowSize;
		std::size_t m_windowBytes;
		std::size_t m_maxSize;
		std::size_t m_reservedBytes;
		VecShare* m_shared;
		VecId m_id;
		bool m_writing;

		VecBase(VecId id, VecShare* shared, std::size_t windowElements, std::size_t windowBytes, std::size_t maxElements, std::size_t reservedBytes, std::size_t headerBytes);
		void wait_read(DWORD ms = MaxWait);

	public:
		~VecBase();
		VecBase(const VecBase&) = delete;
		VecBase& operator=(const VecBase&) = delete;

		std::size_t size() const;
		std::size_t max_size() const noexcept;
		std::size_t capacity() const;
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