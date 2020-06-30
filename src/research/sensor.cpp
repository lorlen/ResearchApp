#include "research/sensor.h"

Sensor::Sensor(/* args */)
{
   #ifdef _Debug
    std::cout << "Creating sensor using std constructor" << std::endl;
    #endif
}

Sensor::Sensor(std::string label, std::string type, std::string unit, uint id)
{
    sensorLabel = label;
    sensorType = type;
    sensorUnit = unit;
    sensor_ID = id;
    #ifdef _Debug
    std::cout << "Creating sensor id: " << sensor_ID<< " label: "<< sensorLabel <<" type: "<< sensorType << std::endl;
    #endif
}

Sensor::~Sensor()
{
    #ifdef _Debug
    std::cout << "Destroing sensor id: " << sensor_ID<< " label: "<< sensorLabel <<" type: "<< sensorType << std::endl;
    #endif
}

std::string Sensor::get_sensorLabel() const
/**
 * Getter - returns sensor label
 * @returns sensorLabel - string with label of a sensor
 * */
{
    return sensorLabel;
}

std::string Sensor::get_sensorType() const
/**
 * Getter - returns sensor type
 * @returns sensorType - string with type of a sensor
 * */
{
    return sensorType;
}

std::string Sensor::get_sensorUnit() const
/**
 * Getter - returns sensor unit
 * @returns sensorUnit - string with unit of a collected data
 * */
{
    return sensorUnit;
}

uint Sensor::get_sensor_ID() const
/**
 * Getter - returns sensor ID
 * @returns sensor_ID - uint with ID of a sensor
 * */
{
    return sensor_ID;
}

void Sensor::change_sensorLabel(std::string newLabel)
{
    sensorLabel = newLabel;
}

void Sensor::change_sensorType(std::string newType)
{
    sensorType = newType;
}

void Sensor::change_sensorUnit(std::string newUnit)
{
    sensorUnit = newUnit;
}

void Sensor::set_sensor_ID(uint id)
{
    sensor_ID = id;
}