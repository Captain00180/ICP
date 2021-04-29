/**
 * @file wattmeter.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the Wattmeter class.
 * @date 2021-04-29
 * 
 */

#include "wattmeter.h"

Wattmeter::Wattmeter
(
    std::string topic_name,
    int interval_in_sec,
    std::string server
): Device::Device(topic_name, interval_in_sec, server)
{
    srand(time(NULL));                        // Different number each time the program launches
    base_watt = rand() % (240 + 1) + 10;      // Random base base_watt in the range <10;250>
}

Wattmeter::~Wattmeter()
{
}

std::string Wattmeter::generateWatt()
{
    srand(time(NULL));                  // Different number each time the program launches
    int max_diff = 10;                  // The maximum differece between the oscillating watts

    // Generate random watt based on the initialized value
    int base = base_watt;
    int random_number = rand() % (max_diff + 1);
    random_number -= max_diff / 2;
    base += random_number;

    // Generate random decimal points
    int decimal = rand() % 10;

    std::string final_watt = std::to_string(base) + '.' + std::to_string(decimal);
    return final_watt;
}

void Wattmeter::generateStatus()
{
    std::string watt = generateWatt();
    set_status(watt + scale);
}
