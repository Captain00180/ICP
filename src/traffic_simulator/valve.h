/**
 * @file valve.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the Valve class.
 * @date 2021-04-29
 * 
 */

#ifndef VALVE_H
#define VALVE_H

#include <string>
#include <regex>

#include "actuator.h"

/**
 * @brief Class Valve represents a valve device.
 * 
 */
class Valve: public Actuator
{
    private:
        /**
         * @brief Generate randomly the state of the valve.
         * Returns string in the format needed to change the state (set:on || set:off)
         * 
         * @return std::string 
         */
        std::string generateRandomState();

    public:
        /**
         * @brief Construct a new Valve object
         * 
         * @param topic_name 
         * @param interval_in_sec 
         * @param server 
         */
        Valve
        (
            std::string topic_name,
            int interval_in_sec,
            std::string server
        );

        /**
         * @brief Destroy the Valve object
         * 
         */
        ~Valve();

        /**
         * @brief Set the status object if the msg has the correct format
         * "set:on" to change the status to on
         * "set:off" to change the status to off
         * @param new_status 
         */
        void set_status(std::string msg) override;
};

#endif //VALVE_H
