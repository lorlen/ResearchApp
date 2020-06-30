#include <string>

class DatabaseReadProblem
{
    public:
    std::string f;
    std::string m;
    std::string what();
    DatabaseReadProblem(std::string filename);
    DatabaseReadProblem(std::string filename, std::string msg);
    ~DatabaseReadProblem();
};

class UserNotLogged
{
    public:
    std::string w;
    std::string m;
    std::string what();
    UserNotLogged(std::string what);
    UserNotLogged(std::string what, std::string msg);
    ~UserNotLogged();
};


class UserNotFound
{
    public:
    int id;
    std::string m;
    std::string what();
    UserNotFound(int id);
    UserNotFound(int id, std::string msg);
    ~UserNotFound();
};