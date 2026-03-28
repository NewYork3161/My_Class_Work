#include "Database.h"
#include <fstream>
#include <sstream>
#include <cstdio>

Database::Database() {
    filename = "users.txt";
}

Database::~Database() {}

void Database::init() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::ofstream newFile(filename);
        newFile.close();
    }
}

bool Database::userExists(const std::string& email) {
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string fileEmail;
        getline(ss, fileEmail, '|');

        if (fileEmail == email) return true;
    }

    return false;
}

bool Database::insertUser(const std::string& email,
    const std::string& name,
    const std::string& password) {

    if (userExists(email)) return false;

    std::ofstream file(filename, std::ios::app);
    file << email << "|" << name << "|" << password << "\n";

    return true;
}

bool Database::verifyUser(const std::string& email,
    const std::string& password) {

    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string fileEmail, name, filePassword;

        getline(ss, fileEmail, '|');
        getline(ss, name, '|');
        getline(ss, filePassword, '|');

        if (fileEmail == email && filePassword == password)
            return true;
    }

    return false;
}

bool Database::updatePassword(const std::string& email,
    const std::string& oldPass,
    const std::string& newPass) {

    std::ifstream file(filename);
    std::ofstream temp("temp.txt");

    std::string line;
    bool updated = false;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string fileEmail, name, filePassword;

        getline(ss, fileEmail, '|');
        getline(ss, name, '|');
        getline(ss, filePassword, '|');

        if (fileEmail == email) {
            if (filePassword != oldPass || oldPass == newPass) {
                temp << line << "\n";
            }
            else {
                temp << fileEmail << "|" << name << "|" << newPass << "\n";
                updated = true;
            }
        }
        else {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();

    std::remove(filename.c_str());
    std::rename("temp.txt", filename.c_str());

    return updated;
}