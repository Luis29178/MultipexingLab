#include "Client.h"
#include <string>
#include <iostream>
#include <charconv>
int Client::tcp_send_whole(SOCKET skSocket, const char* data, uint16_t length)
{
	
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
	else
	{
		 
		while (true)
		{
			std::string x;
			std::cout << std::endl << "Connected to server:\n\n" << "\tUse\n" << "$register YourUserName |-> to register the userto the server\n" <<
				std::endl;

			std::string dtemp = "";
			std::cin.ignore();
			std::getline(std::cin, dtemp);

			int dtempLen = dtemp.length();
			std::string sss = std::to_string(dtempLen);
			
		
			

			int intsz = sss.length();

			if (intsz == 4)
			{
				
			}
			else if (intsz > 0 && intsz < 4)
			{
				char* temp = new char[4];
				int loadFlag = 0;
				int difdif = 4 - intsz;

				for (int x = 0; x < difdif; x++)
				{
					temp[x] = '0';

				}
				for (int i = 0; i < (4 - difdif); i++)
				{
					temp[i + difdif] = sss[i];
				}

				sss = temp;

			}
			
			result = tcp_send_whole(ComSocket, sss.c_str(), 4);
			if ((result == SOCKET_ERROR) || (result == 0))
			{
				// WSAGetLastError() retrives the error in witch result termintated with
				int error = WSAGetLastError();
				return SCK_ERROR;

			}
			

			char* sendBufferfull = new char[dtemp.length()];
			memset(sendBufferfull, 0, dtemp.length());
			strcpy(sendBufferfull, dtemp.c_str());

			result = tcp_send_whole(ComSocket, sendBufferfull, dtemp.length());
		}


	}
	
	

	return SUCCESS;
}
int Client::readMessage()
{
	//will set a buffer to recive 4 bites
	int32_t size = 4;
	byte* buffer = new byte[4];


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


//int Client::sendMessage(char* data, int32_t length)
//{
//
//	//sends holds the length of the message
//	
//
//	char* buffer = new char[30];
//	uint8_t size = 30;
//	std::string bufferlensrting = Client::my_int_to_str(length);
//	char* bufferLenCharArr = (char*)bufferlensrting.c_str();
//	int blen = bufferlensrting.length();
//	
//	#pragma region MessageSetup
//	if (blen == 4)
//	{
//		buffer = int_to_char_arr(length);
//	}
//	else if (blen > 0 && blen < 4)
//	{
//		char* temp = buffer;
//		int loadFlag = 0;
//		int difdif = 4 - blen;
//
//		for (int x = 0; x < difdif; x++)
//		{
//			temp[x] = '0';
//
//		}
//		for (int i = 0; i < (4 - difdif); i++)
//		{
//			temp[i + difdif] = bufferLenCharArr[i];
//		}
//
//		buffer = temp;
//		
//	}
//	else
//	{
//		return PARAMETER_ERROR;
//	}
//#pragma endregion
//
//
//	int bytesSent = 0;
//
//	while (bytesSent < 16)
//	{
//		result = send(ComSocket, (const char*)buffer + bytesSent, 4 - bytesSent, 0);
//
//		if (result <= 0)
//			return result;
//
//		bytesSent += result;
//	}
//	if ((result == SOCKET_ERROR))
//	{
//		return SCK_ERROR;
//	}
//	if ((result == SOCKET_ERROR))
//	{
//		return SCK_ERROR;
//	}
//	
//	bytesSent = 0;
//
//	while (bytesSent < length)
//	{
//		result = send(ComSocket, (const char*)data + bytesSent, length - bytesSent, 0);
//
//		if (result <= 0)
//			return result;
//
//		bytesSent += result;
//	}
//	if ((result == SOCKET_ERROR))
//	{
//		return SCK_ERROR;
//	}
//	if ((result == SOCKET_ERROR))
//	{
//
//		int error = WSAGetLastError();
//		return MESSAGE_ERROR;
//
//	}
//
//	return SUCCESS;
//}
char* Client::int_to_char_arr(int _int)
{
	int length = std::to_string(_int).length();
	//convert int to string
	std::string tempstring = std::to_string(_int);
	//convert string to char
	char* c = (char*)tempstring.c_str();
	
	return c;
}
std::string Client::my_int_to_str(int _int)
{
	int number = _int;

	std::string tmp = std::to_string(number);
	char const* num_char = tmp.c_str();

	return num_char;
}
 Client::Client(){
	 ComSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	 result = 0;


}