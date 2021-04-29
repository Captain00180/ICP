/**
 * @file door_sensor.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the Door_Sensor class.
 * @date 2021-04-29
 * 
 */

#include "door_sensor.h"

Door_Sensor::Door_Sensor
(
    std::string topic_name,
    int interval_in_sec,
    std::string server
): Device::Device(topic_name, interval_in_sec, server)
{
    status = "Movement Detected!";
    max_interval = interval_in_sec;
}

Door_Sensor::~Door_Sensor(){}

void Door_Sensor::generateStatus()
{
    set_new_random_interval();
}

void Door_Sensor::set_new_random_interval()
{
    srand(time(NULL));
    int random_interval = rand() % (max_interval + 1) + 1;        // Generate new interval in range <1;max_interval>
    interval = random_interval;
}
