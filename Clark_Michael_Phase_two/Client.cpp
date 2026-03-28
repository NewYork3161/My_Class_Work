#include "Client.h"



Client::Client(SOCKET s, const std::string& name)
    : clientSocket(s), username(name) {
}



Client::~Client() {
    
}



SOCKET Client::getSocket() const {
    return clientSocket;
}



std::string Client::getName() const {
    return username;
}