#pragma once

#include "support/winheader.h"
#include "ipc/bridge.h"
#include "ipc/view.h"

#include <cassert>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace IPC {
	class Client {
		HANDLE m_sharedMem;
		HANDLE m_rpcStartEvent;
		union {
			struct {
				HANDLE m_process;
				HANDLE m_rpcCompleteEvent;
			};
			HANDLE m_waitHandles[2];
		};
		Parameters* m_ipcParameters;
		bool m_isRpcPending;

		bool beginRpc(Command command);
		WakeReason tryWaitForCompletion(DWORD ms = MaxWait);

	public:
		Client();
		~Client();
		Client(const Client&) = delete;
		Client& operator=(const Client&) = delete;

		bool startServer(const char* executable);
		bool isServerActive();

		bool allocVec(std::size_t elementSize, std::size_t windowSizeInElements, std::size_t maxSizeInElements, std::size_t initialCapacity);
		template<typename T>
		std::optional<VecView<T>> awaitAllocVec() {
			assert(m_ipcParameters->command == Command::AllocVec);

			auto result = waitForCompletion();
			if (result != WakeReason::Complete) {
				LOG::logline("Vec allocation RPC failed");
				return std::nullopt;
			}

			auto& params = m_ipcParameters->params.allocVecParams;
			if (params.id == InvalidVector) {
				LOG::logline("Vec allocation rejected by server");
				return std::nullopt;
			}

			assert(sizeof(T) == params.elementSize);

			// recalculate elements per window
			auto windowElements = params.windowBytes / sizeof(T);
			VecView<T> view(params.id, static_cast<VecBase::VecShare*>(params.header32), static_cast<std::size_t>(windowElements), static_cast<std::size_t>(params.windowBytes),
				static_cast<std::size_t>((params.reservedBytes / params.windowBytes) * windowElements), static_cast<std::size_t>(params.reservedBytes), static_cast<std::size_t>(params.headerBytes));
			if (!view.init()) {
				return std::nullopt;
			}

			return view;
		}
		template<typename T>
		std::optional<VecView<T>> allocVecBlocking(std::size_t windowSizeInElements, std::size_t maxSizeInElements, std::size_t initialCapacity) {
			if (!allocVec(sizeof(T), windowSizeInElements, maxSizeInElements, initialCapacity)) {
				return std::nullopt;
			}

			return awaitAllocVec<T>();
		}

		bool freeVec(VecId id);
		bool awaitFreeVec();
		bool freeVecBlocking(VecId id);

		bool updateDynVis(const std::vector<std::pair<std::uint16_t, bool>>& flags);

		bool initDistantStatics(VecId distantStatics, VecId distantSubsets);

		bool initLandscape(VecId landscapeBuffers);

		bool setWorldSpaceBlocking(const std::string& cellname);

		bool getVisibleMeshesCoarse(VecId visibleSet, const ViewFrustum& viewFrustum, DWORD setFlags, VisibleSetSort sort = VisibleSetSort::None);

		bool getVisibleMeshes(VecId visibleSet, const ViewFrustum& viewFrustum, const D3DXVECTOR4& viewSphere, DWORD setFlags, VisibleSetSort sort = VisibleSetSort::None);

		bool sortVisibleSet(VecId visibleSet, VisibleSetSort sort);

		WakeReason waitForCompletion(DWORD ms = MaxWait);
	};
}