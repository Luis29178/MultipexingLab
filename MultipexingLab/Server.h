#pragma once
#define _CRT_SECURE_NO_WARNINGS                 // turns of deprecated warnings
#define _WINSOCK_DEPRECATED_NO_WARNINGS			 // turns of deprecated warnings for winsock


#include "MessageEnum.h"
#include "Platform.h"
#include "UserInfo.h"
#include <vector>
#include <winsock2.h>
#include <cstdint>
#pragma comment(lib,"Ws2_32.lib")

class Server 
{
private:
	
	//holds users info
	UserInfo* Users = new UserInfo[5];
	
	fd_set currSockets, readySockets;
	sockaddr userAddr;
	SOCKET listenSocket;
	SOCKET ComSocket;
	int result;
	int sizeOfUsereaddr;

public:
	int ConnectService(uint16_t port, char* address);
	int readMessage(SOCKET _comSocket);
	int sendMessage(char* data, int32_t length);
	Server();

};

