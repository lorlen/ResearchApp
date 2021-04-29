#ifndef RESEARCHAPP_DATE_H
#define RESEARCHAPP_DATE_H


#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>

#include "numtypes.h"

#if __has_include(<QtCore/QDate>)
#include <QtCore/QDate>
#endif

using nlohmann::json;

class Date {
    u32 m_year{}, m_month{}, m_day{};

    void validate() const;
    void fromISOString(const std::string& isoString);

public:
    Date() = default;
    Date(u32 year, u32 month, u32 day);
    explicit Date(const std::string& isoString);

    u32 year() const;
    u32 month() const;
    u32 day() const;
    std::string toISOString() const;

    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator!=(const Date& lhs, const Date& rhs);
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator<=(const Date& lhs, const Date& rhs);
    friend bool operator>=(const Date& lhs, const Date& rhs);

    friend void to_json(json& j, const Date& date);
    friend void from_json(const json& j, Date& date);

#if __has_include(<QtCore/QDate>)
    Date(const QDate& qDate);
    operator QDate() const;
    Date& operator=(const QDate& qDate);
#endif
};

class InvalidDateException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};


#endif //RESEARCHAPP_DATE_H
