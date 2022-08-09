#define _CRT_SECURE_NO_WARNINGS                 // turns of deprecated warnings
#define _WINSOCK_DEPRECATED_NO_WARNINGS			 // turns of deprecated warnings for winsock



#include <winsock2.h>
#include <cstdint>
#pragma comment(lib,"Ws2_32.lib")


class PlatformBase
{
private:
	SOCKET ComSocket;
	int result;
	int sendTcpData(SOCKET skSocket, const char* data, uint16_t length);
	int reciveTcpData(SOCKET s, char* buffer, int length);
public:

	virtual int init() = 0;
	int readMessage(char* buffer, int32_t size);
	int sendMessage(char* data, int32_t length);
	virtual void stop() = 0;


};

