#ifndef RESEARCHAPP_SENSOR_H
#define RESEARCHAPP_SENSOR_H


#include <string>
#include "db/Record.h"
#include "external/json.hpp"

using nlohmann::json;

class Sensor: public Record<size_t> {
    std::string m_label, m_type, m_unit;

public:
    Sensor() = default;
    explicit Sensor(std::string label, std::string type, std::string unit);

    const std::string& label() const;
    const std::string& type() const;
    const std::string& unit() const;

    void label(std::string newLabel);
    void type(std::string newType);
    void unit(std::string newUnit);

    friend void to_json(json& j, const Sensor& sensor);
    friend void from_json(const json& j, Sensor& sensor);
};


#endif //RESEARCHAPP_SENSOR_H
