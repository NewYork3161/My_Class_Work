#pragma once

class Authentication;

class UpdateUserScreen {
public:
    UpdateUserScreen(Authentication* auth);
    ~UpdateUserScreen();

    void show();

private:
    Authentication* auth;
};