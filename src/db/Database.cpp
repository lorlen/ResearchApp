#include "db/Database.h"

#include <algorithm>
#include <fstream>
#include "db/exceptions.h"

using nlohmann::json;

Database::Database() {
    std::ifstream researchesFile(researchesPath), usersFile(usersPath), sensorsFile(sensorsPath);

    json researchesJSON, usersJSON, sensorsJSON;

    if (!researchesFile.good() || !usersFile.good() || !sensorsFile.good()) {
        std::ofstream researchesFile(researchesPath), usersFile(usersPath), sensorsFile(sensorsPath);

        auto admin = std::make_shared<User>("admin", "admin", "admin", true);
        admin->m_id = usersNextID;
        m_users.emplace(usersNextID, admin);

        researchesJSON = {
                {"next_id", researchesNextID},
                {"researches", json::object()}
        };

        usersJSON = {
                {"next_id", ++usersNextID},
                {"users", {
                    {std::to_string(usersNextID - 1), *admin}
                }}
        };

        sensorsJSON = {
                {"next_id", sensorsNextID},
                {"sensors", json::object()}
        };

        researchesFile << researchesJSON;
        usersFile << usersJSON;
        sensorsFile << sensorsJSON;
    }
    else {
        researchesFile >> researchesJSON;
        usersFile >> usersJSON;
        sensorsFile >> sensorsJSON;

        researchesNextID = researchesJSON.at("next_id").get<size_t>();
        usersNextID = usersJSON.at("next_id").get<size_t>();
        sensorsNextID = sensorsJSON.at("next_id").get<size_t>();
    }

    for (const auto& [id, val]: sensorsJSON.at("sensors").items()) {
        auto sensor = std::make_shared<Sensor>(val.get<Sensor>());
        sensor->m_id = std::stoull(id);
        m_sensors.emplace(std::stoull(id), sensor);
    }

    for (const auto& [id, val]: usersJSON.at("users").items()) {
        auto user = std::make_shared<User>(val.get<User>());
        user->m_id = std::stoull(id);
        m_users.emplace(std::stoull(id), user);
    }

    for (const auto& [id, val]: researchesJSON.at("researches").items()) {
        auto res = std::make_shared<Research>(val.get<Research>());
        res->m_id = std::stoull(id);

        res->author(m_users.at(val.at("author").get<size_t>()));

        for (auto user_id : val.at("assigned").get<std::vector<size_t>>()) {
            res->assignUser(m_users.at(user_id));
        }

        for (size_t i = 0; i < val.at("research_points").size(); i++) {
            const auto& point = val.at("research_points").at(i);

            for (auto sensor_id : point.at("sensors").get<std::vector<size_t>>()) {
                res->researchPoints()[i].addSensor(m_sensors.at(sensor_id));
            }
        }

        m_researches.emplace(std::stoull(id), res);
    }
}

Database::~Database() {
    std::ofstream researchesFile(researchesPath), usersFile(usersPath), sensorsFile(sensorsPath);

    json researchesJSON, usersJSON, sensorsJSON;

    researchesJSON = {
            {"next_id", researchesNextID},
            {"researches", json::object()}
    };

    usersJSON = {
            {"next_id", usersNextID},
            {"users", json::object()}
    };

    sensorsJSON = {
            {"next_id", sensorsNextID},
            {"sensors", json::object()}
    };

    for (const auto& [id, val]: m_researches) {
        researchesJSON.at("researches").emplace(std::to_string(id), *val);
    }

    for (const auto& [id, val]: m_users) {
        usersJSON.at("users").emplace(std::to_string(id), *val);
    }

    for (const auto& [id, val]: m_sensors) {
        sensorsJSON.at("sensors").emplace(std::to_string(id), *val);
    }

    researchesFile << researchesJSON;
    usersFile << usersJSON;
    sensorsFile << sensorsJSON;
}

inline void Database::checkUser() const {
    if (!m_currentUser)
        throw NotLoggedInException("");
}

inline void Database::checkAdmin() const {
    checkUser();

    if (!m_currentUser->admin())
        throw InsufficientPrivilegesException("");
}

void Database::logIn(const std::string& login, const std::string& password) const {
    auto user_iter = std::find_if(m_users.begin(), m_users.end(), [login](const auto& user) {
        return user.second->login() == login;
    });

    if (user_iter == m_users.end() || !(user_iter->second->verifyPassword(password))) {
        throw UserNotFoundException("");
    }

    m_currentUser = user_iter->second;
}

void Database::logOut() const {
    m_currentUser = nullptr;
}

