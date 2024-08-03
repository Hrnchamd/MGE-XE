#include "client.h"
#include "support/log.h"

#include <cassert>
#include <cstdio>

// ideally this would go in beginRpc, but we can't put it there because we
// need to check that the previous command has finished before we start
// manipulating parameters
#define WAIT_FOR_PREVIOUS_COMMAND { \
	if (tryWaitForCompletion() != WakeReason::Complete) { \
		return false; \
	} \
}

namespace IPC {
	Client::Client() :
		m_process(INVALID_HANDLE_VALUE),
		m_sharedMem(INVALID_HANDLE_VALUE),
		m_rpcStartEvent(INVALID_HANDLE_VALUE),
		m_rpcCompleteEvent(INVALID_HANDLE_VALUE),
		m_ipcParameters(nullptr),
		m_isRpcPending(false)
	{}

	Client::~Client() {
		if (m_process != INVALID_HANDLE_VALUE) {
			TerminateProcess(m_process, 0);
			CloseHandle(m_process);
			m_process = INVALID_HANDLE_VALUE;
		}

		if (m_ipcParameters != nullptr) {
			UnmapViewOfFile(m_ipcParameters);
			m_ipcParameters = nullptr;
		}

		CleanupHandle(m_sharedMem);
		CleanupHandle(m_rpcStartEvent);
		CleanupHandle(m_rpcCompleteEvent);
	}

	bool Client::isServerActive() {
		if (m_process != INVALID_HANDLE_VALUE) {
			if (WaitForSingleObject(m_process, 0) == WAIT_OBJECT_0) {
				// the host process was started but is no longer running
				CloseHandle(m_process);
				m_process = INVALID_HANDLE_VALUE;
				return false;
			}

			return true;
		}

		return false;
	}

	bool Client::startServer(const char* executable) {
		STARTUPINFO startupInfo = {};
		PROCESS_INFORMATION processInfo = {};
		char strHandles[256] = { 0, };

		if (isServerActive()) {
			TerminateProcess(m_process, 0);
			CloseHandle(m_process);
			m_process = INVALID_HANDLE_VALUE;
		}

		CleanupHandle(m_sharedMem);
		CleanupHandle(m_rpcStartEvent);
		CleanupHandle(m_rpcCompleteEvent);

		// make the mapping handle inheritable
		SECURITY_ATTRIBUTES attrsAllowInherit = {
			sizeof(SECURITY_ATTRIBUTES), NULL, TRUE
		};
		m_sharedMem = CreateFileMappingA(INVALID_HANDLE_VALUE, &attrsAllowInherit, PAGE_READWRITE, 0, sizeof(Parameters), NULL);
		if (m_sharedMem == NULL) {
			LOG::winerror("Failed to create shared memory region");
			goto failedOnCreateMapping;
		}

		m_ipcParameters = static_cast<Parameters*>(MapViewOfFile(m_sharedMem, FILE_MAP_ALL_ACCESS, 0, 0, 0));
		if (m_ipcParameters == nullptr) {
			LOG::winerror("Failed to map shared memory region");
			goto failedOnMap;
		}

		ZeroMemory(m_ipcParameters, sizeof(Parameters));

		// get other handles the server will need
		HANDLE thisProcess;
		if (!DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(), &thisProcess, 0, TRUE, DUPLICATE_SAME_ACCESS)) {
			LOG::winerror("Failed to duplicate current process handle");
			goto failedOnProcessHandle;
		}

		m_rpcStartEvent = CreateEventA(&attrsAllowInherit, FALSE, FALSE, NULL);
		if (m_rpcStartEvent == NULL) {
			LOG::winerror("Failed to create RPC start event");
			goto failedOnCreateEvent;
		}

		m_rpcCompleteEvent = CreateEventA(&attrsAllowInherit, FALSE, FALSE, NULL);
		if (m_rpcCompleteEvent == NULL) {
			LOG::winerror("Failed to create RPC complete event");
			goto failedOnCreateCompleteEvent;
		}

		std::sprintf(strHandles, "%p %p %p %p", m_sharedMem, thisProcess, m_rpcStartEvent, m_rpcCompleteEvent);
		if (!CreateProcessA(executable, strHandles, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInfo)) {
			LOG::winerror("Failed to start 64-bit host process %s", executable);
			goto failedOnCreateProcess;
		}

		m_process = processInfo.hProcess;
		// don't care about thread handle
		CloseHandle(processInfo.hThread);

		LOG::logline("64-bit host process started (PID %u)", processInfo.dwProcessId);

		// wait for the server to finish bootstrapping
		if (waitForCompletion() == WakeReason::Complete) {
			return true;
		}

		LOG::logline("Failed waiting for 64-bit host process to initialize");

