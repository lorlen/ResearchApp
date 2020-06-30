#include "research/date.h"
#include <iostream>

Date::Date(/* args */)
{
    #ifdef _Debug
    std::cout << "Creating date" << std::endl;
    #endif
}

Date::Date(int y, int m, int d)
{
    set_new(y, m, d);
    #ifdef _Debug
    std::cout << "Creating date" << std::endl;
    #endif
}

Date::~Date()
{
    #ifdef _Debug
    std::cout << "Destrying date" << std::endl;
    #endif
}


void Date::set_new(int y, int m, int d)
{
    // mabay raise execption 
    if (y>2030 || y < 2019) y = 2020;
    if (m>12 || m < 1) m = 1;
    if (d>31 || d < 1) d = 1;
    if(m==2) // add leap years 
    {
        if (d>28 || d < 1)
            d = 1;
    }
    dyear = y;
    dmonth = m;
    dday = d;
    #ifdef _Debug
    std::cout << "Seting new date y: " << dyear <<" m: "<< dmonth <<" d: "<< dday << std::endl;
    #endif
}

int Date::year() const
{
    return dyear;
}

int Date::month() const
{
    return dmonth;
}

int Date::day() const
{
    return dday;
}

std::string Date::get_date_format() const

{
    return std::to_string(dday) + "-" +std::to_string(dmonth) + "-" +std::to_string(dyear);
}

std::string Date::delta_time_string(Date& another_date) const
{
    int deltayear = abs(dyear - another_date.year());
    int deltam = abs(dmonth - another_date.month());
    int deltad = abs(dday - another_date.day());
    return std::to_string(deltad) + "-" +std::to_string(deltam) + "-" +std::to_string(deltayear);
}

int Date::delta_time(Date& another_date) const
{
    int deltayear = abs(dyear - another_date.year()) * 365; //thats not accurate nor complex,is it enough ? tho
    int deltam = abs(dmonth - another_date.month()) * 31; // again not accurate
    int deltad = abs(dday - another_date.day());
    return deltayear+deltam+deltad;
}

bool Date::operator<(Date& another_date) const
{
    return dyear < another_date.dyear || dmonth < another_date.dmonth || dday < another_date.dday;
}

bool Date::operator<=(Date& another_date) const
{
    return *this < another_date || *this == another_date;
}

bool Date::operator> (Date& another_date) const
{
    return dyear > another_date.dyear || dmonth > another_date.dmonth || dday > another_date.dday;
}

bool Date::operator>= (Date& another_date) const
{
    return *this > another_date || *this == another_date;
}

bool Date::operator== (Date& another_date) const
{
    return dyear == another_date.dyear && dmonth == another_date.dmonth && dday == another_date.dday;
}

std::ostream& operator<<(std::ostream& os, Date& d)
{
    os << d.get_date_format();
    return os;
}

std::istream& operator>>(std::istream& is, Date&d)
{
    //???????
}