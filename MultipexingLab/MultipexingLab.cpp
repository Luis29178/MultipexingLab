// MultipexingLab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"Ws2_32.lib")

// Overides warning 4996 call refering to unsafe copying of user inputs
#pragma warning(disable  : 4996)

#include "MessageEnum.h"
#include "Client.h"
#include "Server.h"

int type;
int port;
int result;
char* IpAdress;
std::string input;



#pragma region Function Declaration Zone 
std::string returnMessage(int messageID);
std::string CallInput();

char* StringToChar_arr(std::string convString);
int clientConnect(int port, char* ipAdress);
int clientRcv(int port, char* ipAdress);
int serverConnect(int port, char* ipAdress);
int StringToInt(std::string convString);



#pragma endregion

Client _client;
Server _server;
int main()
{   
    WSADATA wsadata;
    WSAStartup(WINSOCK_VERSION, &wsadata);


    // Complete as of 8/9/2022
    #pragma region GetType

    std::cout << "\t\t Select Type\n" << "1) Client\n" << "2) Server\n" << std::endl;
    input = CallInput();
    type = StringToInt(input);

        #pragma endregion                 

    // Complete as of 8/11/2022
    #pragma region SetupSwitch
    switch (type)
    {
    case 1:
        //TODO: Implement Client Connecection 
        std::cout << returnMessage(S_CLIENT) << std::endl << std::endl;

        std::cout << "Specify Port: ";
        input = CallInput();
        port = StringToInt(input);


        std::cout << std::endl << "Specify Address: ";
        input = CallInput();
        IpAdress = StringToChar_arr(input);


        result = clientConnect(port, IpAdress);
        std::cout << returnMessage(result) << std::endl;

        

        break;
    case 2:
        //TODO: Implement Server Connection
        std::cout << returnMessage(S_SERVER) << std::endl;

        std::cout << "Specify Port: ";
        input = CallInput();
        port = StringToInt(input);


        std::cout << std::endl << "Specify Address: ";
        input = CallInput();
        IpAdress = StringToChar_arr(input);

        result = serverConnect(port, IpAdress);
        std::cout << returnMessage(result) << std::endl;

        while (true)
        {
            clientRcv(port, IpAdress);
            break;
        }

        break;
    default:
        std::cout << returnMessage(INVALID_INPUT) << std::endl;
        break;
    }
    #pragma endregion


  
#pragma endregion


    
}

int clientConnect(int port, char* ipAdress)
{
    _client = Client();
    return _client.ConnectService(port, IpAdress);
}
int clientRcv(int port, char* ipAdress)
{
    
    return _client.readMessage();

}
int serverConnect(int port, char* ipAdress)
{
    _server = Server();
    return _server.ConnectService(port, IpAdress);
}

std::string returnMessage(int messageID)
{

    switch (messageID)
    {
    case INVALID_INPUT:
        return "\nInvalid Input!!\n";
    case S_CLIENT:
        return "\nClient Selected.\n";
    case S_SERVER:
        return "\nServer Selected.\n";
    case SUCCESS:
        return "\nSuccess!\n";
    case MESSAGE_ERROR:
        return "\nMessage Failed!\n";
    case PARAMETER_ERROR:
        return "\nOutside of Parameters!\n";
    case SCK_ERROR:
        return "\nSocket Error!\n";
    case INVAL_SOCKET:
        return "\nInvalid Socket!\n";


    default:
        return "Unknwon Error";
    }

}
char* StringToChar_arr(std::string convString)
{
    int len = (int)convString.length();
    char* Char_arr = new char[len + 1];
    strcpy(Char_arr, convString.c_str());
    return Char_arr;
}
int StringToInt(std::string ConvString)
{

    return atoi(ConvString.c_str());

}
std::string CallInput()
{
    std::string x;
    std::cin >> x ;
    return  x;
}
