/**
 * @file actuator.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the Actuator class.
 * @date 2021-04-29
 * 
 */

#include "actuator.h"

Actuator::Actuator
(
    std::string topic_name,
    int interval_in_sec,
    std::string server
): Device::Device(topic_name, interval_in_sec, server)
{
    delete callback;    // Deletes the base callback created in the base constructor of Device class.
    callback = new ActuatorCallback(client, *this);
    client.set_callback(*callback);
}

Actuator::~Actuator()
{
    delete callback;
}

int Actuator::subscribe()
{
    if (client.is_connected())
    {    
        client.subscribe(topic, 1, nullptr, *callback);
        return 0;
    }
    else
    {
        return 1;
    }
}

void Actuator::generateStatus(){}
