// MultipexingLab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"Ws2_32.lib")

enum MESSAGES
{
    INVALID_INPUT,
    S_CLIENT,
    S_SERVER,


};

int type;
char* tempType;
int port;
char* tempPort;
int result;
char* IpAdress;
std::string input;


// Function Declarations
std::string returnMessage(int messageID);
int clientConnect(int port, char* ipAdress);

int main()
{
    // Complete as of 8/9/2022
    #pragma region GetType

    std::cout << "\t\t Select Type\n" << "1) Client\n" << "2) Server\n" << std::endl;
    
    std::cin >> input;
    type = atoi(input.c_str());

        #pragma endregion                 


#pragma region SetupSwitch
    switch (type)
    {
    case 1:
        //TODO: Implement Client Connecection 
        std::cout << returnMessage(S_CLIENT) << std::endl << std::endl;

        std::cout << "Specify Port: ";
        std::cin >> tempPort;
        port = (int)tempPort;
        std::cout << std::endl << "Specify Address: ";
        result = clientConnect(port, IpAdress);
        std::cout << returnMessage(result) << std::endl;



        break;
    case 2:
        //TODO: Implement Server Connection
        std::cout << returnMessage(S_SERVER) << std::endl;


        break;
    default:
        std::cout << returnMessage(INVALID_INPUT) << std::endl;
        break;
    }
#pragma endregion






    
}
int clientConnect(int port, char* ipAdress)
{

    return 0;
}

std::string returnMessage(int messageID)
{

    switch (messageID)
    {
    case 0:
        return "Invalid Input!!";
    case 1:
        return "Client Selected.\n";
    case 2:
        return "Server Selected.\n";




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
