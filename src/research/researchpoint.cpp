#include "research/researchpoint.h"

ResearchPoint::ResearchPoint(/* args */)
{
    order = 0;
    #ifdef _Debug
    std::cout << "Creating research point using std constructos" << std::endl;
    #endif
}

ResearchPoint::ResearchPoint(std::string title, bool is_req, uint id)
{
    order = 0;
    researchPointTitle = title;
    requiredMeasurement = is_req;
    researchPoint_ID = id;
    #ifdef _Debug
    std::cout << "Creating research  point id: " << researchPoint_ID<< " title: "<< researchPointTitle <<" req: "<< requiredMeasurement << std::endl;
    #endif
}

ResearchPoint::~ResearchPoint()
{
     #ifdef _Debug
    std::cout << "Destrying research point id: " << researchPoint_ID<< " title: "<< researchPointTitle <<" req: "<< requiredMeasurement << std::endl;
    #endif
}
uint ResearchPoint::get_researchPoint_ID() const
/**
 * Getter - returns research Point ID
 * @returns researchPoint_ID - uint with ID of a researchPoint
 * */
{
    return researchPoint_ID;
}

std::string ResearchPoint::get_researchPointTitle() const
/**
 * Getter - returns Research Point Title
 * @returns researchPointTitle - string with title of a research point
 * */
{
    return researchPointTitle;
}

bool ResearchPoint::is_requiredMeasurement() const
/**
 * Getter - returns bool
 * @returns requiredMeasurement - bool true mean that measurements are required.
 * */
{
    return requiredMeasurement;
}

std::vector<uint> ResearchPoint::get_sensors() const
/**
 * Getter - returns id of used sensors
 * @returns sensors - vector with sensors id to collect data
 * */
{
    return u_sensors;
}


bool ResearchPoint::is_checked()  const
{
    return checked;
}


uint ResearchPoint::get_order() const
{
    return order;
}

void ResearchPoint::set_order(uint o) 
{
    order = o;
}
void ResearchPoint::change_researchPointTitle(std::string newTitle)
{
    researchPointTitle = newTitle;
}

void ResearchPoint::set_required(bool r)
{
    requiredMeasurement = r;
}

bool ResearchPoint::is_sensors() const
{
    return u_sensors.empty();
}


void ResearchPoint::set_checked(bool c) 
{
    checked = c;
}

void ResearchPoint::swich_checked()
{
    checked = !checked;
}


bool ResearchPoint::operator<(ResearchPoint* r) const
{
    return order < r->get_order();
}

bool ResearchPoint::operator>(ResearchPoint* r) const
{
    return order > r->get_order();
}

bool ResearchPoint::operator<(ResearchPoint r) const
{
    return order < r.get_order();
}

bool ResearchPoint::operator>(ResearchPoint r) const
{
    return order > r.get_order();
}

void ResearchPoint::add_sensor(uint id)
{
    u_sensors.push_back(id);
}

void ResearchPoint::delete_sensor(uint id)
{
    for(std::vector<uint>::iterator i = u_sensors.begin(); i!=u_sensors.end();++i)
            {
                int ID = (*i);
                if(ID == id)
                {
                    i = u_sensors.erase(i);
                }
            }
}

void ResearchPoint::set_sensors(std::vector<uint> sens)
{
    u_sensors = sens; 
}

void ResearchPoint::set_researchPoint_ID(uint id)
{
    researchPoint_ID = id;
}