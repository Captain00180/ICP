#include <iostream>
#include <string>
#include "paho.mqtt.cpp/src/mqtt/async_client.h" //!!! Set to your path to your pacho library
#include "action_callback.h"
#include "application_logic.h"


int main(int argc, char* argv[])
{

    application_logic app;

    app.create_client("tcp://test.mosquitto.org:1883", "icp_project");
    app.create_callback();
    app.create_con_opts();


    app.connect();

    app.subscribe("icp_test");
    app.publish("icp_test", "Hello, world!");

    app.disconnect();


    return 0;
}