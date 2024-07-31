#pragma once

#include "ipc/bridge.h"
#include "ipc/vec.h"
#include <queue>
#include <vector>

namespace IPC {
	class Server {
		HANDLE m_sharedMem;
		union {
			struct {
				HANDLE m_clientProcess;
				HANDLE m_rpcStartEvent;
			};
			HANDLE m_waitHandles[2];
		};
		HANDLE m_rpcCompleteEvent;
		std::vector<Vec<char>*> m_vecs;
		std::queue<VecId> m_freeVecs;
		Parameters* m_ipcParameters;

		template<typename T>
		Vec<T>& getVec(VecId id);

		bool allocVec();
		bool freeVec();
		void updateDynVis();
		bool initDistantStatics();
		bool initLandscape();
		void setWorldSpace();
		void getVisibleMeshesCoarse();
		void getVisibleMeshes();
		void sortVisibleSet();

	public:
		Server(HANDLE sharedMem, HANDLE clientProcess, HANDLE rpcStartEvent, HANDLE rpcCompleteEvent);
		~Server();
		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;

		bool init();
		bool listen();

		bool complete();
	};
}