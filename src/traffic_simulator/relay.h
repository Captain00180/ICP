/**
 * @file relay.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the Relay class.
 * @date 2021-04-29
 * 
 */

#ifndef RELAY_H
#define RELAY_H

#include <string>
#include <regex>

#include "actuator.h"

/**
 * @brief Class Relay represents a relay device.
 * 
 */
class Relay: public Actuator
{
    private:
        /**
         * @brief Returns randomly string in the format needed to change the state (set:on || set:off)
         * 
         * @return std::string 
         */
        std::string generateRandomState();

    public:
        /**
         * @brief Construct a new Relay object
         * 
         * @param topic_name 
         * @param interval_in_sec 
         * @param server 
         */
        Relay
        (
            std::string topic_name,
            int interval_in_sec,
            std::string server
        );

        /**
         * @brief Destroy the Relay object
         * 
         */
        ~Relay();

        /**
         * @brief Set the status object if the msg has the correct format
         * "set:on" to change the status to on
         * "set:off" to change the status to off
         * 
         * @param new_status 
         */
        void set_status(std::string msg) override;
};

#endif //RELAY_H
