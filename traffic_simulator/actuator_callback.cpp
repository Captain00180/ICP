/**
 * @file actuator_callback.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the ActuatorCallback class.
 * @date 2021-04-29
 * 
 */

#include "actuator_callback.h"


ActuatorCallback::ActuatorCallback(mqtt::async_client& client, Actuator& new_actuator)
: DeviceCallback(client)
{
    device = &new_actuator;
}

void ActuatorCallback::message_arrived(mqtt::const_message_ptr msg)
{
    device->set_status(msg->get_payload());
}
