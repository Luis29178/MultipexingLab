#include "PlatformBase.h"
#include"MessageEnum.h"




int PlatformBase::readMessage(char* buffer, int32_t size)
{
	int len = recv(ComSocket, buffer, size, 0);
	if ((len == SOCKET_ERROR) || (len == 0))
	{
		return SCK_ERROR;
	}
	if (len > size)
	{
		return PARAMETER_ERROR;
	}


	result = reciveTcpData(ComSocket, (char*)buffer, len);
	if ((result == SOCKET_ERROR) || (result == 0))
	{
		return MESSAGE_ERROR;
	}

	return SUCCESS;
}

int PlatformBase::sendMessage(char* data, int32_t length)
{
	int len = send(ComSocket, (const char*)data, length, 0);
	if ((len == SOCKET_ERROR) || (len == 0))
	{
		return SCK_ERROR;
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






int PlatformBase::sendTcpData(SOCKET skSocket, const char* data, uint16_t length)
{
	int result;
	int bytesSent = 0;



	while (bytesSent < length)
	{



		result = send(skSocket, (const char*)data + bytesSent, length - bytesSent, 0);

		if (result <= 0)
			return result;

		bytesSent += result;
	}

	return bytesSent;
}

int PlatformBase::reciveTcpData(SOCKET s, char* buffer, int length)
{
	int total = 0;



	do
	{

		int ret = recv(s, buffer + total, length - total, 0);
		if (ret < 1)
			return ret;
		else
			total += ret;

	} while (total < length);

	return total;
}

