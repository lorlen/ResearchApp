#pragma once
#include "external/json.hpp"
#include "db/user.h"
#include <vector>
#include <map>
#include <fstream>
#include "db/cipher.h"
#include "external/sha256.h"
#include <set>
#include <iostream>
#include "db/exceptions.h"
#include "research/research.h"
#include "research/date.h"
#include "research/researchpoint.h"
#include "research/sensor.h"

using json = nlohmann::json;

/**
 * Databes class - handles files , operations and storing objects
 *
 * Codes of problems:
 * -1 - not an admin
 *  - 2 - not unique login
 *  - 3 - user not found
 * -4
 * -5 - unsuccesful login attempt
 * - 44- not logged in
 * */
class Database
{
private:
    //// next ids for items 
    uint next_user_id = 0;
    uint next_research_id = 0;
    uint next_research_point_id = 0;
    uint next_sensor_id = 0;
    //// amounts of items
    uint users_amount = 0;
    uint sensors_amount = 0;
    uint research_amount = 0;
    uint reserach_point_amount = 0;
    //// names of files with information
    std::string ufilename = "users.json";
    std::string rfilename = "research.json";
    std::string sfilename = "sensors.json";
    ///
    json users_json;
    json research_json;
    json sensors_json;
    ///
    std::vector<json*> research_jsons;
    /// 
    std::set<std::string> logins;
    std::map<uint, User*> users;
    std::map<uint, Research*> researchs;
    std::map<uint, Sensor*> sensors;
    ///
    User* currently_logged = nullptr;
    ///
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz"; // ABCDEFGHIJKLMNOPQRSTUVWXYZ
    std::string key = "supertajnykeywhichcanbeundersoodbynarrowamountofrobots";
    Cipher cipher;
    ////////////////////////////////////////////
    /**
    * Creates files and set everything up
    * @returns nothing
     * */
    void first_run(); //1
    /**
     * Save all infromations from filesanmes and id to main fila
     * Then saves all objects to files
     *@returns Nothing
    * */
    void shutdown(); //1

    ///
    /**
     * Loads users from given json and inserts them into map of users (id, poiter ot object)
     * User Data gets decrypted
     * @param data - json with users
     * */
    void load_users(json& data); //1
    /**
     * Saves all users, than moves data from json oject to actual file
     * */
    void save_users(); //1
    void save_user(uint id); //1
    /**
     * Saves given user to a file and encrypts user data
     * Data is stored in json object not in file
     * @param U Pointer to the user
     * */
    void save_user(User* u); //1

    /**
     * Loads researchs and research poites together
     * Gets filemanes form json then opens evertfiles and gets date
     * @param data - json with names of files with research
     * */
    void load_researchs(json& data);
    /**
     * Loads researchs and research poites together
     * Gets filemanes form json then opens evertfiles and gets date
     * */
    void save_researchs();
    /**
     * Loads sensors and inserts them into map
     * @param data - json with sensors
     * */
    void load_sensors(json data);
    /**
     * Saves senors to a file(sensors.json)
     * @returns nothing
     * */
    void save_sensors();
    //////////////////////////////////

    /**
     * Creates user with given level and does some checks
     * @param login - login of the user
     * @param password - password of the user - will be hased
     * @param name  - name of the user
     * @returns - id of the user if operations was succeful otherwise code of error
     * */
    int add_u_inner(std::string login, std::string password, std::string name, bool level); //1
    int log_out(uint id);   //1
    int log_out(User* u);   //

    /**
     * Split text to two parts seperated by spplitter
     * @param text - text to split
     * @param sppliter -  sppliter in text
     * @returns vector with string splitted
     * */
    std::vector<std::string>* split(std::string text,char splitter);
public:
    uint get_next_point_id();
    User* get_currently_loged();
    
    ///         User
    /**
     * Checks if login and password are correct and loges in
     * @param login - login of the user
     * @param password - password of the user - will be hased
     * @returns - id of the user if operations was succeful otherwise code of error
     * */
    int log_in(std::string login, std::string password);
    int log_out();

