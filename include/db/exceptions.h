#pragma once

#include <stdexcept>

class DatabaseException: public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class UserNotFoundException: public DatabaseException {
    using DatabaseException::DatabaseException;
};

class NotLoggedInException: public DatabaseException {
    using DatabaseException::DatabaseException;
};

class InsufficientPrivilegesException: public DatabaseException {
    using DatabaseException::DatabaseException;
};
