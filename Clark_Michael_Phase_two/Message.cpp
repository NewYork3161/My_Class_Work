#include "Message.h"


bool Message::sendMessage(SOCKET socket, const std::string& text) {
	if (text.length() > 255) return false;
	uint8_t len = static_cast<uint8_t>(text.length());

	if (send(socket, (char*)&len, 1, 0) <= 0) return false;


	int sent = 0;
	while (sent < (int)len) {
		int result = send(socket, text.c_str() + sent, len - sent, 0);
		if (result <= 0) return false;
		sent += result;
	}
	return true;
}


int Message::receiveMessage(SOCKET socket, char* buffer) {
	uint8_t len = 0;

	if (recv(socket, (char*)&len, 1, 0) <= 0) return -1;


	int received = 0;
	while (received < (int)len) {
		int result = recv(socket, buffer + received, len - received, 0);
		if (result <= 0) return -1;
		received += result;


	}

	buffer[len] = '\0';
	return (int)len;




}