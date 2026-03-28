#include "LoginScreen.h"
#include "Authentication.h"

#include <iostream>

LoginScreen::LoginScreen(Authentication* a)
    : auth(a) {
}

LoginScreen::~LoginScreen() {}

bool LoginScreen::show() {
    std::string email, password;

    std::cout << "\n=== WELCOME TO MICHAEL'S SERVER ===\n";
    std::cout << "\n=== LOGIN ===\n";

    std::cout << "Email: ";
    std::cin >> email;

    std::cout << "Password: ";
    std::cin >> password;

    if (auth->login(email, password)) {
        std::cout << "Login successful\n";
        return true;
    }
    else {
        std::cout << "Invalid credentials\n";
        return false;
    }
}