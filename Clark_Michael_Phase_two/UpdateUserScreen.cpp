#include "UpdateUserScreen.h"
#include "Authentication.h"

#include <iostream>

UpdateUserScreen::UpdateUserScreen(Authentication* a) : auth(a) {}
UpdateUserScreen::~UpdateUserScreen() {}

void UpdateUserScreen::show() {
    std::string email, oldPass, newPass;

    std::cout << "\n=== UPDATE USER ===\n";
    std::cout << "Email: ";
    std::cin >> email;

    std::cout << "Old Password: ";
    std::cin >> oldPass;

    std::cout << "New Password: ";
    std::cin >> newPass;

    if (auth->changePassword(email, oldPass, newPass)) {
        std::cout << "Updated\n";
    }
    else {
        std::cout << "Failed\n";
    }
}