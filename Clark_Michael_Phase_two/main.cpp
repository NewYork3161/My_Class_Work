#include "Server.h"

#include <thread>
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

void autoClient() {

    std::this_thread::sleep_for(std::chrono::seconds(1));

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);


    inet_pton(AF_INET, "10.0.0.154", &server.sin_addr);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cout << "AUTO CLIENT FAILED TO CONNECT\n";
        return;
    }

    std::cout << "AUTO CLIENT CONNECTED\n";

    std::string name = "AutoUser";
    uint8_t nameLen = (uint8_t)name.size();

    send(sock, (char*)&nameLen, 1, 0);
    send(sock, name.c_str(), nameLen, 0);


    while (true) {

        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::string msg = "Hello from auto client";

        // 🔥 FIXED: SEND LENGTH FIRST
        uint8_t msgLen = (uint8_t)msg.size();

        send(sock, (char*)&msgLen, 1, 0);
        send(sock, msg.c_str(), msgLen, 0);
    }
}


int main() {

    Server server(8080, 10, '/');

    if (!server.initializeServer()) {
        std::cout << "Server failed to start\n";
        return 0;
    }


    std::thread clientThread(autoClient);


    server.runServer();

    clientThread.join();

    return 0;
}