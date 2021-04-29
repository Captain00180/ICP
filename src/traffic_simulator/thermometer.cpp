
/**
 * @file thermometer.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the Thermometer class.
 * @date 2021-04-29
 * 
 */

#include "thermometer.h"

Thermometer::Thermometer
(
    std::string topic_name,
    int interval_in_sec,
    std::string server
): Device::Device(topic_name, interval_in_sec, server)
{
    srand(time(NULL));                              // Different number each time the program launches
    scale = "°C";
    base_temperature = rand() % (40 + 1) - 10;      // Random base temperature <-10;30>
}

Thermometer::~Thermometer(){}

void Thermometer::generateStatus()
{
    std::string temperature = generateTemperature();
    set_status(temperature + scale);
}

std::string Thermometer::generateTemperature()
{
    srand(time(NULL));                  // Different number each time the program launches
    int max_diff = 2;                   // The maximum  differece between temperatures

    // Generate random temperature based on the options
    int basic_temp = base_temperature; 
    int random_number = rand() % (max_diff + 1);
    random_number -= max_diff / 2;
    basic_temp += random_number;

    // Generate random decimal points
    int decimal_temp = rand() % 100;

    std::string final_temp = std::to_string(basic_temp) + '.' + std::to_string(decimal_temp);
    return final_temp;
}
