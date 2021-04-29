/**
 * @file thermostat.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the Thermostat class.
 * @date 2021-04-29
 * 
 */

#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <string>
#include <regex>

#include "actuator.h"

/**
 * @brief Class Thermostat represents a thermostat device.
 * 
 */
class Thermostat: public Actuator
{
    private:
        std::string scale = "°C";

        /**
         * @brief Generates a random setpoint in the range <-10;40>
         * 
         * @return std::string 
         */
        std::string generateRandomSetpoint();

    public:
        /**
         * @brief Construct a new Thermostat object
         * 
         * @param topic_name 
         * @param interval_in_sec 
         * @param server 
         */
        Thermostat
        (
            std::string topic_name,
            int interval_in_sec,
            std::string server
        );

        /**
         * @brief Destroy the Thermostat object
         * 
         */
        ~Thermostat();

        /**
         * @brief Set the status object if the msg has the correct format
         * "set:\d+°C" to change the status to \d+°C
         * @param new_status 
         */
        void set_status(std::string msg) override;
};

#endif //THERMOSTAT_H
