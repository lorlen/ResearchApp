#pragma once

#include <memory>
#include <string>
#include <vector>
#include "db/Record.h"
#include "research/Date.h"
#include "research/ResearchPoint.h"
#include "research/User.h"

using nlohmann::json;

class Research: public Record<size_t> {
    std::string m_title;
    Date m_startDate;
    Date m_endDate;
    std::string m_info;
    std::weak_ptr<User> m_author;
    std::vector<std::weak_ptr<User>> m_assigned;
    std::vector<ResearchPoint> m_points;

public:
    Research() = default;
    explicit Research(std::string title, Date startDate, Date endDate, std::string info, const std::shared_ptr<User>& author);

    const std::string& title() const;
    const Date& startDate() const;
    const Date& endDate() const;
    const std::string& info() const;
    std::weak_ptr<User> author() const;
    const std::vector<std::weak_ptr<User>>& assignedUsers() const;
    const std::vector<ResearchPoint>& researchPoints() const;
    bool isAssignedTo(const std::shared_ptr<User>& user) const;
    size_t countCheckedPoints() const;

    std::vector<std::weak_ptr<User>>& assignedUsers();
    std::vector<ResearchPoint>& researchPoints();

    void title(std::string newTitle);
    void startDate(const Date& newStartDate);
    void endDate(const Date& newEndDate);
    void info(std::string newInfo);
    void author(const std::shared_ptr<User>& newAuthor);
    void assignedUsers(const std::vector<std::shared_ptr<User>>& newUsers);
    void researchPoints(const std::vector<ResearchPoint>& newPoints);

    void assignUser(const std::shared_ptr<User>& user);
    void addResearchPoint(const ResearchPoint& point);

    friend void to_json(json& j, const Research& research);
    friend void from_json(const json& j, Research& research);
};
