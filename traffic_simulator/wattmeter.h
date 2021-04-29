/**
 * @file wattmeter.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the Wattmeter class.
 * @date 2021-04-29 
 * 
 */

#ifndef WATTMETER_H
#define WATTMETER_H

#include <string>

#include "device.h"

/**
 * @brief Class Wattmeter represents a wattmeter device.
 * 
 */
class Wattmeter: public Device
{
    private:
        int base_watt;              // The base watt is generated randomly when a new wattmeter is created.
        std::string scale = "W";

    public:
        /**
         * @brief Construct a new Wattmeter object
         * Initializes the base_watt variable randomly in the range <10;250>
         * @param topic_name 
         * @param interval_in_sec 
         * @param server 
         */
        Wattmeter
        (
            std::string topic_name,
            int interval_in_sec,
            std::string server
        );

        /**
         * @brief Destroy the Wattmeter object
         * 
         */
        ~Wattmeter();

        /**
         * @brief Generates modified watt value based on the base_watt value.
         * Generates watt randomly in the range <base_watt-max_diff/2;base_watt+max_diff/2>
         * 
         * @return std::string 
         */
        std::string generateWatt();

        /**
         * @brief Updates the status variable based on the watt value and the scale.
         * 
         */
        void generateStatus() override;
};

#endif //WATTMETER_H
