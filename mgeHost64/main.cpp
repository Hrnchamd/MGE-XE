#include "support/winheader.h"
#include "support/log.h"
#include "mge/configuration.h"
#include "ipc/server.h"

#include <cstdio>

int main(int argc, char** argv) {
	LOG::open("mgeHost64.log");
	LOG::logline("Host process");

	HANDLE sharedMem = INVALID_HANDLE_VALUE;
	HANDLE clientProcess = INVALID_HANDLE_VALUE;
	HANDLE rpcStartEvent = INVALID_HANDLE_VALUE;
	HANDLE rpcCompleteEvent = INVALID_HANDLE_VALUE;
	if (std::sscanf(GetCommandLineA(), "%p %p %p %p", &sharedMem, &clientProcess, &rpcStartEvent, &rpcCompleteEvent) != 4) {
		LOG::logline("Expected handles not found on command line");
		LOG::flush();
		return 1;
	}

	Configuration.LoadSettings();

	IPC::Server server(sharedMem, clientProcess, rpcStartEvent, rpcCompleteEvent);
	if (!server.init()) {
		LOG::flush();
		return 2;
	}
	if (!server.listen()) {
		LOG::flush();
		return 3;
	}

	LOG::flush();
	return 0;
}