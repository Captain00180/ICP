/**
 * @file traffic_simulator.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the traffic simulator
 * @date 2021-04-29
 * 
 */

#include "traffic_simulator.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Please specify the configuration file." << std::endl;
        return 1;
    }

    time_t time_started;
    time(&time_started);

    Traffic_Config tc;
    std::vector<Device*> list_of_devices = tc.generate_devices_from_file(argv[1]);

    for (auto it = std::begin(list_of_devices); it != std::end(list_of_devices); ++it) {
        if ((*it)->connect() || (*it)->subscribe())
        {
            std::cerr << "\nError: Couldn't connect to the MQTT server." << std::endl;
            return 1;
        }
    }

    time_t current_time;
    long long program_lifetime_sec = tc.get_lifetime_sec();
    do
    {
        time(&current_time);
        for (auto it = std::begin(list_of_devices); it != std::end(list_of_devices); ++it)
        {
            if ((*it)->did_interval_pass())
            {
                (*it)->generateStatus();
                mqtt::message_ptr payload = (*it)->make_message();
                (*it)->publish(payload);
            }
        }
        sleep(1);
    } while (difftime(current_time, time_started) < program_lifetime_sec);    

    for (auto it = std::begin(list_of_devices); it != std::end(list_of_devices); ++it) {
        (*it)->disconnect();
    }
    list_of_devices.clear();

    return 0;
}