#pragma once

#include <winsock2.h>
#include <string>

class Client {
public:
    Client(SOCKET s, const std::string& name);
    ~Client();

    SOCKET getSocket() const;
    std::string getName() const;

private:
    SOCKET clientSocket;
    std::string username;
};