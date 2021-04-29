/**
 * @file door_sensor.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the Door_Sensor class.
 * @date 2021-04-29
 * 
 */

#ifndef DOOR_SENSOR_H
#define DOOR_SENSOR_H

#include <string>

#include "device.h"

/**
 * @brief Class Door_Sensor represents a door sensor device.
 * 
 */
class Door_Sensor: public Device
{
    private:
    int max_interval;

    public:
        /**
         * @brief Construct a new Door_Sensor object
         * Door_Sensor's interval functions as maximal possible interval.
         * 
         * @param topic_name 
         * @param interval_in_sec 
         * @param server 
         */
        Door_Sensor
        (
            std::string topic_name,
            int interval_in_sec,
            std::string server
        );

        /**
         * @brief Destroy the Door_Sensor object
         * 
         */
        ~Door_Sensor();

        /**
         * @brief Set the new random interval in the range <1;max_interval>
         * 
         */
        void set_new_random_interval();

        /**
         * @brief Sets a new interval.
         * 
         */
        void generateStatus() override;
};

#endif //DOOR_SENSOR_H
