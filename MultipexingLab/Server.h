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
	UserInfo* Users = new UserInfo[3];
	int UserCount;
	
	fd_set currSockets, readySockets;
	sockaddr userAddr;
	SOCKET listenSocket;
	SOCKET ComSocket;
	int result;
	int sizeOfUsereaddr;
	

public:
	int tcp_recv_whole(SOCKET s, char* buf, int len);
	char* FirtsLogAck;
	int ConnectService(uint16_t port, char* address);
	int commandHandeler(char* _command);
	//int readMessage(SOCKET _comSocket);
	//int sendMessage(int s ,char* data, int32_t length);
	char* int_to_char_arr(int _int);
	Server();

};

