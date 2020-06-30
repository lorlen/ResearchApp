#include "db/user.h"

User::User(/* args */)
{
}

// User::User(std::string loginn, std::string passwordd, std::string namee, bool levell = false)
// {
//     login = loginn;
//     password = passwordd;
//     name = namee;
//     level = levell;
//     //id = User::nextid;
//     //User::nextid++;
// }

User::User(std::string loginn, std::string passwordd, std::string namee, uint idd, bool levell = false)
{
    login = loginn;
    password = passwordd;
    name = namee;
    id = idd;
    level = levell;
    #ifdef _Debug
    std::cout << "Creating user id: " << id<< " name: "<< name <<" login: "<< login << std::endl;
    #endif
}

User::~User()
{
        #ifdef _Debug
        std::cout << "Destroying user id: " << id<< " name: "<< name <<" login: "<< login << std::endl;
        #endif
}

std::string User::get_name() const
{
    return name;
}

std::string User::get_login() const
{
    return login;
}

bool User::is_admin() const
{
    return level;
}

std::string User::get_credenital_string() const
{
    return  login + ":" + password;
}

std::vector<uint> User::get_attached() const
{
    return attached;
}

void User::set_attached(std::vector<uint> a)
{
    attached = a;
}

std::vector<uint> User::get_authored() const
{
    return author_to;
}

void User::set_authored(std::vector<uint> a)
{
    author_to = a;
}


void User::operator=(User *u)
{
    login = u->get_login();
    name = u->get_name();
    id = u->get_id();
    password = u->get_password();
    attached = u->get_attached();
    author_to = u->get_authored();
    level = u->is_admin();
}

void User::change_login(std::string new_login)
{
    login = new_login;
}

int User::change_password(std::string old, std::string new_passwrord)
{
    if(old == password){
    #ifdef _Debug
        std::cout << "current password: " <<password << "new pass : " << new_passwrord << std::endl; 
    #endif
        password = new_passwrord;
    #ifdef _Debug
        std::cout << "changing password to: " << new_passwrord << "old: " << old << std::endl; 
    #endif
        return 0;
    }
    #ifdef _Debug
        std::cout << "WRONG PASSWORD: current password: " <<password<< "new pass : " << new_passwrord << std::endl; 
    #endif
    return -1;
}

bool User::check_password(std::string pass)
{
    return pass == password;
}

void User::change_name(std::string new_name)
{
    name = new_name;
}

uint User::get_id() const
{
    return id;
}

std::string User::get_password() const
{
    return password;
}

std::ostream& operator<< (std::ostream&os,User *u)
{
    os << "id" << u->get_id()<< " name " << u->get_name();
    return os;
}