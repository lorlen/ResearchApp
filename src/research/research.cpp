#include "research/research.h"

Research::Research(/* args */)
{

}

Research::Research(std::string title, Date s_d, Date e_d, std::string st, uint author_id, uint id)
{
    researchTitle = title;
    s_data = s_d;
    d_data = e_d;
    state = st;
    author_user_ID = author_id;
    research_ID = id;
    #ifdef _Debug
    std::cout << "Creating research id: " << id<< " title: "<< researchTitle <<" author: "<< author_user_ID << std::endl;
    #endif
}

Research::~Research()
{
    for(auto p: researchPoints)
        delete p;
    #ifdef _Debug
    std::cout << "Destroying research id: " << research_ID<< " title: "<< researchTitle <<" author: "<< author_user_ID << std::endl;
    #endif
}

std::string Research::get_researchTitle() const
/**
 * Getter - returns Research Title
 * @returns researchTitle - string with title of a research
 * */
{
    return researchTitle;
}

uint Research::get_research_ID() const
/**
 * Getter - returns research ID
 * @returns research_ID - uint with ID of a research
 * */
{
    return research_ID;
}

Date Research::get_start_date() const
/**
 * Getter - returns launch Date
 * @returns s_data - launch Date of research
 * */
{
    return s_data;
}

Date Research::get_deadline_date() const
/**
 * Getter - returns deadline Date
 * @returns s_data - deadline Date of research
 * */
{
    return d_data;
}

std::string Research::get_state() const
/**
 * Getter - returns state
 * @returns state - state of research true - ongoing false - ended
 * */
{
    return state;
}


uint Research::get_author_user() const
/**
 * Getter - returns id of author user
 * @returns author_user_ID - uint Id of author user.
 * */
{
    return author_user_ID;
}

std::vector<uint> Research::get_users_ID() const
/**
 * Getter - returns vector of users' IDs
 * @returns users_ID - vector with users id
 * */
{
    return users_ID;
}

std::vector<uint> Research::get_researchPoints_ID() const
/**
 * Getter - returns vector of researchPoints' IDs
 * @returns researchPoints_ID - vector with researchPoints id
 * */
{
    return researchPoints_ID;
}

void Research::change_researchTitle(std::string newTitle)
{
    researchTitle = newTitle;
}

void Research::set_research_ID(uint id)
{
    research_ID = id;
}

void Research::set_start_data(Date s)
{
    s_data = s;
}

void Research::change_endline_data(Date d)
{
    d_data = d;
}

void Research::add_user(uint id)
{
    users_ID.push_back(id);
}

void Research::delete_user(uint id)
{
    for(std::vector<uint>::iterator i = users_ID.begin(); i!=users_ID.end();++i)
            {
                int ID = (*i);
                if(ID == id)
                {
                    i = users_ID.erase(i);
                }
            }
}

void Research::add_researchPoint(uint id)
{
    users_ID.push_back(id);
}

void Research::delete_researchPoint(uint id)
{
    int index = 0;
    for(auto p : researchPoints)
            {
                if(p->get_researchPoint_ID() == id)
                {
                    delete p;
                    researchPoints.erase(researchPoints.begin()+index);
                }
                ++index;
            }
}

void Research::set_state(std::string s)
{
    state = s;
}

void Research::set_users(std::vector<uint> us)
{
    users_ID = us;
}

void Research::set_researchPoints(std::vector<ResearchPoint*> vec)
{
    int found = 0;
    for(auto p: researchPoints)
    {
        for(auto p2:vec)
        {
            if( p2->get_researchPoint_ID() == p->get_researchPoint_ID())
            {
                found = 1;
            }
        }
        if(found == 0)
        { 
            delete p;
        }
        found = 0;
    }
    researchPoints = vec;
}

std::vector<ResearchPoint*>  Research::get_researchPoints() const
{
    return researchPoints;
}

std::vector<ResearchPoint*>  Research::get_researchPoints_sorted() 
{
    std::sort(researchPoints.begin(), researchPoints.end(), [](ResearchPoint* a, ResearchPoint* b) { return (*a < *b); });
    return researchPoints;
}

void Research::add_researchPoint(ResearchPoint *p)
{
    researchPoints.push_back(p);
}

void Research::set_s_date(Date s)
{
    s_data = s;
}

void Research::set_d_date(Date d)
{
    d_data = d;
}

void Research::set_author(uint id)
{
    author_user_ID = id;
}

ResearchPoint* Research::get_researchPoint(uint id) const
{
    for(auto p: researchPoints)
    {
        if(p->get_researchPoint_ID() == id)
            return p;
    }
}

void Research::operator=(Research *r)
{
    researchTitle = r->get_researchTitle();
    research_ID = r->get_research_ID();
    s_data = r->get_start_date();
    d_data = r->get_deadline_date();
    state = r->get_state();
    author_user_ID = r->get_author_user();
    users_ID = r->get_users_ID();
    researchPoints = r->get_researchPoints();
}