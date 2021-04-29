/**
 * @file thermometer.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the Thermometer class.
 * @date 2021-04-29
 * 
 */

#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <string>

#include "device.h"

/**
 * @brief Class Thermostat represents a thermometer device.
 * 
 */
class Thermometer: public Device
{
    private:
        std::string scale;
        int base_temperature;

    public:
        /**
         * @brief Construct a new Thermometer object
         * Generates random base setpoint in the range <-10;30>
         * 
         * @param topic_name 
         * @param interval_in_sec 
         * @param server 
         */
        Thermometer
        (
            std::string topic_name,
            int interval_in_sec,
            std::string server
        );

        /**
         * @brief Destroy the Thermometer object
         * 
         */
        ~Thermometer();

        /**
         * @brief Sets a new temperature in the range <base-max_diff/2;base+max_diff/2>
         * 
         * @return std::string 
         */
        std::string generateTemperature();

        /**
         * @brief Sets a new status based on the base_temperature and generateTemperature function.
         * 
         */
        void generateStatus() override;
};

#endif //THERMOMETER