std::shared_ptr<User> Database::currentUser() const {
    return m_currentUser;
}

const std::map<size_t, std::shared_ptr<Research>>& Database::researches() const {
    checkUser();
    return m_researches;
}

const std::map<size_t, std::shared_ptr<User>>& Database::users() const {
    checkUser();
    return m_users;
}

const std::map<size_t, std::shared_ptr<Sensor>>& Database::sensors() const {
    checkUser();
    return m_sensors;
}

std::vector<std::shared_ptr<const Research>> Database::getResearchesByStartDate(const Date& date) const {
    checkUser();
    std::vector<std::shared_ptr<const Research>> result;

    for (const auto& [id, val]: m_researches) {
        if (val->startDate() == date) {
            result.push_back(val);
        }
    }

    return result;
}

std::shared_ptr<const User> Database::getUserByLogin(const std::string& login) const {
    checkUser();

    for (const auto& [id, val]: m_users) {
        if (val->login() == login) {
            return val;
        }
    }
    throw UserNotFoundException(login);
}

std::map<size_t, std::shared_ptr<Research>>& Database::researches() {
    checkUser();
    return m_researches;
}

std::map<size_t, std::shared_ptr<User>>& Database::users() {
    checkAdmin();
    return m_users;
}

std::map<size_t, std::shared_ptr<Sensor>>& Database::sensors() {
    checkAdmin();
    return m_sensors;
}

std::vector<std::shared_ptr<Research>> Database::getResearchesByStartDate(const Date& date) {
    checkUser();
    std::vector<std::shared_ptr<Research>> result;

    for (const auto& [id, val]: m_researches) {
        if (val->startDate() == date) {
            result.push_back(val);
        }
    }

    return result;
}

std::shared_ptr<User> Database::getUserByLogin(const std::string& login) {
    checkAdmin();
    for (const auto& [id, val]: m_users) {
        if (val->login() == login) {
            return val;
        }
    }
    throw UserNotFoundException(login);
}

size_t Database::addResearch(const Research& research) {
    checkAdmin();
    auto rptr = std::make_shared<Research>(research);
    rptr->m_id = researchesNextID;
    if (!rptr->author().lock())
        rptr->author(m_currentUser);
    m_researches.emplace(researchesNextID, rptr);
    return researchesNextID++;
}

size_t Database::addResearchPoint(size_t researchID, const ResearchPoint& point) {
    checkAdmin();
    auto& points = m_researches.at(researchID)->researchPoints();
    points.push_back(point);
    return points.size() - 1;
}

size_t Database::addUser(const User& user) {
    checkAdmin();

    for (const auto& [id, val]: m_users) {
        if (val->login() == user.login()) {
            throw DatabaseException("User with login \"" + user.login() + "\" is already registered");
        }
    }

    auto uptr = std::make_shared<User>(user);
    uptr->m_id = usersNextID;
    m_users.emplace(usersNextID, uptr);
    return usersNextID++;
}

size_t Database::addSensor(const Sensor& sensor) {
    checkAdmin();
    auto sptr = std::make_shared<Sensor>(sensor);
    sptr->m_id = sensorsNextID;
    m_sensors.emplace(sensorsNextID, sptr);
    return sensorsNextID++;
}

void Database::deleteResearch(std::shared_ptr<Research> research) {
    checkAdmin();
    m_researches.erase(research->m_id);
}

void Database::deleteResearchPoint(std::shared_ptr<Research> research, size_t researchPointIndex) {
    checkAdmin();
    auto& points = research->researchPoints();
    points.erase(points.begin() + researchPointIndex);
}

void Database::deleteUser(std::shared_ptr<User> user) {
    checkAdmin();
    m_users.erase(user->m_id);
}

void Database::deleteUser(const std::string& login) {
    checkAdmin();

    for (const auto& [id, val]: m_users) {
        if (val->login() == login) {
            m_users.erase(id);
            return;
        }
    }
}

void Database::deleteSensor(std::shared_ptr<Sensor> sensor) {
    checkAdmin();
    m_sensors.erase(sensor->m_id);
}

void Database::deleteResearch(size_t id) {
    checkAdmin();
    m_researches.erase(id);
}

void Database::deleteResearchPoint(size_t researchID, size_t researchPointIndex) {
    checkAdmin();
    auto& points = m_researches.at(researchID)->researchPoints();
    points.erase(points.begin() + researchPointIndex);
}

void Database::deleteUser(size_t id) {
    checkAdmin();
    m_users.erase(id);
}

void Database::deleteSensor(size_t id) {
    checkAdmin();
    m_sensors.erase(id);
}