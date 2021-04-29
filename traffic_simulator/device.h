/**
 * @file device.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the Device class.
 * @date 2021-04-29
 * 
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <time.h>
#include <ctime>

#include "device_callback.h"
#include "mqtt/async_client.h"
#include "mqtt/callback.h"

class DeviceCallback; //  Declaring the class DeviceCallback to avoid problems associated with the circular dependency

/**
 * @brief Class Device is used as the base class for the devices.
 * 
 */
class Device
{
    private:
        const std::string CLIENT_ID_PREFIX = "ICP_testing_client_";

    protected:
        std::string topic;
        std::string status;
        int interval;
        time_t last_publish;

        mqtt::async_client client;
        DeviceCallback* callback = nullptr;
        mqtt::connect_options connect_options;

    public:

        /**
         * @brief Construct a new Device object
         * 
         * @param topic_name std::string Name of the device's topic
         * @param interval_in_sec int The interval of publishing a new message for the device
         * @param server std::string The server, the device connects to
         */
        Device
        (
            std::string topic_name,
            int interval_in_sec,
            std::string server
        );

        /**
         * @brief Destroy the Device object
         * 
         */
        ~Device();

        /**
         * @brief Get the status object
         * 
         * @return std::string 
         */
        std::string get_status();

        /**
         * @brief Function tests if the period of the interval has passed.
         * 
         * @return true Interval has passed.
         * @return false Interval hasn't passed.
         */
        bool did_interval_pass();

        /**
         * @brief Functions tries to connect the device to its server.
         * 
         * @return int Returns zero if successfully connected. Nonzero otherwise.
         */
        int connect();

        /**
         * @brief Disconnects the device from its server.
         * 
         */
        void disconnect();

        /**
         * @brief Publishes the payload to the device's topic.
         * 
         * @param payload
         */
        void publish(mqtt::message_ptr payload);

        /**
         * @brief Tries to subscribe the device to its topic.
         * Virtual Function supposed to be potentially overriden by an inherited class.
         * Returns zero and doesn't do anything in the base class.
         * 
         * @return int Returns zero if successfully subscribed. Nonzero otherwise.
         */
        virtual int subscribe();

        /**
         * @brief Generates new status.
         * Virtual Function supposed to be potentially overriden by an inherited class.
         * Doesn't do anything in the base class.
         */
        virtual void generateStatus();

        /**
         * @brief Creates the message from the device's data to be later send.
         * 
         * @return mqtt::message_ptr 
         */
        virtual mqtt::message_ptr make_message();

        /**
         * @brief Set the status object
         * 
         * @param new_status 
         */
        virtual void set_status(std::string new_status);
};

#endif //DEVICE_H
