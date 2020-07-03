#ifndef RESEARCHAPP_EXCEPTIONS_H
#define RESEARCHAPP_EXCEPTIONS_H


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

#endif //RESEARCHAPP_EXCEPTIONS_H
