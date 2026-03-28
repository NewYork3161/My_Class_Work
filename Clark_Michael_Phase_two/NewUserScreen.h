#pragma once

class Authentication;

class NewUserScreen {
public:
    NewUserScreen(Authentication* auth);
    ~NewUserScreen();

    void show();

private:
    Authentication* auth;
};