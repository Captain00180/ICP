/**
 * @file hygrometer.cpp
 * @author David Hurta (xhurta04)
 * @brief Source file for the Hygrometer class.
 * @date 2021-04-29
 * 
 */

#include "hygrometer.h"

Hygrometer::Hygrometer
(
    std::string topic_name,
    int interval_in_sec,
    std::string server
): Device::Device(topic_name, interval_in_sec, server)
{
    srand(time(NULL));                              // Different number each time the program launches
    base_percentage = rand() % (80 + 1) + 10;      // Random base base_percentage <10;90>
}

Hygrometer::~Hygrometer()
{
}

void Hygrometer::generateStatus()
{
    std::string temperature = generateHygro();
    set_status(temperature + scale);
}

std::string Hygrometer::generateHygro()
{
    srand(time(NULL));                  // Different number each time the program launches
    int max_diff = 2;                   // The maximum  differece between percentages

    // Generate random percentage based on the initialized value
    int base = base_percentage;
    int random_number = rand() % (max_diff + 1);
    random_number -= max_diff / 2;
    base += random_number;

    // Generate random decimal points
    int decimal_percentage = rand() % 10;

    std::string final_percentage = std::to_string(base) + '.' + std::to_string(decimal_percentage);
    return final_percentage;
}