    /**
     * Returns name of a user with that id
     * @param id - id of user
     * @returns user's name
     * */
    std::string get_user_name(uint id) const;
    /**
     * Returns pointet to user with id
     * @param id - id of user
     * @returns pointer to a user
     * */
    User* get_user(uint id) const;
    /**
     * Returns vector with pairs where first is id of user, second is user name
     * @returns vector
     * */
    std::vector<std::pair<uint, std::string>> get_users() const;
    /**
     * Returns vector with pointers to all loaded users
     * @returns vector
     * */
    std::vector<User*> get_users_pointers() const;
    /**
     * Creates normal user
     * @param login - login of the user
     * @param password - password of the user - will be hased
     * @param name  - name of the user
     * @returns - id of the user if operations was succeful otherwise code of error
     * */
    int add_user(std::string login, std::string password, std::string name); //1
    /**
     * Creates admin user
     * @param login - login of the user
     * @param password - password of the user - will be hased
     * @param name  - name of the user
     * @returns - id of the user if operations was succeful otherwise code of error
     * */
    int add_admin(std::string login, std::string password, std::string name); //1

    /**
     * Returns true  is loged is an admin
     * @returns true - admin, false - not admin
     * */
    bool is_admin(); //1
    /**
     * Returns ture is user with id is an admin, false other wise
     * @param id user's id - to check
     * @returns  true - admin, false - not admin
     * */
    bool is_admin(uint id); //
    /**
     * changes users under id, to data from poitrer user
     * @param id - Id of user to change
     * @param u - pointer to the other user
     * @returns code of succes or error
     * */
    int modify_user(uint id, User* u);
    /**
     * Changes login of user with given id
     * @param id -id of user
     * @param new_login - new_login
     * @returns code of error of or 0 is succes
     * */
    int modify_user_login(uint id, std::string new_login);
    /**
     * Changes name of user with given id
     * @param id -id of user
     * @param new_login - new_name
     * @returns code of error of or 0 is succes
     * */
    int modify_user_name(uint id, std::string  new_name);
    /**
     * Changes  password of a user with given id;
     * @param id -id of user
     * @param old_password - old password
     * @param new_password - new_password
     * @returns code of error of or 0 is succes
     * */
    int modify_user_password(uint id, std::string old_pasword, std::string new_password);
    /**
     * changes password of currently logged user
     * @param new_password - string with new password
     * @param old_password - string with old password
     * */
    int change_password(std::string old_pasword, std::string new_password); //1
    /**
     * changes login of currentlu logged user
     * @param new_name - string with new login
     * */
    void change_login(std::string new_login); //1
    /**
     * changes name of currentlu logged user
     * @param new_name - string with new name
     * */
    void change_name(std::string new_name); //1
    /**
     * Remoes user with given id
     * @param id - id of user to delete
     * @returns code of succes/error
     * */
    int remove_user(uint id); //1
    /**
     * Removes users under pointer
     * @param u pointer to user
     * @returns code of succes/error
     * */
    int remove_user(User* u); //1
    ////////////Research
    /**
     * Returns pointer to research
     * @param id of research
     * @returns pointer to research
     * */
    Research* get_research(uint id) const;
    /**
     * Add research to dataabase
     * @param r pointet to research to add
     * @returns id to users or code of error
     * */
    int add_research(Research* r); // jako user brany currently loged  // remove this ?????????????
    /**
     * Add research to dataabase
     * @param title
     * @param s_d - start date of research
     * @param d_d - deadline date of resarech
     * @param st - current sate of reesaech
     * @param author_id
     * @returns id to users or code of error
     * */
    int add_research(std::string title, Date s_d, Date d_d, std::string st, uint author_id);
    /**
     * Add research to dataabase, assumes that author is currently logged
     * @param title
     * @param s_d - start date of research
     * @param d_d - deadline date of resarech
     * @param st - current sate of reesaech
     * @returns id to users or code of error
     * */
    int add_research(std::string title, Date s_d, Date d_d, std::string st);//
    /**
     * Removes research with given id
     * @param id - id of reseach
     * @returns code of succes(0)/error
     * */
    int remove_research(uint id);
    /**
     * Modifies research's
     * @param id - id to the research to  modify
     * @param
     * @returns code of succces(0)/error
     * */
    int modify_research(uint id, Research *r);//
    /**
     * Modifies research's title
     * @param id - id to the research to modify
     * @param title - research's title
     * @returns code of succces(0)/error
     * */
    int modify_research_title(uint id, std::string title);//
    /**
     * Modifies research's start date
     * @param id - id to the research to  modify
     * @param s_d - start date
     * @returns code of succces(0)/error
     * */
    int modify_research_start_date(uint id, Date s_d);//
    /**
     * Modifies research's deadline date
     * @param id - id to the research to  modify
     * @param d_d deadline date
     * @returns code of succces(0)/error
     * */
    int modify_research_end_date(uint id, Date d_d);//
    /**
     * Modifies research's state
     * @param id - id to the research to  modify
     * @param state - new state
     * @returns code of succces(0)/error
     * */
    int modify_research_state(uint id, std::string state);//
    /**
     * Getter
     * @param id research's id
     * @returns research's title
     * */
    std::string get_research_title(uint id) const; //
    /**
     * Getter
     * @param id research's id
     * @returns research's start date
     * */
    Date get_research_start_date(uint id) const;//
    /**
     * Getter
     * @param id research's id
     * @returns research's  dead line date
     * */
    Date get_research_end_date(uint id) const;//
    /**
     * Getter
     * @param id research's id
     * @returns research's state
     * */
    std::string get_research_state(uint id) const;//
    /**
     * Getter
     * @param id research's id
     * @returns vector with users
     * */
    std::vector<uint> get_research_users(uint id) const;
    /**
     * Getter
     * @param id research's id
     * @returns research's authoer
     * */
    uint get_research_author(uint id) const;
    /**
     * Getter
     * @param id research's id
     * @returns vector with research pointers
     * */
    std::vector<ResearchPoint*> get_research_points_pointers(uint id) const;
    /**
    * Getter - for sorted points
    * @param id research's id
    * @returns vector with research pointers - sorted
    * */
    std::vector<ResearchPoint*> get_research_points_pointers_sorted(uint id);
    /**
     * Getter
     * @param id research's id
     * @returns vector with pairs where first is id, second -point's title
     * */
    std::vector<std::pair<uint, std::string>> get_research_points(uint id) const;
    /**
     * Getter
     * @param id research's id
     * @returns vector with pairs where first is id, second -point's title (sorted)
     * */
    std::vector<std::pair<uint, std::string>> get_research_points_sorted(uint id) ;
    /**
     * Getter
     * @param r_id research's id
     * @param p_id research point's id
     * @returns vector with ponters to sensors attached to the point
     * */
    std::vector<Sensor*> get_research_point_sensors_pointers(uint r_id, uint p_id) const;
    /**
     * Getter
     * @param r_id research's id
     * @param p_id research point's id
     * @returns vector with pairs where first is id, second -sensor's title
     * */
    std::vector<std::pair<uint, std::string>> get_research_point_sensors(uint r_id, uint p_id) const;
    //int modify_research(uint id, );

