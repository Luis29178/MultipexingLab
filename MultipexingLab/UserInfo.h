#pragma once
class UserInfo
{
public:

	char* userName;
	char* ipAddress;
	int socket;

	UserInfo(char* _userName, char* _ipAddress, int _socket);
	UserInfo();
	~UserInfo();

	char* getUserName();
	char* getipAddress();
	int getSocket();

private:
	

	// check if it works to return the values ve modifieng the memory in the addres passed in
	//void getInfo(char* _userName, int bitsinuserName, char* _ipAddress, int bitsInIpAdress, int* _socket);



};