	failedOnCreateProcess:
		CleanupHandle(m_rpcCompleteEvent);
	failedOnCreateCompleteEvent:
		CleanupHandle(m_rpcStartEvent);
	failedOnCreateEvent:
		CloseHandle(thisProcess);
	failedOnProcessHandle:
		UnmapViewOfFile(m_ipcParameters);
		m_ipcParameters = nullptr;
	failedOnMap:
		CloseHandle(m_sharedMem);
	failedOnCreateMapping:
		m_sharedMem = INVALID_HANDLE_VALUE;
		return false;
	}

	bool Client::beginRpc(Command command) {
		if (m_isRpcPending) {
			LOG::logline("Attempted RPC while another RPC was still in progress");
			return false;
		}

		// clear any unprocessed completion events
		ResetEvent(m_rpcCompleteEvent);

		m_ipcParameters->command = command;
		if (!SetEvent(m_rpcStartEvent)) {
			LOG::winerror("Failed to set RPC start event");
			return false;
		}

		m_isRpcPending = true;
		return true;
	}

	bool Client::allocVec(std::size_t elementSize, std::size_t windowSizeInElements, std::size_t maxSizeInElements, std::size_t initialCapacity) {
		WAIT_FOR_PREVIOUS_COMMAND;

		auto& params = m_ipcParameters->params.allocVecParams;
		params.elementSize = elementSize;
		params.windowSizeInElements = windowSizeInElements;
		params.maxCapacityInElements = maxSizeInElements;
		params.initialCapacity = initialCapacity;
		return beginRpc(Command::AllocVec);
	}

	bool Client::freeVec(VecId id) {
		WAIT_FOR_PREVIOUS_COMMAND;

		m_ipcParameters->params.freeVecParams.id = id;
		return beginRpc(Command::FreeVec);
	}

	bool Client::awaitFreeVec() {
		assert(m_ipcParameters->command == Command::FreeVec);

		auto result = waitForCompletion();
		if (result != WakeReason::Complete) {
			LOG::logline("Vec free RPC failed");
			return false;
		}

		return m_ipcParameters->params.freeVecParams.wasFreed;
	}

	bool Client::freeVecBlocking(VecId id) {
		if (!freeVec(id)) {
			return false;
		}

		return awaitFreeVec();
	}

	bool Client::updateDynVis(VecId id) {
		WAIT_FOR_PREVIOUS_COMMAND;

		m_ipcParameters->params.dynVisParams.id = id;
		return beginRpc(Command::UpdateDynVis);
	}

	bool Client::initDistantStatics(VecId distantStatics, VecId distantSubsets) {
		WAIT_FOR_PREVIOUS_COMMAND;

		auto& params = m_ipcParameters->params.distantStaticParams;
		params.distantStatics = distantStatics;
		params.distantSubsets = distantSubsets;
		return beginRpc(Command::InitDistantStatics);
	}

	bool Client::initLandscape(VecId landscapeBuffers) {
		WAIT_FOR_PREVIOUS_COMMAND;

		m_ipcParameters->params.initLandscapeParams.buffers = landscapeBuffers;
		return beginRpc(Command::InitLandscape);
	}

	bool Client::setWorldSpaceBlocking(const std::string& cellname) {
		WAIT_FOR_PREVIOUS_COMMAND;

		auto& params = m_ipcParameters->params.worldSpaceParams;
		strncpy(params.cellname, cellname.c_str(), sizeof(params.cellname));
		params.cellname[sizeof(params.cellname) - 1] = 0;
		if (!beginRpc(Command::SetWorldSpace)) {
			return false;
		}

		if (waitForCompletion() != WakeReason::Complete)
			return false;

		return params.cellFound;
	}

	bool Client::getVisibleMeshesCoarse(VecId visibleSet, const ViewFrustum& viewFrustum, DWORD setFlags, VisibleSetSort sort) {
		WAIT_FOR_PREVIOUS_COMMAND;

		auto& params = m_ipcParameters->params.meshParams;
		params.visibleSet = visibleSet;
		params.viewFrustum = viewFrustum;
		params.sort = sort;
		params.setFlags = setFlags;
		return beginRpc(Command::GetVisibleMeshesCoarse);
	}

	bool Client::getVisibleMeshes(VecId visibleSet, const ViewFrustum& viewFrustum, const D3DXVECTOR4& viewSphere, DWORD setFlags, VisibleSetSort sort) {
		WAIT_FOR_PREVIOUS_COMMAND;

		auto& params = m_ipcParameters->params.meshParams;
		params.visibleSet = visibleSet;
		params.viewFrustum = viewFrustum;
		params.viewSphere = viewSphere;
		params.sort = sort;
		params.setFlags = setFlags;
		return beginRpc(Command::GetVisibleMeshes);
	}

	bool Client::sortVisibleSet(VecId visibleSet, VisibleSetSort sort) {
		WAIT_FOR_PREVIOUS_COMMAND;

		if (sort == VisibleSetSort::None) {
			SetEvent(m_rpcCompleteEvent);
			return true;
		}

		auto& params = m_ipcParameters->params.meshParams;
		params.visibleSet = visibleSet;
		params.sort = sort;
		return beginRpc(Command::SortVisibleSet);
	}

	WakeReason Client::waitForCompletion(DWORD ms) {
		auto result = WaitForMultipleObjects(2, m_waitHandles, FALSE, ms);
		switch (result) {
		case WAIT_FAILED:
			LOG::winerror("IPC client wait for RPC completion failed");
			return WakeReason::Error;
		case WAIT_TIMEOUT:
			return WakeReason::Timeout;
		default:
			auto handleIndex = result - WAIT_OBJECT_0;
			switch (handleIndex) {
			case 0:
				return WakeReason::ServerLost;
			case 1:
				m_isRpcPending = false;
				return WakeReason::Complete;
			default:
				return WakeReason::Error;
			}
		}
	}

	WakeReason Client::tryWaitForCompletion(DWORD ms) {
		if (m_isRpcPending) {
			return waitForCompletion(ms);
		}

		return WakeReason::Complete;
	}
}