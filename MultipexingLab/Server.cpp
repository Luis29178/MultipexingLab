#include "Server.h"


int Server::ConnectService(uint16_t port, char* address)
{

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	result = bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		return INVAL_SOCKET;
	}

	result = listen(listenSocket, 1);
	if (result == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		return SCK_ERROR;
	}

	FD_ZERO(&currSockets);
	FD_SET(listenSocket, &currSockets);

	while (true)
	{
		
		readySockets = currSockets;

		int socketCount = select(NULL, &readySockets, NULL, NULL, NULL);
		if (socketCount < 0)
		{
			int error = WSAGetLastError();
			return SELECT_ERROR;

		}
		if (FD_ISSET(listenSocket, &readySockets)) {
			ComSocket = accept(listenSocket, NULL,NULL);
			FD_SET(ComSocket, &currSockets);

		}
		for (int i = 0; i < socketCount; i++){
			//^ for & v if : both work to itterate throught fd_sets
			if (readySockets.fd_array[i] != listenSocket) {

				readMessage(readySockets.fd_array[i]);

			}
					
				

			
		}

	}


	




	return SUCCESS;
}
int Server::readMessage(SOCKET _comSocket)
{
	char* buffer = new char[256];
	buffer[0] = (byte)'\0';

	int32_t size = sizeof(buffer);
	int len = recv(_comSocket, buffer, size, 0);
	if ((len == SOCKET_ERROR) || (len == 0))
	{
		int error = WSAGetLastError();
		return SCK_ERROR;
	}
	if (len > size)
	{
		int error = WSAGetLastError();
		return PARAMETER_ERROR;
	}

	result = reciveTcpData(_comSocket, (char*)buffer, len);
	if ((result == SOCKET_ERROR) || (result == 0))
	{
		// WSAGetLastError() retrives the error in witch result termintated with
		int error = WSAGetLastError();
		return MESSAGE_ERROR;

	}

	return SUCCESS;
}
int Server::sendMessage(char* data, int32_t length)
{
	int len = send(ComSocket, (const char*)data, length, 0);
	if ((len == SOCKET_ERROR) || (len == 0))
	{
		return DISCONNECT;
	}
	if (len < 0 || len >255)
	{
		return PARAMETER_ERROR;
	}

	result = sendTcpData(ComSocket, data, len);
	if ((result == SOCKET_ERROR) || (result == 0))
	{

		int error = WSAGetLastError();
		return MESSAGE_ERROR;

	}
	return SUCCESS;
}
Server::Server() {

	ComSocket = NULL;
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	result = 0;

}
