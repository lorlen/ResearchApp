#pragma once

class Database;

template<typename T>
class Record {
protected:
    T m_id{};

    Record() = default;
    explicit Record(T id) : m_id(std::move(id)) {}

public:
    T id() const {
        return m_id;
    }

    friend bool operator==(const Record& lhs, const Record& rhs) {
        return lhs.m_id == rhs.m_id;
    }

    friend class Database;
};
