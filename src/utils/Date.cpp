#include "utils/Date.h"

#include <array>
#include <iomanip>
#include <sstream>

#include "numtypes.h"

static inline bool isLeapYear(u32 year) {
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

static std::array<u32, 12> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date(u32 year, u32 month, u32 day) : m_year(year), m_month(month), m_day(day) {
    validate();
}

Date::Date(const std::string& isoString) {
    fromISOString(isoString);
    validate();
}

void Date::validate() const {
    if (m_year == 0 || m_month == 0 || m_day == 0 || m_month > 12
        || m_day > daysInMonth[m_month] + size_t(m_month == 2 && isLeapYear(m_year))) {
        std::ostringstream stream;
        stream << "Date values fall out of allowed range: year=" << m_year
               << ", month=" << m_month
               << ", day=" << m_day;
        throw InvalidDateException(stream.str());
    }
}

void Date::fromISOString(const std::string& isoString) {
    std::istringstream stream(isoString);
    std::tm time{};
    stream >> std::get_time(&time, "%Y-%m-%d");

    if (stream.fail()) {
        throw InvalidDateException("\"" + isoString + "\" is not a valid ISO format date");
    }

    m_year = time.tm_year + 1900;
    m_month = time.tm_mon + 1;
    m_day = time.tm_mday;
}

u32 Date::year() const {
    return m_year;
}

u32 Date::month() const {
    return m_month;
}

u32 Date::day() const {
    return m_day;
}

std::string Date::toISOString() const {
    std::ostringstream stream;
    stream << std::setfill('0')
           << std::setw(4) << m_year << '-'
           << std::setw(2) << m_month << '-'
           << std::setw(2) << m_day;
    return stream.str();
}

Date::operator std::string() const {
    return toISOString();
}

#if __has_include(<QtCore/QDate>)
Date::Date(const QDate& qDate) : m_year(qDate.year()), m_month(qDate.month()), m_day(qDate.day()) {
    validate();
}

Date::operator QDate() const {
    return QDate(m_year, m_month, m_day);
}

Date& Date::operator=(const QDate& qDate) {
    m_year = qDate.year();
    m_month = qDate.month();
    m_day = qDate.day();
    return *this;
}
#endif

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.m_year == rhs.m_year && lhs.m_month == rhs.m_month && lhs.m_day == rhs.m_day;
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(rhs == lhs);
}

bool operator<(const Date& lhs, const Date& rhs) {
    return lhs.m_year < rhs.m_year || lhs.m_month < rhs.m_month || lhs.m_day < rhs.m_day;
}

bool operator>(const Date& lhs, const Date& rhs) {
    return rhs < lhs;
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

