/**
 * @file relay.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the Relay class.
 * @date 2021-04-29
 * 
 */

#include "relay.h"

Relay::Relay
(
    std::string topic_name,
    int interval_in_sec,
    std::string server
): Actuator::Actuator(topic_name, interval_in_sec, server)
{
    set_status(generateRandomState());
}

Relay::~Relay(){}

std::string Relay::generateRandomState()
{
    srand(time(NULL));
    int temp = rand() % 2;
    if (temp)
    {
        return "set:on";
    }
    else
    {
        return "set:off";
    }
}

void Relay::set_status(std::string msg)
{
    if (std::regex_match(msg, std::regex("^set:on$")))
    {
        status = "on";
    }
    else if (std::regex_match(msg, std::regex("^set:off$")))
    {
        status = "off";
    }
}
