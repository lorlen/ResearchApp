#pragma once

#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "research/Sensor.h"

using nlohmann::json;

class ResearchPoint {
    std::string m_title;
    std::vector<std::weak_ptr<Sensor>> m_sensors;
    bool m_required{}, m_checked{};

public:
    ResearchPoint() = default;
    explicit ResearchPoint(std::string title, bool isRequired);

    const std::string& title() const;
    const std::vector<std::weak_ptr<Sensor>>& sensors() const;
    bool required() const;
    bool checked() const;

    void title(std::string newTitle);
    void sensors(const std::vector<std::shared_ptr<Sensor>>& newSensors);
    void required(bool isRequired);
    void checked(bool isChecked);

    void addSensor(const std::shared_ptr<Sensor>& sensor);

    friend void to_json(json& j, const ResearchPoint& point);
    friend void from_json(const json& j, ResearchPoint& point);
};
