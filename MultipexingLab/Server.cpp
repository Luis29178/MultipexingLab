#include "Server.h"
#include "CommandEnum.h"
#include <string>
#include <iostream>




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

			sizeOfUsereaddr = sizeof(struct sockaddr);
			ComSocket = accept(listenSocket, &userAddr,&sizeOfUsereaddr);
			sockaddr_in *temp = (sockaddr_in*)&userAddr;
			char* adress = inet_ntoa(temp->sin_addr);


			FD_SET(ComSocket, &currSockets);
			

		}
		else {
			for (int i = 0; i < socketCount; i++) {
				//^ for & v if : both work to itterate throught fd_sets
				if (readySockets.fd_array[i] != listenSocket) {

					char* size = new char[4];
					result = tcp_recv_whole(ComSocket, (char*)size, 4);
					if ((result == SOCKET_ERROR) || (result == 0))
					{
						// WSAGetLastError() retrives the error in witch result termintated with
						int error = WSAGetLastError();
						return SCK_ERROR;

					}
					
					std::string len = "";
					for (int i = 0; i < 4; i++)
					{
						len = len + size[i];
					}
					std::string truelen = "";
					for (int i = 0; i < 4; i++)
					{
						bool check = true;
						if(len[i] == '0' && check)
						{
							
						}
						else
						{
							truelen = truelen + len[i];
							check = false;
						}
					}
					int sendlen = stoi(truelen);
					char* buffer = new char[sendlen];

					result = tcp_recv_whole(ComSocket, (char*)buffer, sendlen);
					if ((result == SOCKET_ERROR) || (result == 0))
					{
						// WSAGetLastError() retrives the error in witch result termintated with
						int error = WSAGetLastError();
						return SCK_ERROR;

					}
					else
					{
						bool cbool = true;
						int spliterIndex = 0;
						for (int i = 0; i < sendlen; i++)
						{
							char comchar = buffer[i];
							if (comchar != ' ' && cbool)
							{
								spliterIndex++;
							}
							else
							{
								cbool = false;
							}
						}

						char* command = new char[spliterIndex];
						for (int i = 0; i < spliterIndex; i++)
						{
							command[i] = buffer[i];
						}
						char* UserName = new char[abs(sendlen-spliterIndex)];
						for (int i = spliterIndex; i < sendlen; i++)
						{
							UserName[i - spliterIndex] = buffer[i];
						}


						if (command[0] == '$')
						{
							result = commandHandeler(command);
						}

						switch (result)
						{
						case REGISTER:
						{
							UserInfo newUser = UserInfo(UserName, address, ComSocket);
							Users[UserCount] = newUser;
							UserCount++;
							break;

						}
						case DISPLAY_CREDENTIAL:
						{
							UserInfo temp;
							for (int i = 0; i < UserCount; i++)
							{
								if (Users[i].getipAddress() == address)
								{
									std::cout << "Username: " << Users[i].getUserName() << std::endl
										<< "Ipv4: " << Users[i].getipAddress() << std::endl;
									break;
								}
							}
							
						}
						case QUIT:
						{
							UserInfo* temp = new UserInfo[3];
							int x = 0;
							for (int i = 0; i < UserCount; i++)
							{
								if (Users[i].getSocket() == ComSocket)
								{
									
								}
								else
								{
									temp[x] = Users[i];
									x++;
								}
							}

							Users = temp;
							closesocket(ComSocket);
						}
						default:
							break;
						}
						/*std::string scommand = "";
						for (int i = 0; i < spliterIndex; i++)
						{
							scommand = scommand + command[i];
						}

						if (scommand == "$register")
						{
							UserInfo newUser = UserInfo(UserName, address, ComSocket);
						}*/
					}

				}

			}
		}


	}


	




	return SUCCESS;
}

int Server::commandHandeler(char* _command)
{
	std::string scommand = "";
	for (int i = 0; i < sizeof(_command); i++)
	{
		scommand = scommand + _command[i];
	}

	if (scommand == "$reg")
	{
		return REGISTER;
	}
	if (scommand == "$disCred")
	{
		return DISPLAY_CREDENTIAL;
	}
	if (scommand == "$quit")
	{
		return QUIT;
	}

}




//int Server::readMessage(SOCKET _comSocket)
//{
//	char* buffer = new char[4];
//	
//
//	int32_t size = sizeof(buffer);
//	int lTotal = 0;
//	int len;
//
//	#pragma region Length Send Loop
//	do
//	{
//		len = recv(_comSocket, buffer + lTotal, size - lTotal, 0);
//		if (len < 1)
//			return MESSAGE_ERROR;
//		else
//			lTotal += len;
//	} while (lTotal < size);
//	if ((len == SOCKET_ERROR) || (len == 0))
//	{
//		int error = WSAGetLastError();
//		return SCK_ERROR;
//	}
//	if (len > size)
//	{
//		int error = WSAGetLastError();
//		return PARAMETER_ERROR;
//	}
//#pragma endregion
//
//
//	std::string slen = std::string(buffer);
//	len = stoi(slen);
//	buffer = new char[len];
//	result = recv(_comSocket, buffer, len, 0);
//	if ((result == SOCKET_ERROR) || (result == 0))
//	{
//		// WSAGetLastError() retrives the error in witch result termintated with
//		int error = WSAGetLastError();
//		return MESSAGE_ERROR;
//
//	}
//
//	return SUCCESS;
//}
int Server::tcp_recv_whole(SOCKET s, char* buf, int len)
{
	int total = 0;

	do
	{
		int ret = recv(s, buf + total, len - total, 0);
		if (ret < 1)
			return ret;
		else
			total += ret;

	} while (total < len);

	return total;
}


//int Server::sendMessage(int s, char* data, int32_t length)
//{
//	char* buffer = new char[4];
//	if (length == 4)
//	{
//		buffer = int_to_char_arr(length);
//	}
//	else if (length > 0 && length < 4)
//	{
//		char* temp[4];
//		int loadFlag = 0;
//		int difdif = 4 - length;
//		for (int i = 0; i < 4; i++)
//		{
//			for (int x = 0; x < difdif; x++)
//			{
//				int INPUT = 0;
//				temp[x] = int_to_char_arr(x);
//
//			}
//
//		}
//	}
//	else
//	{
//		return PARAMETER_ERROR;
//	}
//
//	result = send(ComSocket, (const char*)buffer, sizeof(buffer), 0);
//	if ((result == SOCKET_ERROR))
//	{
//		return SCK_ERROR;
//	}
//
//	result = sendTcpData(ComSocket, data, length);
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

char* Server::int_to_char_arr(int _int)
{
	int length = std::to_string(_int).length();
	//convert int to string
	std::string tempstring = std::to_string(_int);
	//convert string to char
	char* c = const_cast<char*>(tempstring.c_str());

	return c;
}


Server::Server() {

	ComSocket = NULL;
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	result = 0;
	UserCount = 0;
	

}
