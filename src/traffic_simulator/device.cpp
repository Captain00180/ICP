/**
 * @file device.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the Device class.
 * @date 2021-04-29
 * 
 */

#include "device.h"

Device::Device(
    std::string topic_name,
    int interval_in_sec,
    std::string server
):  client(server, CLIENT_ID_PREFIX + topic_name)
{
    topic = topic_name;
    status = "";
    interval = interval_in_sec;
    time(&last_publish);
    connect_options.set_clean_session(true);

    if (callback == nullptr)
    {
        callback = new DeviceCallback(client);
        client.set_callback(*callback);
    }
}

Device::~Device()
{
    delete callback;
}

std::string Device::get_status()
{
    return status;
}

bool Device::did_interval_pass()
{
    time_t now, diff;
    time(&now);
    diff = difftime(now, last_publish);
    return diff > interval;
}

int Device::connect()
{
    try
    {
        client.connect(connect_options, nullptr, *callback)->wait();
        return 0;
    }
    catch(const mqtt::exception& err)
    {
        std::cerr << "\nError: Unable to connect to MQTT server: \t" << err << std::endl;
        return 1;
    }    
}

void Device::disconnect()
{
    try
    {
        client.disconnect()->wait();
    }
    catch (const mqtt::exception& err)
    {
        return;
    }
}

void Device::publish(mqtt::message_ptr payload)
{
    if (client.is_connected())
    {
        mqtt::message_ptr message = make_message();
        client.publish(message, nullptr, *callback)->wait();
        time(&last_publish);
    }
    else
    {
        std::cerr << "\nInfo: Trying to reconnect topic: \t" << topic << std::endl;
        client.reconnect();
    }
}

int Device::subscribe()
{
    return 0;
}

void Device::generateStatus(){}

mqtt::message_ptr Device::make_message()
{
    return mqtt::make_message(topic, status);
}

void Device::set_status(std::string new_status)
{
    status = new_status;
}
