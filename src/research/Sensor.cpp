#include "research/Sensor.h"

Sensor::Sensor(std::string label, std::string type, std::string unit)
        : m_label(std::move(label)), m_type(std::move(type)), m_unit(std::move(unit)) {}

const std::string& Sensor::label() const {
    return m_label;
}

const std::string& Sensor::type() const {
    return m_type;
}

const std::string& Sensor::unit() const {
    return m_unit;
}

void Sensor::label(std::string newLabel) {
    m_label = std::move(newLabel);
}

void Sensor::type(std::string newType) {
    m_type = std::move(newType);
}

void Sensor::unit(std::string newUnit) {
    m_unit = std::move(newUnit);
}

void to_json(json& j, const Sensor& sensor) {
    j = json {
            {"label", sensor.m_label},
            {"type", sensor.m_type},
            {"unit", sensor.m_unit}
    };
}

void from_json(const json& j, Sensor& sensor) {
    j.at("label").get_to(sensor.m_label);
    j.at("type").get_to(sensor.m_type);
    j.at("unit").get_to(sensor.m_unit);
}
