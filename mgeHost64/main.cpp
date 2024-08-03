#include "support/winheader.h"
#include "support/log.h"
#include "mge/configuration.h"
#include "ipc/server.h"

#include <cstdio>

int main(int argc, char** argv) {
	LOG::open("mgeHost64.log");
	LOG::logline("Host process started");

	HANDLE sharedMem = INVALID_HANDLE_VALUE;
	HANDLE clientProcess = INVALID_HANDLE_VALUE;
	HANDLE rpcStartEvent = INVALID_HANDLE_VALUE;
	HANDLE rpcCompleteEvent = INVALID_HANDLE_VALUE;
	if (std::sscanf(GetCommandLineA(), "%p %p %p %p", &sharedMem, &clientProcess, &rpcStartEvent, &rpcCompleteEvent) != 4) {
		LOG::logline("Expected handles not found on command line");
		LOG::flush();
		return 1;
	}

#ifdef _DEBUG
	while (!IsDebuggerPresent()) {
		Sleep(100);
	}
#endif

	Configuration.LoadSettings();
	if (!IPC::initImports()) {
		LOG::logline("!! Required memory mapping APIs are not available");
		LOG::flush();
		return 4;
	}

	IPC::Server server(sharedMem, clientProcess, rpcStartEvent, rpcCompleteEvent);
	if (!server.init()) {
		LOG::logline("!! Server initialization failed");
		LOG::flush();
		return 2;
	}
	if (!server.listen()) {
		LOG::logline("!! Server listen failed");
		LOG::flush();
		return 3;
	}

	LOG::flush();
	return 0;
}