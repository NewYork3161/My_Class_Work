#pragma once
#include <string>

class Authentication {
public:
    Authentication();
    ~Authentication();

    bool login(const std::string& email, const std::string& password);
    bool registerUser(const std::string& email, const std::string& name, const std::string& password);
    bool changePassword(const std::string& email, const std::string& oldPass, const std::string& newPass);
};