    /**
     * Add new resaech point to research with given id
     * @param research_id research to add point to
     * @param title point's title
     * @param is_req, ture if required, false otherwise
     * @returns point's is or error code
     * */
    int add_research_point(uint research_id, std::string title, bool is_req);//
    /**
     * Removes pont
     * @param research_id research to add point to
     * @param title point's title
     * @param is_req, ture if required, false otherwise
     * @returns 0 if succesful code of error otherwise
     * */
    int remove_research_point(uint research_id, uint point_id);//
    /**
     * Modifies points's with data from other point
     * @param research_id
     * @param point_id
     * @param p pointer to point to get data from
     * @return code of succes(0) of error
     * */
    int modify_research_point(uint research_id, uint point_id, ResearchPoint* p);//
    /**
    * Modifies points's title
    * @param research_id
    * @param point_id - id of resaech point's attache to research_id
    * @param title - new title
    * @return code of succes(0) of error
    * */
    int modify_research_point_title(uint research_id, uint point_id, std::string title);//
    /**
    * Modifies points's req
    * @param research_id
    * @param point_id - id of resaech point's attache to research_id
    * @param req  - new req
    * @return code of succes(0) of error
    * */
    int modify_research_req(uint research_id, uint point_id, bool req);//
    /**
     * Switches checkbox on point with the id
     * @param research_id - id of research with point
     * @param point_id - id of research
     * @returns 0 or code of error
     * */
    int change_checkbox(uint research_id, uint point_id); //
    /**
     * Setter
     * @param research_id - id of research with point
     * @param point_id - id of research
     * @param checked - new checkbox value
     * @returns 0 or code of error
     * */
    int set_checkbox(uint research_id, uint point_id, bool checked); //
    /**
     * Creates new sensor and attaches it to a point with given id
     * @param research_id  - research with point
     * @param researchPoint_id - point to atttch sensor to
     * @param lable sensor's lable
     * @param type sensor's type
     * @param unit sensor's unit
     * @returns 0 if succes or  error code
     * */
    int add_sensor_research(uint research_id, uint researchPoint_id, std::string lable, std::string type, std::string unit);//
    /**
     * Attaches sensor to a point with given id
     * @param research_id  - research with point
     * @param researchPoint_id - point to atttch sensor to
     * @param sensor_id - sesor to attch
     * @returns 0 if succes or  error code
     * */
    int add_sensor_research(uint research_id, uint researchPoint_id ,uint sensor_id);//
    /**
     * Removes attachment form point does not deletes sensor
     * @param research_id  - research with point
     * @param researchPoint_id - point with sensor
     * @param sensor_id - sensor to remove
     * @returns 0 if succes or  error code
     * */
    int remove_sensor_research(uint research_id, uint researchPoint_id ,uint sensor_id);//
    /**
     * Getter - find researchs with given stard date
     * @param s_d start date to find
     * @returns vector with pointer to researches
     * */
    std::vector<Research*> get_researchs_s_d_pointers(Date s_d) const;
    /**
     * Getter - find researchs with given deadline date
     * @param d_d deadline date to find
     * @returns vector with pointer to researches
     * */
    std::vector<Research*> get_researchs_d_d_pointers(Date d_d) const;
    /**
     * Getter - find researchs with given  user attached
     * @param user_id user attached to research
     * @returns vector with pointer to researches
     * */
    std::vector<Research*> get_researchs_user_pointers(uint user_id) const;
    /**
     * Getter - find researchs witch has been made by given user
     * @param user_id author id
     * @returns vector with pointer to researches
     * */
    std::vector<Research*> get_researchs_author_pointers(uint user_id) const;

