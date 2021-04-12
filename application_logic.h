//
// Created by filipjanuska on 4/11/21.
//

#ifndef ICP_APPLICATION_LOGIC_H
#define ICP_APPLICATION_LOGIC_H

#include "paho.mqtt.cpp/src/mqtt/async_client.h" //!!! Set to your path to your pacho library
#include "action_callback.h"

class application_logic {
    mqtt::async_client* active_client_;
    action_callback* active_callback_;
    mqtt::connect_options* active_con_opts;

public:

    int create_client(const std::string& server, const std::string& clientID);

    int create_callback();

    int create_con_opts();

    void delete_client();

    void delete_callback();

    void delete_con_opts();

    int connect();

    int disconnect();

    int subscribe(const std::string& topic);

    int unsubscribe(const std::string& topic);

    int publish(const std::string& topic, const std::string& payload);

    application_logic();

    ~application_logic();


};


#endif //ICP_APPLICATION_LOGIC_H
