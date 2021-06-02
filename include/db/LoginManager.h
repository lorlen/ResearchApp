#pragma once

#include <optional>

#include "entities/User.h"

class LoginManager {
    static std::optional<User> _currentUser;

public:
    static std::optional<User> currentUser();
    static std::optional<User> registerUser(const std::string& login, const std::string& displayName,
                      const std::string& password, bool isAdmin = false);
    static std::optional<User> logIn(const std::string& login, const std::string& password);
    static void logOut();
    static void checkUser();
    static void checkAdmin();

    LoginManager() = delete;
};
