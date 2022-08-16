#pragma once

#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include "stdint.h"

// Platform-specific library export line (in Windows, DLL export.)
#define EXPORTED extern "C" __declspec(dllexport) 


	int sendTcpData(SOCKET skSocket, const char* data, uint16_t length);

	int reciveTcpData(SOCKET s, char* buffer, int length);

