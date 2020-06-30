#pragma once
#include <string>
#include <iostream>


class Sensor
{
private:
    uint sensor_ID;
    std::string sensorLabel;
    std::string sensorType;
    std::string sensorUnit;
    

public:
    /**
    * Getter - returns Sensor Label
    * @returns sensorLabel - string of a sensor label
    * */
    std::string get_sensorLabel() const;

    /**
    * Getter - returns Sensor Type
    * @returns sensorType - string of a sensor type
    * */
    std::string get_sensorType() const;

    /**
    * Getter - returns Sensor Unit
    * @returns sensorUnit - string of a sensor unit
    * */
    std::string get_sensorUnit() const;

    /**
    * Getter - returns Sensor ID
    * @returns sensor_ID - uint of a sensor ID
    * */
    uint get_sensor_ID() const;

    /**
     * Changer - changes sensorLabel, can be used by user
     * \param[in] newLabel a string argument of new sensorLabel
     * */
    void change_sensorLabel(std::string newLabel);

    /**
     * Changer - changes sensorType, can be used by user
     * \param[in] newType a string argument of new sensorType
     * */
    void change_sensorType(std::string newType);

    /**
     * Changer - changes sensorUnit, can be used by user
     * \param[in] newUnit a string argument of new sensorUnit
     * */
    void change_sensorUnit(std::string newUnit);

    /**
     * Setter - sets sensor_ID
     * \param[in] id an uint argument of new sensor_ID value
     * */
    void set_sensor_ID(uint id);
    
    Sensor();
    Sensor(std::string label, std::string type, std::string unit, uint id);
    ~Sensor();
};
