#include <algorithm>
#include "research/ResearchPoint.h"

ResearchPoint::ResearchPoint(std::string title, bool isRequired)
        : m_title(std::move(title)), m_required(isRequired) {}

const std::string& ResearchPoint::title() const {
    return m_title;
}

const std::vector<std::weak_ptr<Sensor>>& ResearchPoint::sensors() const {
    return m_sensors;
}

bool ResearchPoint::required() const {
    return m_required;
}

bool ResearchPoint::checked() const {
    return m_checked;
}

void ResearchPoint::title(std::string newTitle) {
    m_title = std::move(newTitle);
}

void ResearchPoint::sensors(const std::vector<std::shared_ptr<Sensor>>& newSensors) {
    m_sensors = std::vector<std::weak_ptr<Sensor>>(newSensors.begin(), newSensors.end());
}

void ResearchPoint::required(bool isRequired) {
    m_required = isRequired;
}

void ResearchPoint::checked(bool isChecked) {
    m_checked = isChecked;
}

void ResearchPoint::addSensor(const std::shared_ptr<Sensor>& sensor) {
    m_sensors.push_back(sensor);
}

void to_json(json& j, const ResearchPoint& point) {
    std::vector<size_t> sensors;
    sensors.reserve(point.m_sensors.size());
    std::transform(point.m_sensors.begin(), point.m_sensors.end(), std::back_inserter(sensors),
                   [](auto sensor) { return sensor.lock()->id(); });

    j = json {
            {"title", point.m_title},
            {"required", point.m_required},
            {"checked", point.m_checked},
            {"sensors", sensors}
    };
}

void from_json(const json& j, ResearchPoint& point) {
    j.at("title").get_to(point.m_title);
    j.at("required").get_to(point.m_required);
    j.at("checked").get_to(point.m_checked);
}


