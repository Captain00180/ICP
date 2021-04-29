/**
 * @file valve.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the Valve class.
 * @date 2021-04-29
 * 
 */
#include "valve.h"

Valve::Valve
(
    std::string topic_name,
    int interval_in_sec,
    std::string server
): Actuator::Actuator(topic_name, interval_in_sec, server)
{
    set_status(generateRandomState());
}

Valve::~Valve(){}

std::string Valve::generateRandomState()
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

void Valve::set_status(std::string msg)
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
