/**
 * @file traffic_config.h
 * @author David Hurta (xhurta04)
 * @brief Header filer for configuring the traffic simulator.
 * @date 2021-04-29
 *
 */

#ifndef TRAFFIC_CONFIG_H
#define TRAFFIC_CONFIG_H

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <regex> 
#include <sstream>
#include <sys/stat.h>

#include "device.h"
#include "thermometer.h"
#include "camera.h"
#include "relay.h"
#include "thermostat.h"
#include "hygrometer.h"
#include "wattmeter.h"
#include "door_sensor.h"
#include "valve.h"

/**
 * @brief Class Traffic_Config handles configuring the traffic simulator.
 * 
 */
class Traffic_Config
{
private:
    std::string server;
    long long lifetime_in_seconds;

public:
    /**
     * @brief Construct a new Traffic_Config object
     * 
     */
    Traffic_Config();

    /**
     * @brief Destroy the Traffic_Config object
     * 
     */
    ~Traffic_Config();

    /**
     * @brief Set the server object
     * 
     * @param server 
     */
    void set_server(std::string server);

    /**
     * @brief Get the server object
     * 
     * @return std::string 
     */
    std::string get_server();

    /**
     * @brief Get the lifetime of the simulator in seconds object
     * 
     * @return long long 
     */
    long long get_lifetime_sec();

    /**
     * @brief Function returns vector of devices based on the configuration file.
     * If any error occurs or the syntax is invalid, an error message is printed into the std::cerr and the device is skipped.
     * 
     * @param config_file Configuration file containing devices to be created.
     * @return std::vector<Device*> List of created devices.
     */
    std::vector<Device*> generate_devices_from_file(std::string config_file);
};

#endif //TRAFFIC_CONFIG_H
