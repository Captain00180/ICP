/**
 * @file actuator.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the class Actuator.
 * @date 2021-04-29
 * 
 */

#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <string>

#include "device.h"
#include "actuator_callback.h"

/**
 * @brief Actuator class uses the actuator callback which is used to update device's status via messages.
 * 
 */
class Actuator: public Device
{
    private:

    public:
        /**
         * @brief Construct a new Actuator object
         * 
         * @param topic_name 
         * @param interval_in_sec 
         * @param server 
         */
        Actuator
        (
            std::string topic_name,
            int interval_in_sec,
            std::string server
        );

        /**
         * @brief Destroy the Actuator object
         * 
         */
        ~Actuator();

    /**
     * @brief Functions subscribes device to its topic.
     * 
     * @return int Retuns zero on success, nonzero otherwise.
     */
    int subscribe() override;

    /**
     * @brief Function used for generating new status. 
     * The actuator overrides this function to do nothing.
     * 
     */
    void generateStatus() override;
};

#endif //ACTUATOR_H
