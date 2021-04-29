/**
 * @file device_callback.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the basic callback class used in the Device class.
 * @date 2021-04-29
 * 
 */

#include "device_callback.h"

DeviceCallback::DeviceCallback(mqtt::async_client& client): client(client){}

void DeviceCallback::on_success(const mqtt::token& tok){}

void DeviceCallback::on_failure(const mqtt::token& tok){}
