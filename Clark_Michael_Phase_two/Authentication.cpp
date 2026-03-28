#include "Authentication.h"
#include "Database.h"

Authentication::Authentication() {}
Authentication::~Authentication() {}

bool Authentication::login(const std::string& email, const std::string& password) {
    Database db;
    return db.verifyUser(email, password);
}

bool Authentication::registerUser(const std::string& email,
    const std::string& name,
    const std::string& password) {
    Database db;
    return db.insertUser(email, name, password);
}

bool Authentication::changePassword(const std::string& email,
    const std::string& oldPass,
    const std::string& newPass) {
    Database db;
    return db.updatePassword(email, oldPass, newPass);
}