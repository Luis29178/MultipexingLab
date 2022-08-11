#pragma once
#define _CRT_SECURE_NO_WARNINGS                 // turns of deprecated warnings
#define _WINSOCK_DEPRECATED_NO_WARNINGS			 // turns of deprecated warnings for winsock

#include "MessageEnum.h"
#include <winsock2.h>
#include <cstdint>
#pragma comment(lib,"Ws2_32.lib")


class Client 
{
private:
	SOCKET ComSocket;
	int result;
public:
	
    int ConnectService(uint16_t port, char* address);
	Client();

	
	

};

