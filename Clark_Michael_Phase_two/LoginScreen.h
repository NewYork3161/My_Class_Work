#pragma once
#include <string>

class Authentication;

class LoginScreen {
public:
    LoginScreen(Authentication* auth);
    ~LoginScreen();

    // returns true if login successful
    bool show();

private:
    Authentication* auth;
};