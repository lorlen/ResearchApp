#pragma once

#include <string>

#include "numtypes.h"

struct User {
    i64 id;
    std::string login;
    std::string displayName;
    std::string passwordHash;
    std::string passwordSalt;
    bool isAdmin;

    void hashPassword(const std::string& password);
    bool verifyPassword(const std::string& password) const;
};
