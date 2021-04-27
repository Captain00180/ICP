//
// Created by filipjanuska on 4/11/21.
//

#ifndef ICP_APPLICATION_LOGIC_H
#define ICP_APPLICATION_LOGIC_H

#include <map>

#include "mqtt/async_client.h"
#include "ActionCallback.h"
#include "topic.h"

class ApplicationLogic {


public:
    mqtt::async_client* active_client_;
    ActionCallback* active_callback_;
    mqtt::connect_options* active_con_opts;

    std::vector<topic*> subscribed_topics;

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

    void add_topic(const std::string& name);

    bool topic_subscribed(const std::string& name);

    int publish(const std::string& topic, const std::string& payload);

    ApplicationLogic();

    ~ApplicationLogic();


};


#endif //ICP_APPLICATION_LOGIC_H
