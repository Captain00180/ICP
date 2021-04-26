//
// Created by filipjanuska on 4/11/21.
//

#ifndef ICP_ACTION_CALLBACK_H
#define ICP_ACTION_CALLBACK_H

#include <iostream>
#include <QObject>
#include "mqtt/async_client.h"


class action_callback : public QObject, public virtual mqtt::callback, public virtual mqtt::iaction_listener{
    Q_OBJECT
    mqtt::async_client& client_;

    void on_success(const mqtt::token& tok) override;

    void on_failure(const mqtt::token& tok) override;

    void connected(const std::string& cause) override;

    void connection_lost(const std::string& cause) override;

    void message_arrived(mqtt::const_message_ptr msg) override;

    void delivery_complete(mqtt::delivery_token_ptr tok) override;

signals:
    void connection_failed();
    void subscribe_success();
    void subscribe_failed();
    void message_received(const std::string topic_name, const std::string payload);

public:
    action_callback(mqtt::async_client& client);

    bool print_messages = true;

};


#endif //ICP_ACTION_CALLBACK_H
