#pragma once
#include <string>
#include <vector>
#include "research/date.h"
#include "research/researchpoint.h"
#include <iostream>
#include <algorithm>


class Research
{
private:
    std::string researchTitle;
    uint research_ID;
    Date s_data;
    Date d_data;
    std::string state; // change 
    uint author_user_ID;
    std::vector<uint> users_ID;
    std::vector<uint> researchPoints_ID;
    std::vector<ResearchPoint*> researchPoints;

public:
    /**
    * Getter - returns Research Title
    * @returns researchTitle - string with title of a research
    * */
    std::string get_researchTitle() const;

    /**
    * Getter - returns research ID
    * @returns research_ID - uint with ID of a research
    * */
    uint get_research_ID() const;

    /**
     * Getter - returns launch Date
     * @returns s_data - launch Date of research
     * */
    Date get_start_date() const;

    /**
     * Getter - returns deadline Date
     * @returns s_data - deadline Date of research
     * */
    Date get_deadline_date() const;

    /**
     * Getter - returns state
     * @returns state - state of research true - ongoing false - ended
     * */
    std::string get_state() const;

    /**
     * Getter - returns id of author user
     * @returns author_user_ID - uint Id of author user.
     * */
    uint get_author_user() const;

    /**
     * Getter - returns vector of users' IDs
     * @returns users_ID - vector with users id
     * */
    std::vector<uint>get_users_ID() const;

    /**
     * Getter - returns vector of researchPoints' IDs
     * @returns researchPoints_ID - vector with researchPoints id
     * */
    std::vector<uint> get_researchPoints_ID() const;

    /**
     * Getter - returns researchPoint of given ID
     * @returns p - researchPoint object of given ID
     * */
    ResearchPoint* get_researchPoint(uint id) const;
    /**
     * Getter - returns vector of researchPoints objects
     * @returns researchPoints - vector of researchPoints
     * */
    std::vector<ResearchPoint*> get_researchPoints() const;

    std::vector<ResearchPoint*> get_researchPoints_sorted() ;
    /**
     * Changer - changes researchTitle, can be used by user
     * \param[in] newTitle a string argument of new researchTitle
     * */
    // change - like set, but can be changed by user
    void change_researchTitle(std::string newTitle);

    /**
     * Setter - sets research_ID
     * \param[in] id an unsigned int argument of new research_ID value
     * */
    void set_research_ID(uint id);

    /**
     * Setter - sets s_data
     * \param[in] s a Date object of new date
     * */
    void set_start_data(Date s);

    /**
     * Changer - changes d_data, can be used by user
     * \param[in] d a new endline Date object
     * */
    void change_endline_data(Date d);

    /**
     * Setter - sets state
     * \param[in] s a new state
     * */
    void set_state(std::string s);

    /**
     * Setter - sets s_data
     * \param[in] s a Date object of new date
     * */
    void set_s_date(Date s);

    /**
     * Setter - sets d_data
     * \param[in] d a new endline Date object
     * */
    void set_d_date(Date d);

    /**
     * Setter - sets researchPoints
     * \param[in] vec a new vector of ResearchPoint objects
     * */
    void set_researchPoints(std::vector<ResearchPoint*> vec);

    /**
     * Setter - sets users_ID
     * \param[in] us a new vector of users ID
     * */
    void set_users(std::vector<uint> us);

    /**
     * Setter - sets author_user_ID
     * \param[in] id a uint of author ID
     * */
    void set_author(uint id);

    /**
     * Adds new user to vector
     * \param[in] id a uint of user ID
     * */
    void add_user(uint id);

    /**
     * Deletes user of given ID from users_ID vector
     * \param[in] id a uint of user ID
     * */
    void delete_user(uint id);

    /**
     * Adds new researchPoint ID to vector
     * \param[in] id a uint of researchPoint ID
     * */
    void add_researchPoint(uint id);

    /**
     * Adds new researchPoint object to vector
     * \param[in] *p pointer of ResearchPoint
     * */
    void add_researchPoint(ResearchPoint *p);

    /**
     * Deletes reserchPoint of given ID from researchPoints_ID vector
     * \param[in] id a uint of user ID
     * */
    void delete_researchPoint(uint id);


    void operator=(Research* r);
    Research();
    Research(std::string title, Date s_d, Date d_d, std::string st, uint author_id, uint id);
    ~Research();
};
