#pragma once
#include <string>
#include <vector>
#include <iostream>


class ResearchPoint
{
private:
    uint researchPoint_ID;
    std::string researchPointTitle;
    bool requiredMeasurement;
    std::vector<uint> u_sensors;
    uint order;
    //std::vector<bool> is_checked;
    bool checked = false;

public:
    /**
    * Getter - returns researchPoint_ID
    * @returns researchPoint_ID - uint ID of researchPoint.
    * */
    uint get_researchPoint_ID() const;

    /**
    * Getter - returns researchPoint Title
    * @returns researchPointTitle - string with title of a researchPoint
    * */
    std::string get_researchPointTitle() const;

    /**
    * Getter - returns logical value of requiredMeasurement
    * @returns requiredMeasurement - bool flag if measurements are needed
    * */
    bool is_requiredMeasurement() const;

    /**
    * Getter - returns logical value of requiredMeasurement
    * @returns u_sensors - uint vector of used sensor in this point
    * */
    std::vector<uint> get_sensors() const;

    /**
    * Getter - returns logical value of checked
    * @returns checked - bool flag if researchPoint is checked
    * */
    bool is_checked() const;

    uint get_order() const;

    void set_order(uint o);

    /**
     * Setter - sets researchPoint_ID
     * \param[in] id an unsigned int argument of new researchPoint_ID value
     * */
    void set_researchPoint_ID(uint id);

    /**
     * Changer - changes researchPointTitle, can be used by user
     * \param[in] newTitle a string argument of new researchPointTitle
     * */
    void change_researchPointTitle(std::string newTitle);

    /**
     * Setter - sets new logical value to requiredMeasurement
     * \param[in] r a bool of new requiredMeasurement value
     * */
    void set_required(bool r);

    /**
     * Setter - sets new u_sensors vector
     * \param[in] sens an uint vector of sensors ID
     * */
    void set_sensors(std::vector<uint> sens);

    /**
     * Adds new sensor ID to u_sensors vector
     * \param[in] id an uint of sensor ID
     * */
    void add_sensor(uint id);

    /**
     * Delates sensor ID from u_sensors vector
     * \param[in] id an uint of sensor ID
     * */
    void delete_sensor(uint id);

    /**
    * Getter - returns logical value whether u_sensor is empty or not
    * @returns u_sensors.empty() - bool flag
    * */
    bool is_sensors() const;

    /**
     * Setter - sets new check logical value
     * \param[in] c a bool of a new state
     * */
    void set_checked(bool c);

    /**
     * Switchs state of logical flag checked
     * */
    void swich_checked();

    /**
    * Operator - returns logical value whether ID of given researchPoint is bigger than current researchPoint
    * */
    bool operator<(ResearchPoint* r) const;

    /**
    * Operator - returns logical value whether ID of given researchPoint is smaller than current researchPoint
    * */
    bool operator>(ResearchPoint* r) const;

    bool operator<(ResearchPoint r) const;
    bool operator>(ResearchPoint r) const;
    ResearchPoint();
    ResearchPoint(std::string title, bool is_req, uint id);
    ~ResearchPoint();
};
