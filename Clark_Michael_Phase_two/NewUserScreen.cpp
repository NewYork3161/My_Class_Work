#include "NewUserScreen.h"
#include "Authentication.h"

#include <iostream>

NewUserScreen::NewUserScreen(Authentication* a) : auth(a) {}
NewUserScreen::~NewUserScreen() {}

void NewUserScreen::show() {
    std::string email, name, password;

    std::cout << "\n=== NEW USER ===\n";
    std::cout << "Email: ";
    std::cin >> email;

    std::cout << "Name: ";
    std::cin >> name;

    std::cout << "Password: ";
    std::cin >> password;

    if (auth->registerUser(email, name, password)) {
        std::cout << "User created\n";
    }
    else {
        std::cout << "User exists\n";
    }
}