#pragma once

#include <winsock2.h>
#include <vector>
#include <string>

#include "Client.h"


class Server {
private:
    int serverPort;
    int maxCapacity;
    char commandCharacter;

    SOCKET listeningSocket;

    std::vector<Client> connectedClients;


    void acceptClient(fd_set& master);
    void handleClientData(SOCKET sock, fd_set& master);
    void removeClient(size_t index);

public:

    Server(int port, int capacity, char command);
    ~Server();


    bool initializeServer();
    void runServer();
};