#include "UserInfo.h"
#include <winnt.h>

UserInfo::UserInfo(char* _userName, char* _ipAddress, int _socket)
{
	userName = _userName;
	ipAddress = _ipAddress;
	socket = _socket;

}

UserInfo::UserInfo()
{
}

UserInfo::~UserInfo()
{

}

void UserInfo::getInfo(char* _userName, int bitsinuserName, char* _ipAddress, int bitsInIpAdress, int* _socket)
{

	//delete the inputs

	//allocate dinamic memmory to not cap buffer


	//DATI_COPPY OR MEEMCOPY the stored input to the Usernames

	memcpy(_userName, userName, sizeof(userName));
	memcpy(_ipAddress, ipAddress, sizeof(ipAddress));
	memcpy(_socket, _socket, sizeof(userName));

}
char* UserInfo::getUserName() 
{
	return userName;
}
char* UserInfo::getipAddress()
{
	return ipAddress;
}

int UserInfo::getSocket()
{
	return socket;
}