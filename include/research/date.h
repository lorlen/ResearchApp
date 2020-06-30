#pragma once
#include <string>


class Date
{
private:
    int dyear;  // there is d in front so c++ can tell the diffrence between variable and methode
    int dmonth;
    int dday;
public:
    /**
     * Retuns string with formated date in human friendly way day-month-year
     * @returns str with date
     * */
    std::string get_date_format() const;
    /**
     * used to get year of date
     * @returns year of the date
     * */
    int year() const;
    /**
     * used to get month of date
     * @returns month of the date
     * */
    int month() const;
    /**
     * used to get day of date
     * @returns day of the date
     * */
    int day() const;
    /**
     * Set new date for object - checks given paramters and set correct date
     * @param y year of the date not higher than 2030 and not smaller than 2019 - otherwise will be set to 2019
     * @param  m  month of the date 1-12 - otherwise will be set to 1
     * @param d day of the date 1-31 for febuary 1 - 28 -  otherwise will be set to 1
     * */
    void set_new(int y, int m, int d);
    /**
     * Returns diffrence in between in string foramt - d-m-y if diffrence in day, month or year is 0 this will be returned
     * @param another_date - date to get delta
     * @returns string with time delta
     * */
    std::string delta_time_string(Date& another_date) const;
    /**
     * Returns diffrence beteen date in days
     * @param another_date - date to get delta
     * @returns int with days
     * */
    int delta_time(Date& another_date) const;
    /**
     * Used to deterimne which date is "biggeer"
     * @param another_date date to compare
     * @returns bool - true is another date is "bigger", false otherwise
     * */
    bool operator>(Date& another_date) const;
    /**
     * Used to deterimne which date is "biggeer"
     * @param another_date date to compare
     * @returns bool - true is another date is "bigger", false otherwise
     * */
    bool operator<(Date& another_date) const;
    /**
     * Used to deterimne if dates are the same.
     * @param another_date date to compare
     * @returns bool - true is dates are the same, false otherwise
     * */
    bool operator==(Date& another_date) const;
    bool operator>=(Date& another_date) const;
    bool operator<=(Date& another_date) const;

    Date(/* args */);
    /**
     * Constutor checks given paramters and set correct date by calling set_new methode
     * @param y year of the date not higher than 2030 and not smaller than 2019 - otherwise will be set to 2019
     * @param  m  month of the date 1-12 - otherwise will be set to 1
     * @param d day of the date 1-31 for febuary 1 - 28 -  otherwise will be set to 1
     * */
    Date(int y, int m, int d);
    ~Date();
    /**
     * Sents date in fromat in stream
     * @param o - ostream to put info on
     * @param d - date
     * @returns srt::ostream
     * */
friend
    std::ostream& operator <<(std::ostream& o, Date& d);
friend
    std::istream& operator>>(std::istream&o, Date& d); // not done
};

