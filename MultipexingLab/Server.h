#pragma once
#define _CRT_SECURE_NO_WARNINGS                 // turns of deprecated warnings
#define _WINSOCK_DEPRECATED_NO_WARNINGS			 // turns of deprecated warnings for winsock


#include "MessageEnum.h"
#include "Platform.h"
#include <winsock2.h>
#include <cstdint>
#pragma comment(lib,"Ws2_32.lib")

class Server 
{
private:
	fd_set currSockets, readySockets;
	SOCKET listenSocket;
	SOCKET ComSocket;
	int result;

public:
	int ConnectService(uint16_t port, char* address);
	int readMessage(SOCKET _comSocket);
	int sendMessage(char* data, int32_t length);
	Server();

};

