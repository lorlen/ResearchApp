#ifndef RESEARCHAPP_DATABASE_H
#define RESEARCHAPP_DATABASE_H


#include <map>
#include <memory>
#include <string>
#include "research/Date.h"
#include "research/Research.h"
#include "research/User.h"
#include "research/Sensor.h"
#include "external/json.hpp"

using nlohmann::json;

class Database {
    static constexpr auto researchesPath = "researches.json";
    static constexpr auto usersPath = "users.json";
    static constexpr auto sensorsPath = "sensors.json";

    // 0 is reserved for invalid ID
    size_t researchesNextID = 1;
    size_t usersNextID = 1;
    size_t sensorsNextID = 1;
    std::map<size_t, std::shared_ptr<Research>> m_researches;
    std::map<size_t, std::shared_ptr<User>> m_users;
    std::map<size_t, std::shared_ptr<Sensor>> m_sensors;
    mutable std::shared_ptr<User> m_currentUser;

    inline void checkUser() const;
    inline void checkAdmin() const;

public:
    Database();
    ~Database();

    // technical functions
    void logIn(const std::string& login, const std::string& password) const;
    void logOut() const;
    std::shared_ptr<User> currentUser() const;

    // const getters
    const std::map<size_t, std::shared_ptr<Research>>& researches() const;
    const std::map<size_t, std::shared_ptr<User>>& users() const;
    const std::map<size_t, std::shared_ptr<Sensor>>& sensors() const;
    std::vector<std::shared_ptr<const Research>> getResearchesByStartDate(const Date& date) const;
    std::shared_ptr<const User> getUserByLogin(const std::string& login) const;

    // non-const getters
    std::map<size_t, std::shared_ptr<Research>>& researches();
    std::map<size_t, std::shared_ptr<User>>& users();
    std::map<size_t, std::shared_ptr<Sensor>>& sensors();
    std::vector<std::shared_ptr<Research>> getResearchesByStartDate(const Date& date);
    std::shared_ptr<User> getUserByLogin(const std::string& login);

    // adders
    size_t addResearch(const Research& research);
    size_t addResearchPoint(size_t researchID, const ResearchPoint& point);
    size_t addUser(const User& user);
    size_t addSensor(const Sensor& sensor);

    // deleters
    void deleteResearch(std::shared_ptr<Research> research);
    void deleteResearchPoint(std::shared_ptr<Research> research, size_t researchPointIndex);
    void deleteUser(std::shared_ptr<User> user);
    void deleteUser(const std::string& login);
    void deleteSensor(std::shared_ptr<Sensor> sensor);

    void deleteResearch(size_t id);
    void deleteResearchPoint(size_t researchID, size_t researchPointIndex);
    void deleteUser(size_t id);
    void deleteSensor(size_t id);
};


#endif //RESEARCHAPP_DATABASE_H
