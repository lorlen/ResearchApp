#pragma once

#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include "db/Record.h"

using nlohmann::json;

class User: public Record<std::string> {
    std::string m_displayName, m_passwdHash, m_passwdSalt;
    bool m_admin{};

    std::string hashPassword(const std::string& password) const;

public:
    User() = default;
    explicit User(std::string login, std::string displayName, const std::string& password, bool isAdmin);

    const std::string& login() const;
    const std::string& displayName() const;
    bool verifyPassword(const std::string& password) const;
    bool admin() const;

    void login(std::string newLogin);
    void displayName(std::string newDisplayName);
    void password(const std::string& newPassword);
    void admin(bool isAdmin);

    friend void to_json(json& j, const User& user);
    friend void from_json(const json& j, User& user);
};
