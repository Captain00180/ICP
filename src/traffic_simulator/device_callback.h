/**
 * @file device_callback.h
 * @author David Hurta (xhurta04)
 * @brief Header file the basic callback class used in the Device class.
 * @date 2021-04-29
 * 
 */

#ifndef DEVICE_CALLBACK_H
#define DEVICE_CALLBACK_H

#include "device.h"
#include "mqtt/async_client.h"
#include "mqtt/callback.h"

class Device; // Declaring the class Device, to avoid problems associated with the circular dependency

/**
 * @brief Class used for a basic callback used in the Device class.
 * 
 */
class DeviceCallback : public mqtt::callback, public virtual mqtt::iaction_listener{
    private:
        mqtt::async_client& client;

        /**
         * @brief Function is called when success occurres.
         * 
         * @param tok 
         */
        virtual void on_success(const mqtt::token& tok) override;

        /**
         * @brief Function is called when failure occurres.
         * 
         * @param tok 
         */
        virtual void on_failure(const mqtt::token& tok) override;

    public:
        /**
         * @brief Construct a new Device Callback object
         * 
         * @param client 
         */
        DeviceCallback(mqtt::async_client& client);
};

#endif //DEVICE_CALLBACK_H
