#include "Server.h"
#include "MessageEnum.h"

int Server::ConnectService(uint16_t port, char* address)
{

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	result = bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR)
	{
		int x = WSAGetLastError();
		return INVAL_SOCKET;
	}

	result = listen(listenSocket, 1);
	if (result == SOCKET_ERROR)
	{
		return SCK_ERROR;
	}

	ComSocket = accept(listenSocket, NULL, NULL); // Code will wait for a responce from a client here 
	if (ComSocket == INVALID_SOCKET)
	{
		return INVAL_SOCKET;
	}

	return SUCCESS;
}
Server::Server() {
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	result = 0;

}
