#pragma once
#include <string>
#include "external/json.hpp"
#include <iostream>

using json = nlohmann::json;

class User
{
private:
    static std::vector<std::string> logins;
    uint id;
    std::string login;
    std::string password;
    std::string name;
    bool level;
    std::vector<uint> attached;
    std::vector<uint> author_to; 
public:
    //static uint nextid;
    /**
     * Functions retuns string with info to verify user formated in a specific way
     * @returns stirng with info
     * */
    std::string get_credenital_string() const;
    json* get_infomation() const;
    /**
     * Returs False  - functions can be used to tell if user is an admin
     * @returns bool - False
     * */
    bool is_admin() const;
    /**
     * Getter - returns user name
     * @returns name - string with name of a user
     * */
    std::string get_name() const;
    /**
     * Getter - returns login of a user
     * @returns login -string with a login
     * */
    std::string get_login() const;
    std::string get_password() const;
    std::vector<uint> get_attached() const;
    std::vector<uint> get_authored() const;
    void set_attached(std::vector<uint> a);
    void set_authored(std::vector<uint> a);
    bool check_password(std::string pass);
    int change_password(std::string oldpass, std::string new_pass); 
    void change_login(std::string new_login); //add password
    void change_name(std::string new_name);
    void add_research(uint id); 
    uint get_id() const;

    void operator=(User* u);

    User();
    // User(std::string login, std::string password, std::string name, bool level);
    User(std::string login, std::string password, std::string name, uint id, bool level);
    ~User();
friend
    std::ostream& operator<< (std::ostream&os,User *u);
};

