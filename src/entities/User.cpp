#include "entities/User.h"

#include <iomanip>
#include <random>
#include <sstream>

#include <picosha2.h>

void User::hashPassword(const std::string& password) {
    auto gen = std::mt19937_64(std::random_device()());
    std::ostringstream stream;
    stream << std::setfill('0') << std::setw(sizeof(u64) * 2) << std::hex << gen();

    passwordSalt = stream.str();
    passwordHash = picosha2::hash256_hex_string(password + passwordSalt);
}

bool User::verifyPassword(const std::string& password) const {
    return picosha2::hash256_hex_string(password + passwordSalt) == passwordHash;
}
