#include "PromptUserApplication.h"
#include "Authentication.h"
#include "LoginScreen.h"
#include "NewUserScreen.h"
#include "UpdateUserScreen.h"
#include "MainProgram.h"  

#include <iostream>

PromptUserApplication::PromptUserApplication() {}
PromptUserApplication::~PromptUserApplication() {}

void PromptUserApplication::run() {
    int choice;

    Authentication auth;

    do {
        std::cout << "Welcome to Michael's server." << std::endl;
        std::cout << "\n=== MENU ===\n";
        std::cout << "1. New User\n";
        std::cout << "2. Login\n";
        std::cout << "3. Update User\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            NewUserScreen screen(&auth);
            screen.show();
            break;
        }
        case 2: {
            LoginScreen screen(&auth);

            if (screen.show()) {
                MainProgram app;
                app.run();
                return;
            }

            break;
        }
        case 3: {
            UpdateUserScreen screen(&auth);
            screen.show();
            break;
        }
        }

    } while (choice != 4);
}