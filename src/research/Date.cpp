#include "research/Date.h"

#include <array>
#include <iomanip>
#include <sstream>

static inline bool isLeapYear(uint32_t year) {
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

static std::array<uint32_t, 12> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date(uint32_t year, uint32_t month, uint32_t day) : m_year(year), m_month(month), m_day(day) {
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
    if (sscanf(isoString.c_str(), "%4d-%2d-%2d", &m_year, &m_month, &m_day) != 3) {
        throw InvalidDateException("\"" + isoString + "\" is not a valid ISO format date");
    }
}

uint32_t Date::year() const {
    return m_year;
}

uint32_t Date::month() const {
    return m_month;
}

uint32_t Date::day() const {
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

void to_json(json& j, const Date& date) {
    j = date.toISOString();
}

void from_json(const json& j, Date& date) {
    date.fromISOString(j.get<std::string>());
}

