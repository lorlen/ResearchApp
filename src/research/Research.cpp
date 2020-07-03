#include <algorithm>
#include "research/Research.h"

Research::Research(std::string title, Date startDate, Date endDate, std::string info,
                   const std::shared_ptr<User>& author)
                   : m_title(std::move(title)), m_startDate(startDate), m_endDate(endDate),
                   m_info(std::move(info)), m_author(author) {}

const std::string& Research::title() const {
    return m_title;
}

const Date& Research::startDate() const {
    return m_startDate;
}

const Date& Research::endDate() const {
    return m_endDate;
}

const std::string& Research::info() const {
    return m_info;
}

std::weak_ptr<User> Research::author() const {
    return m_author;
}

const std::vector<std::weak_ptr<User>>& Research::assignedUsers() const {
    return m_assigned;
}

const std::vector<ResearchPoint>& Research::researchPoints() const {
    return m_points;
}

bool Research::isAssignedTo(const std::shared_ptr<User>& user) const {
    for (auto& user_weak: m_assigned) {
        if (user_weak.lock()->id() == user->id()) {
            return true;
        }
    }

    return false;
}

size_t Research::countCheckedPoints() const {
    size_t sum = 0;

    for (const auto& point: m_points) {
        sum += point.checked();
    }

    return sum;
}

std::vector<std::weak_ptr<User>>& Research::assignedUsers() {
    return m_assigned;
}

std::vector<ResearchPoint>& Research::researchPoints() {
    return m_points;
}

void Research::title(std::string newTitle) {
    m_title = std::move(newTitle);
}

void Research::startDate(const Date& newStartDate) {
    m_startDate = newStartDate;
}

void Research::endDate(const Date& newEndDate) {
    m_endDate = newEndDate;
}

void Research::info(std::string newInfo) {
    m_info = std::move(newInfo);
}

void Research::author(const std::shared_ptr<User>& newAuthor) {
    m_author = newAuthor;
}

void Research::assignedUsers(const std::vector<std::shared_ptr<User>>& newUsers) {
    m_assigned = std::vector<std::weak_ptr<User>>(newUsers.begin(), newUsers.end());
}

void Research::researchPoints(const std::vector<ResearchPoint>& newPoints) {
    m_points = newPoints;
}

void Research::assignUser(const std::shared_ptr<User>& user) {
    m_assigned.push_back(user);
}

void Research::addResearchPoint(const ResearchPoint& point) {
    m_points.push_back(point);
}

void to_json(json& j, const Research& research) {
    std::vector<size_t> assigned;
    assigned.reserve(research.m_assigned.size());
    std::transform(research.m_assigned.begin(), research.m_assigned.end(), std::back_inserter(assigned),
            [](auto user) { return user.lock()->id(); });

    j = json {
            {"title", research.m_title},
            {"start_date", research.m_startDate},
            {"end_date", research.m_endDate},
            {"info", research.m_info},
            {"author", research.m_author.lock()->id()},
            {"assigned", assigned},
            {"research_points", research.m_points}
    };
}

void from_json(const json& j, Research& research) {
    j.at("title").get_to(research.m_title);
    j.at("start_date").get_to(research.m_startDate);
    j.at("end_date").get_to(research.m_endDate);
    j.at("info").get_to(research.m_info);
    j.at("research_points").get_to(research.m_points);
}
