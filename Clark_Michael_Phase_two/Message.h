#pragma once
#include <winsock2.h>
#include <string>
#include <vector>

class Message
{
public:
	static bool sendMessage(SOCKET socket, const std::string& text);
	static int  receiveMessage(SOCKET socket, char* buffer);

};

