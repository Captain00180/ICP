/**
 * @file hygrometer.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the Hygrometer class.
 * @date 2021-04-29
 * 
 */

#ifndef HYGROMETER_H
#define HYGROMETER_H

#include <string>

#include "device.h"

/**
 * @brief Class Hygrometer represents a hygrometer device.
 *
 */
class Hygrometer: public Device
{
    private:
        int base_percentage;
        std::string scale = "%";

    public:
        /**
         * @brief Construct a new Hygrometer object
         * Generates random base setpoint in the range <10;90>
         * 
         * @param topic_name 
         * @param interval_in_sec 
         * @param server 
         */
        Hygrometer
        (
            std::string topic_name,
            int interval_in_sec,
            std::string server
        );

        /**
         * @brief Destroy the Hygrometer object
         * 
         */
        ~Hygrometer();

        /**
         * @brief 
         * 
         * @return std::string Sets a new temperature in the range <base-max_diff/2;base+max_diff/2>
         */
        std::string generateHygro();

        /**
         * @brief Sets a new status based on the base_percentage and generateHygro function.
         * 
         */
        void generateStatus() override;
};

#endif //HYGROMETER_H
