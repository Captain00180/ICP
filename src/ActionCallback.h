/**
 * @file ActionCallback.h
 * @brief Header for the ActionCallback class
 */
#ifndef ICP_ACTION_CALLBACK_H
#define ICP_ACTION_CALLBACK_H

#include <iostream>
#include <QObject>
#include <fstream>

#include "mqtt/async_client.h"

/**
 * @class ActionCallback
 * @brief Handles the callbacks for asynchronous operations
 * The class defines and implements callbacks needed for
 * asynchronous mqtt communication. Callbacks emit signals
 * to the GUI frontend to notify the application.
 */
class ActionCallback : public QObject, public virtual mqtt::callback, public virtual mqtt::iaction_listener{
    Q_OBJECT
    mqtt::async_client& client_;

    void on_success(const mqtt::token& tok) override;

    void on_failure(const mqtt::token& tok) override;

    void connected(const std::string& cause) override;

    void connection_lost(const std::string& cause) override;

    void message_arrived(mqtt::const_message_ptr msg) override;

    void delivery_complete(mqtt::delivery_token_ptr tok) override;

    // Signals which are emitted during their corresponding callbacks
    // They're connected to slots in frontend
signals:
    void connection_failed();
    void subscribe_success();
    void subscribe_failed();
    /**
     * Sends a signal when the client receives a message
     * @param topic_name Name of the topic
     * @param payload Payload of the message
     */
    void message_received(const std::string topic_name, const std::string payload);

public:
    ActionCallback(mqtt::async_client& client);

    bool print_messages = true;

};


#endif //ICP_ACTION_CALLBACK_H
