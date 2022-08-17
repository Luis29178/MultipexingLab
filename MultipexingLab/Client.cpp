#include "Client.h"
#include <iostream>
#include <string>
#include <charconv>
int Client::ConnectService(uint16_t port, char* address)
{
	//Comsocket Defined in constructor
	if (ComSocket == INVALID_SOCKET)
	{
		return INVAL_SOCKET;
	}
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr(address);
	serverAddr.sin_port = htons(port);

	int result = connect(ComSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR)
	{

		return SCK_ERROR;
	}
	
	

	return SUCCESS;
}
int Client::readMessage()
{
	//will set a buffer to recive 4 bites
	int32_t size = 16;
	byte* buffer = new byte[size];


	int len = recv(ComSocket, (char*)buffer , size, 0);
	if ((len == SOCKET_ERROR) || (len == 0))
	{
		return DISCONNECT;
	}
	if (len > size)
	{
		return PARAMETER_ERROR;
	}
	delete[] buffer;
	buffer = new byte[len];

	result = reciveTcpData(ComSocket, (char*)buffer, len);
	if ((result == SOCKET_ERROR) || (result == 0))
	{
		return MESSAGE_ERROR;
	}

	return SUCCESS;
}
int Client::sendMessage(char* data, int32_t length)
{
	char* buffer = int_to_char_arr(length);

	result = send(ComSocket, (const char*)buffer, sizeof(buffer), 0);
	if ((result == SOCKET_ERROR))
	{
		return SCK_ERROR;
	}
	
	result = sendTcpData(ComSocket, data, length);
	if ((result == SOCKET_ERROR))
	{

		int error = WSAGetLastError();
		return MESSAGE_ERROR;

	}

	return SUCCESS;
}
char* Client::int_to_char_arr(int _int)
{
	int length = std::to_string(_int).length();
	//convert int to string
	std::string tempstring = std::to_string(_int);
	//convert string to char
	char* c = const_cast<char*>(tempstring.c_str());
	
	return c;
}
 Client::Client(){
	 ComSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	 result = 0;


}