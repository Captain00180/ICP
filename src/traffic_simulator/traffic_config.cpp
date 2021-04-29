/**
 * @file traffic_config.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the configuring of the traffic simulator.
 * @date 2021-04-29
 * 
 */

#include "traffic_config.h"

Traffic_Config::Traffic_Config(){}

Traffic_Config::~Traffic_Config(){}

void Traffic_Config::set_server(std::string new_server)
{
    server = new_server;
}

std::string Traffic_Config::get_server()
{
    return server;
}

long long Traffic_Config::get_lifetime_sec()
{
    return lifetime_in_seconds;
}

std::vector<Device*> Traffic_Config::generate_devices_from_file(std::string config_file)
{
    std::ifstream input(config_file);
    std::string server = "";
    std::vector<Device*> list;

    for(std::string line; getline(input, line);)
    {
        std::smatch matches;
        
        if (std::regex_match(line, matches, std::regex("^server:(.*)$")))
        {
            server = matches[1];
        }
        else if (std::regex_match(line, matches, std::regex("^lifetime:([1-9]+[0-9]*)$")))
        {
            lifetime_in_seconds = std::stol(matches[1]);
        }
        else if (std::regex_match(line, matches, std::regex("^((#.*)|())$")))
        {
            // Comment or blank new line
            continue;
        }
        else if (std::regex_match(line, matches, std::regex("^thermometer;(.*);([1-9]+[0-9]*)$")))
        {
            Thermometer* device = new Thermometer(matches[1], std::stoi(matches[2]), server);
            list.push_back(device);
        }
        else if (std::regex_match(line, matches, std::regex("^hygrometer;(.*);([1-9]+[0-9]*)$")))
        {
            Hygrometer* device = new Hygrometer(matches[1], std::stoi(matches[2]), server);
            list.push_back(device);
        }
        else if (std::regex_match(line, matches, std::regex("^wattmeter;(.*);([1-9]+[0-9]*)$")))
        {
            Wattmeter* device = new Wattmeter(matches[1], std::stoi(matches[2]), server);
            list.push_back(device);
        }
        else if (std::regex_match(line, matches, std::regex("^door_sensor;(.*);([1-9]+[0-9]*)$")))
        {
            Door_Sensor* device = new Door_Sensor(matches[1], std::stoi(matches[2]), server);
            list.push_back(device);
        }
        else if (std::regex_match(line, matches, std::regex("^relay;(.*);([1-9]+[0-9]*)$")))
        {
            Relay* device = new Relay(matches[1], std::stoi(matches[2]), server);
            list.push_back(device);
        }
        else if (std::regex_match(line, matches, std::regex("^thermostat;(.*);([1-9]+[0-9]*)$")))
        {
            Thermostat* device = new Thermostat(matches[1], std::stoi(matches[2]), server);
            list.push_back(device);
        }
        else if (std::regex_match(line, matches, std::regex("^valve;(.*);([1-9]+[0-9]*)$")))
        {
            Valve* device = new Valve(matches[1], std::stoi(matches[2]), server);
            list.push_back(device);
        }
        else if (std::regex_match(line, matches, std::regex("^camera;(.*);([1-9]+[0-9]*);(.*);([1-9]+[0-9]*)$")))
        {
            std::string directory =  matches[3];
            
            struct stat sb;
            if (stat(directory.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
            {
                Camera* device = new Camera(matches[1], std::stoi(matches[2]), server, directory, std::stoi(matches[4]));
                list.push_back(device);
            }
            else
            {
                std::cerr << "Directory: " << directory << " Doesn't exist or is unaccessible!" << std::endl;
            }
        }
        else
        {
            std::cerr << "Line: " << line << " Has Wrong Format! Is skipped..." << std::endl;
        }
    }

    return list;
}
