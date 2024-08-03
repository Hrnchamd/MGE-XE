#pragma once

#include "ipc/bridge.h"
#include "ipc/vec.h"
#include <queue>
#include <vector>

namespace IPC {
	/**
	* @class Server
	* @brief Listener for RPC commands to the 64-bit server process.
	* 
	* Server implements the various RPC commands that the client process may request. The server process is started
	* by the client process and exits automatically when the client process exits. The server process exists to host
	* distant land structures and provide an API to share distant land information with the client. The implementation
	* of this API is handled within the Server class itself via the `listen` method, which will listen for and execute
	* commands until the client process exits or the client instructs the server to exit.
	* 
	* Only one RPC may be active at a time. The client must wait for the completion signal before sending another RPC.
	* The client must also wait for the completion signal after starting the server process, which will be signaled
	* when the server is ready to begin accepting commands.
	*/
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