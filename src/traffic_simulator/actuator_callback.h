/**
 * @file actuator_callback.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the ActuatorCallback class.
 * @date 2021-04-29
 * 
 */

#ifndef ACTUATOR_CALLBACK_H
#define ACTUATOR_CALLBACK_H

#include "device_callback.h"
#include "actuator.h"
#include "mqtt/async_client.h"
#include "mqtt/callback.h"

class Actuator; // Declaring the class Actuator, to avoid problems associated with the circular dependency

/**
 * @brief ActuatorCallback class used for the Actuator class. Allows for updating device's status via messages.
 * 
 */
class ActuatorCallback : public DeviceCallback{
    private:
        Actuator* device;

    public:
        /**
         * @brief Construct a new Actuator Callback object
         * 
         * @param client 
         * @param new_actuator 
         */
        ActuatorCallback(mqtt::async_client& client, Actuator& new_actuator);

        /**
         * @brief Function is called when a new message arrive into the device's topic.
         * Function calls the set_status function with the msg parameter.
         * 
         * @param msg 
         */
        void message_arrived(mqtt::const_message_ptr msg) override;
};

#endif //ACTUATOR_CALLBACK_H
