#pragma once
#include <string>

class Database {
public:
    Database();
    ~Database();

    void init();

    bool insertUser(const std::string& email, const std::string& name, const std::string& password);
    bool verifyUser(const std::string& email, const std::string& password);
    bool updatePassword(const std::string& email, const std::string& oldPass, const std::string& newPass);

private:
    std::string filename;
    bool userExists(const std::string& email);
};