    /**
     * Getter - find researchs with given stard date
     * @param s_d start date to find
     * @returns vector with pairs where fist is id - second is title
     * */
    std::vector<std::pair<uint, std::string>> get_researchs_s_d(Date s_d) const;
    /**
     * Getter - find researchs with given deadline date
     * @param d_d deadline date to find
     * @returns vector with pairs where fist is id - second is title
     * */
    std::vector<std::pair<uint, std::string>> get_researchs_d_d(Date d_d) const;
    /**
    * Getter - find researchs with given  user attached
    * @param user_id user attached to research
    * @returns vector with pairs where fist is id - second is title
    * */
    std::vector<std::pair<uint, std::string>> get_researchs_user(uint user_id) const;
    /**
     * Getter - find researchs witch has been made by given user
     * @param user_id author id
     * @returns vector with pairs where fist is id - second is title
     * */
    std::vector<std::pair<uint, std::string>> get_researchs_author(uint user_id) const;

    // //// sensors
    /**
     * Add senors to databse, retuns id if succesfull
     * @param lable sensor's lable
     * @param type sensor's type
     * @param unit sensor's unit
     * @returns id of error code
     * */
    int add_sensor(std::string lable, std::string type, std::string unit);//
    /**
     * Deletes sensor from data base, does not remove attachmet to this sensor from points
     * @param id id of sensor to remove
     * @returns 0 if succes to error code
     * */
    int delete_sensor(uint id);//
    /**
     * Modifies sensor's lable
     * @param id sensor's id to modify
     * @param lable - new lable
     * @returns 0 if succes or error code
     * */
    int modify_sensor_lable(uint id, std::string lable);//
    /**
     * Modifies sensor's type
     * @param id sensor's id to modify
     * @param type new type
     * @returns 0 if succes or error code
     * */
    int modify_sensor_type(uint id, std::string type);//
    /**
     * Modifies sensor's unit
     * @param id sensor's id to modify
     * @param unit new unit
     * @returns 0 if succes or error code
     * */
    int modify_sensor_unit(uint id, std::string unit);//

    Sensor* get_sensor(uint id) const;
    std::vector<Sensor*> get_sensors_pointers() const;
    std::vector<std::pair<uint, std::string>> get_sensors() const;


    /**
     * Sort resaech points with id , ascesnding
     * @param id reasech's id
     * */
    void sort_research_points(uint id);
    template < class T>
    bool in_vector(std::vector<T>  &vec, T  element) const
    {
        auto it = std::find(vec.begin(), vec.end(), element);

        if (it != vec.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // ///////////////////////////////////////////////////

    /**
    * Constructor  - load all iformations and objects from files, if program runs for the first time
    * All files are created and configured
    * */
    Database();
    /**
     * Saves all files and infomartions into files, then cleans up
     * */
    ~Database();
};
