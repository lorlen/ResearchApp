#include "db/exceptions.h"


DatabaseReadProblem::DatabaseReadProblem(std::string filename, std::string msg = "Coudn't read from file")
{
    m = msg;
    f = filename;
}

DatabaseReadProblem::DatabaseReadProblem(std::string filename)
{
    m = "Coudn't read from file";
    f = filename;
}

DatabaseReadProblem::~DatabaseReadProblem()
{
}

std::string DatabaseReadProblem::what()
{
    return m + f;
}


 UserNotLogged::UserNotLogged(std::string what, std::string msg = "User is not logged while accesing: ")
 {
     w = what;
     m = msg;
 }

 UserNotLogged::UserNotLogged(std::string what)
 {
     w = what;
     m = "User is not logged while accesing: ";
 }

 UserNotLogged::~UserNotLogged()
 {
 }

 std::string UserNotLogged::what()
{
    return m + w;
}



UserNotFound::UserNotFound(int i, std::string msg = "User not found under id: ")
 {
     id = i;
     m = msg;
 }

UserNotFound::UserNotFound(int i)
 {
     id = i;
     m = "User not found under id: ";
 }

UserNotFound::~UserNotFound()
 {
 }

 std::string UserNotFound::what()
{
    return m + std::to_string(id);
}