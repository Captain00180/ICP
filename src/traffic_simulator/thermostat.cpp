/**
 * @file thermostat.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the Thermostat class.
 * @date 2021-04-29
 * 
 */

#include "thermostat.h"

Thermostat::Thermostat
(
    std::string topic_name,
    int interval_in_sec,
    std::string server
): Actuator::Actuator(topic_name, interval_in_sec, server)
{
    scale = "°C";
    set_status("set:" + generateRandomSetpoint() + scale);
}

Thermostat::~Thermostat(){}

std::string Thermostat::generateRandomSetpoint()
{
    srand(time(NULL));
    int temp = rand() % (50 + 1) - 10;      // Generates random setpoint in the range <-10;40>
    return std::to_string(temp);
}

void Thermostat::set_status(std::string msg)
{
    if (std::regex_match(msg, std::regex("^set:(\\+|-)?[[:digit:]]+°C$")))
    {
        std::string substr = msg.substr(4, msg.length());
        status = substr;
    }
}
