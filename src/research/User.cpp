#include "research/User.h"

#include <iomanip>
#include <random>
#include <sstream>
#include "external/picosha2.h"

User::User(std::string login, std::string displayName, const std::string& password, bool isAdmin)
        : m_login(std::move(login)), m_displayName(std::move(displayName)), m_admin(isAdmin) {
    auto gen = std::mt19937_64(std::random_device()());
    std::ostringstream stream;
    stream << std::setfill('0') << std::setw(sizeof(uint64_t) * 2) << std::hex << gen();
    m_passwdSalt = stream.str();
    m_passwdHash = hashPassword(password);
}

std::string User::hashPassword(const std::string& password) const {
    return picosha2::hash256_hex_string(password + ":" + m_passwdSalt);
}

const std::string& User::login() const {
    return m_login;
}

const std::string& User::displayName() const {
    return m_displayName;
}

bool User::verifyPassword(const std::string& password) const {
    return m_passwdHash == hashPassword(password);
}

bool User::admin() const {
    return m_admin;
}

void User::login(std::string newLogin) {
    m_login = std::move(newLogin);
}

void User::displayName(std::string newDisplayName) {
    m_displayName = std::move(newDisplayName);
}

void User::password(const std::string& newPassword) {
    m_passwdHash = hashPassword(newPassword);
}

void User::admin(bool isAdmin) {
    m_admin = isAdmin;
}

void to_json(json& j, const User& user) {
    j = json {
            {"login", user.m_login},
            {"display_name", user.m_displayName},
            {"password_hash", user.m_passwdHash},
            {"password_salt", user.m_passwdSalt},
            {"admin", user.m_admin}
    };
}

void from_json(const json& j, User& user) {
    j.at("login").get_to(user.m_login);
    j.at("display_name").get_to(user.m_displayName);
    j.at("password_hash").get_to(user.m_passwdHash);
    j.at("password_salt").get_to(user.m_passwdSalt);
    j.at("admin").get_to(user.m_admin);
}
