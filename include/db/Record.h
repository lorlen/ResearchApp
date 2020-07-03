#ifndef RESEARCHAPP_RECORD_H
#define RESEARCHAPP_RECORD_H


class Database;

class Record {
protected:
    size_t m_id{};

public:
    size_t id() const {
        return m_id;
    }

    friend bool operator==(const Record& lhs, const Record& rhs) {
        return lhs.m_id == rhs.m_id;
    }

    friend class Database;
};


#endif //RESEARCHAPP_RECORD_H
