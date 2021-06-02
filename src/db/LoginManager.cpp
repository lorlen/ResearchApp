#include "db/LoginManager.h"

#include "db/exceptions.h"
#include "db/StorageManager.h"
#include "entities/User.h"

std::optional<User> LoginManager::_currentUser = std::nullopt;

std::optional<User> LoginManager::currentUser() {
    return _currentUser;
}

std::optional<User> LoginManager::registerUser(const std::string& login, const std::string& displayName,
                                               const std::string& password, bool isAdmin) {
    using namespace sqlite_orm;

    checkAdmin();

    auto db = StorageManager::get();

    if (db.count<User>(where(c(&User::login) == login)) > 0) {
        return std::nullopt;
    }

    User user { -1, login, displayName, "", "", isAdmin };
    user.hashPassword(password);

    user.id = db.insert(user);

    return user;
}

std::optional<User> LoginManager::logIn(const std::string& login, const std::string& password) {
    using namespace sqlite_orm;

    auto user = StorageManager::get().get_all<User>(where(c(&User::login) == login));

    if (user.empty() || !user[0].verifyPassword(password)) {
        return std::nullopt;
    }

    _currentUser.emplace(user[0]);
    return user[0];
}

void LoginManager::logOut() {
    _currentUser.reset();
}

void LoginManager::checkUser() {
    if (!_currentUser.has_value()) {
        throw NotLoggedInException("User not logged in");
    }
}

void LoginManager::checkAdmin() {
    checkUser();

    if (!_currentUser->isAdmin) {
        throw InsufficientPrivilegesException("User is not an admin");
    }
}