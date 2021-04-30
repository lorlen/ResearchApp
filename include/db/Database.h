#ifndef RESEARCHAPP_DATABASE_H
#define RESEARCHAPP_DATABASE_H


#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "research/Date.h"
#include "research/Research.h"
#include "research/User.h"
#include "research/Sensor.h"

using nlohmann::json;

class Database {
    std::string researchesPath;
    std::string usersPath;
    std::string sensorsPath;

    // 0 is reserved for invalid ID
    size_t researchesNextID = 1;
    size_t sensorsNextID = 1;

    std::unordered_map<size_t, std::shared_ptr<Research>> m_researches;
    std::map<std::string, std::shared_ptr<User>> m_users;
    std::map<size_t, std::shared_ptr<Sensor>> m_sensors;

    mutable std::shared_ptr<User> m_currentUser;

    inline void checkUser() const;
    inline void checkAdmin() const;

public:
    Database(std::string rPath = "researches.json", std::string uPath = "users.json", std::string sPath = "sensors.json");
    ~Database();

    // technical functions
    void logIn(const std::string& login, const std::string& password) const;
    void logOut() const;
    std::shared_ptr<User> currentUser() const;

    // const getters
    const std::unordered_map<size_t, std::shared_ptr<Research>>& researches() const;
    const std::map<std::string, std::shared_ptr<User>>& users() const;
    const std::map<size_t, std::shared_ptr<Sensor>>& sensors() const;
    std::vector<std::shared_ptr<const Research>> getResearchesByStartDate(const Date& date) const;

    // non-const getters
    std::unordered_map<size_t, std::shared_ptr<Research>>& researches();
    std::map<std::string, std::shared_ptr<User>>& users();
    std::map<size_t, std::shared_ptr<Sensor>>& sensors();
    std::vector<std::shared_ptr<Research>> getResearchesByStartDate(const Date& date);

    // adders
    size_t addResearch(const Research& research);
    size_t addResearchPoint(const std::shared_ptr<Research>& research, const ResearchPoint& point);
    bool addUser(const User& user);
    size_t addSensor(const Sensor& sensor);

    // deleters
    void deleteResearch(const std::shared_ptr<Research>& research);
    void deleteResearchPoint(const std::shared_ptr<Research>& research, size_t researchPointIndex);
    void deleteUser(const std::shared_ptr<User>& user);
    void deleteSensor(const std::shared_ptr<Sensor>& sensor);

    void deleteResearch(size_t id);
    void deleteResearchPoint(size_t researchID, size_t researchPointIndex);
    void deleteUser(const std::string& login);
    void deleteSensor(size_t id);
};

namespace globals {
    /**
     * The global database singleton.
     */
    extern ::Database db;
}


#endif //RESEARCHAPP_DATABASE_H
