#include "MainProgram.h"
#include "Server.h"

#include <iostream>

MainProgram::MainProgram() {}
MainProgram::~MainProgram() {}

void MainProgram::run() {

    std::cout << "\nYou logged in\n";


    int port = 4435;
    int capacity = 10;
    char cmdChar = '~';

    std::cout << "\n--- CNE Chat Server Setup ---\n";
    std::cout << "Port: " << port << "\n";
    std::cout << "Capacity: " << capacity << "\n";
    std::cout << "Command Character: " << cmdChar << "\n\n";

    Server chatServer(port, capacity, cmdChar);

    if (chatServer.initializeServer()) {
        chatServer.runServer();
    }
    else {
        std::cerr << "Critical Error: Server initialization failed.\n";
    }
}