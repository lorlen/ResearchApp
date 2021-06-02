#pragma once

#include <stdexcept>
#include <string>
#include <sqlite_orm/sqlite_orm.h>

#include "numtypes.h"

#if __has_include(<QtCore/QDate>)
#include <QtCore/QDate>
#endif

class Date {
    u32 m_year{}, m_month{}, m_day{};

    void validate() const;
    void fromISOString(const std::string& isoString);

public:
    Date() = default;
    Date(u32 year, u32 month, u32 day);
    explicit Date(const std::string& isoString);

    [[nodiscard]] u32 year() const;
    [[nodiscard]] u32 month() const;
    [[nodiscard]] u32 day() const;
    [[nodiscard]] std::string toISOString() const;

    explicit operator std::string() const;

    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator!=(const Date& lhs, const Date& rhs);
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator<=(const Date& lhs, const Date& rhs);
    friend bool operator>=(const Date& lhs, const Date& rhs);

#if __has_include(<QtCore/QDate>)
    Date(const QDate& qDate);
    operator QDate() const;
    Date& operator=(const QDate& qDate);
#endif
};

class InvalidDateException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

namespace sqlite_orm {

    template<>
    struct type_printer<Date> : public text_printer {};

    template<>
    struct statement_binder<Date> {
        int bind(sqlite3_stmt* stmt, int index, const Date& value) {
            return statement_binder<std::string>().bind(stmt, index, value.toISOString());
        }
    };

    template<>
    struct field_printer<Date> {
        std::string operator()(const Date& date) const {
            return date.toISOString();
        }
    };

    template<>
    struct row_extractor<Date> {
        Date extract(const char* row) {
            try {
                return Date(row);
            } catch (const InvalidDateException&) {
                throw std::runtime_error("incorrect date string (" + std::string(row) + ")");
            }
        }

        Date extract(sqlite3_stmt* stmt, int columnIndex) {
            return extract((const char*) sqlite3_column_text(stmt, columnIndex));
        }
    };

}
