#include "Server.h"
#include "Message.h"

#include <WS2tcpip.h>
#include <iostream>
#include <fstream>
#include <string>

#pragma comment(lib, "ws2_32.lib")


std::string getLocalIP() {
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        return "Error";
    }

    addrinfo hints{}, * info;
    hints.ai_family = AF_INET;

    if (getaddrinfo(hostname, NULL, &hints, &info) != 0) {
        return "Error";
    }

    sockaddr_in* addr = (sockaddr_in*)info->ai_addr;
    char ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &addr->sin_addr, ip, sizeof(ip));

    freeaddrinfo(info);
    return std::string(ip);
}



Server::Server(int port, int capacity, char command)
    : serverPort(port),
    maxCapacity(capacity),
    commandCharacter(command),
    listeningSocket(INVALID_SOCKET)
{
}

Server::~Server() {
    closesocket(listeningSocket);
    WSACleanup();
}



bool Server::initializeServer() {

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return false;

    listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listeningSocket == INVALID_SOCKET) return false;

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(serverPort);
    hint.sin_addr.s_addr = INADDR_ANY;

    if (bind(listeningSocket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR) return false;
    if (listen(listeningSocket, maxCapacity) == SOCKET_ERROR) return false;

    std::cout << "\n=============================\n";
    std::cout << " Server started successfully\n";
    std::cout << " Server IP: " << getLocalIP() << "\n";
    std::cout << " Listening on port: " << serverPort << "\n";
    std::cout << "=============================\n\n";

    return true;
}



void Server::runServer() {

    fd_set master;
    FD_ZERO(&master);
    FD_SET(listeningSocket, &master);

    std::cout << "Server is now running and waiting for clients...\n";

    while (true) {

        fd_set copy = master;

        int socketCount = select(FD_SETSIZE, &copy, nullptr, nullptr, nullptr);

        if (socketCount == SOCKET_ERROR) {
            std::cerr << "select() error: " << WSAGetLastError() << "\n";
            break;
        }

        for (int i = 0; i < (int)copy.fd_count; i++) {
            SOCKET sock = copy.fd_array[i];

            if (sock == listeningSocket) {
                acceptClient(master);
            }
            else {
                handleClientData(sock, master);
            }
        }
    }
}



void Server::acceptClient(fd_set& master) {

    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);

    SOCKET client = accept(listeningSocket, (sockaddr*)&clientAddr, &clientSize);

    if (client == INVALID_SOCKET) return;

    if (connectedClients.size() >= (size_t)maxCapacity) {
        std::cout << "Connection rejected: max capacity reached.\n";
        closesocket(client);
        return;
    }

    char nameBuffer[64];

    if (Message::receiveMessage(client, nameBuffer) > 0) {

        connectedClients.push_back(Client(client, nameBuffer));
        FD_SET(client, &master);

        Message::sendMessage(client, "Welcome! Registration successful.");

        std::cout << "\nCLIENT CONNECTED: " << nameBuffer << std::endl;
        std::cout << "Active Clients: " << connectedClients.size() << "\n";
    }
    else {
        closesocket(client);
    }
}



void Server::handleClientData(SOCKET sock, fd_set& master) {

    char buffer[256];

    int bytes = Message::receiveMessage(sock, buffer);

    if (bytes <= 0) {

        for (auto it = connectedClients.begin(); it != connectedClients.end(); ++it) {
            if (it->getSocket() == sock) {

                std::cout << "User " << it->getName() << " disconnected.\n";

                FD_CLR(sock, &master);
                closesocket(sock);
                connectedClients.erase(it);
                break;
            }
        }

        return;
    }

    std::string msg = buffer;


    std::ofstream log("server.log", std::ios::app);
    log << msg << std::endl;



    if (msg == "~getlist") {

        std::string list = "Connected Users:\n";

        for (auto& client : connectedClients) {
            list += client.getName() + "\n";
        }

        Message::sendMessage(sock, list);
        return;
    }

    if (msg == "~logout") {

        std::cout << "Client requested logout\n";

        for (auto it = connectedClients.begin(); it != connectedClients.end(); ++it) {
            if (it->getSocket() == sock) {

                FD_CLR(sock, &master);
                closesocket(sock);
                connectedClients.erase(it);
                break;
            }
        }

        return;
    }



    for (auto& client : connectedClients) {
        if (client.getSocket() != sock) {
            Message::sendMessage(client.getSocket(), msg);
        }
    }

    std::cout << "Chat: " << msg << std::endl;
}


void Server::removeClient(size_t index) {
    closesocket(connectedClients[index].getSocket());
    connectedClients.erase(connectedClients.begin() + index);
}