#pragma once
#define _CRT_SECURE_NO_WARNINGS                 // turns of deprecated warnings
#define _WINSOCK_DEPRECATED_NO_WARNINGS			 // turns of deprecated warnings for winsock

#include "Platform.h"
#include "MessageEnum.h"
#include <string>
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
	int readMessage();
	//int sendMessage(char* data, int32_t length);
	int tcp_send_whole(SOCKET skSocket, const char* data, uint16_t length);
	char* int_to_char_arr(int _int);
	std::string my_int_to_str(int _int);
	Client();

	
	

};

