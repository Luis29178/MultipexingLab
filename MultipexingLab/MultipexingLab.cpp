// MultipexingLab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"Ws2_32.lib")

enum Messages
{
    INVALID_INPUT,
    S_CLIENT,
    S_SERVER,


};

int type;
std::string IpAdress;
int port;

SOCKET ComSocket;
SOCKET ListenSocket;

int main()
{
    std::cout << "\t\t Select Type\n" << "1) Client\n" << "2) Server\n" << std::endl;
    
    std::cin >> type;

    switch (type)
    {
    case 1:
        //TODO: Implement Client Connecection 
        std::cout << returnMessage(S_CLIENT) << std::endl;


        break;
    case 2:
        //TODO: Implement Server Connection
        std::cout << returnMessage(S_SERVER) << std::endl;


        break;
    default:
        std::cout << returnMessage(INVALID_INPUT) << std::endl;
        break;
    }





    
}

std::string returnMessage(int messageID)
{
    std::string errorMessage;

    switch (messageID)
    {
    case 0:
        return "Invalid Input!!";



    default:
        return "Unknwon Error";
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
