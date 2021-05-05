/**
 * @file ActionCallback.h
 * @brief Header for the ActionCallback class
 * @author Filip Januška
 */
#ifndef ICP_ACTION_CALLBACK_H
#define ICP_ACTION_CALLBACK_H

#include <iostream>
#include <QObject>
#include <QtCore/QVariant>
#include "mqtt/async_client.h"

/**
 * @class ActionCallback
 * @brief Handles the callbacks for asynchronous operations
 * The class defines and implements callbacks needed for
 * asynchronous mqtt communication. Callbacks emit Qt signals
 * to the GUI frontend to notify the application.
 */
class ActionCallback : public QObject, public virtual mqtt::callback, public virtual mqtt::iaction_listener{
    Q_OBJECT
    mqtt::async_client& client_;      /**< Reference to the mqtt client in an ApplicationLogic instance*/

    /**
     * On success callback - triggers when an async action is successful
     * @param tok Action token, holding information about the action
     */
    void on_success(const mqtt::token& tok) override;

    /**
     * On failure callback - triggers when an async action is unsuccessful
     * @param tok Action token, holding information about the action
     */
    void on_failure(const mqtt::token& tok) override;

    /**
     * Connected callback - Triggers when the client connects to a broker
     */
    void connected(const std::string& /*cause*/) override;

    /**
     * Connected callback - Triggers when the client connects to a broker
     * Attempts to reconnect a number of times
     * TODO signal the frontend
     */
    void connection_lost(const std::string& /*cause*/) override;

    /**
     * Message arrived callback - Triggers when client receives a message
     * @param msg Contains information about the message (e.g. topic, payload)
     */
    void message_arrived(mqtt::const_message_ptr msg) override;

    /**
     * Delivery complete callback - Triggers when a message is successfully delivered
     * @param tok Action token, holding information about the action
     */
    void delivery_complete(mqtt::delivery_token_ptr tok) override;

    // Signals which are emitted during their corresponding callbacks
    // They're connected to slots in frontend
signals:
    /**
     * Connection failed signal is emitted when client loses connection
     */
    void connection_failed();
    /**
     * Subscribe success signal is emitted when client successfully subscribes to a topic
     */
    void subscribe_success();
    /**
     * Subscribe failed signal is emitted when client fails to subscribe to a topic
     */
    void subscribe_failed();
    /**
     * Sends a signal when the client receives a message.
     * The signal carries the topic name and message payload
     * @param topic_name Name of the topic
     * @param payload Payload of the message
     */
    void message_received(std::string topic_name, std::string payload);

public:
    /**
     * ActionCallback constructor
     * @param client Reference to an async client, which carries out the actions
     */
    explicit ActionCallback(mqtt::async_client& client);

};


#endif //ICP_ACTION_CALLBACK_H
