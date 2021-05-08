/**
 * @file ActionCallback.cpp
 * @brief Implementation of the ActionCallback class
 * @author Filip Januška
 */

#include "ActionCallback.h"


ActionCallback::ActionCallback(mqtt::async_client &client)
                : client_(client) {}

void ActionCallback::on_success(const mqtt::token &tok){
    if (tok.get_type() == mqtt::token::SUBSCRIBE)
    {
        // Notify the frontend that subscribe action has been successful
        emit subscribe_success();
    }
}

void ActionCallback::on_failure(const mqtt::token &tok){
    if (tok.get_type() == mqtt::token::SUBSCRIBE)
    {
        // Notify the frontend that subscribe action has failed
        emit subscribe_failed();
    }
}

void ActionCallback::connection_lost(const std::string& /*cause*/) {
    int reconnect_attempts = 5;

    while(!client_.is_connected() && reconnect_attempts-- > 0)
    {
        // Attempt to reconnect for "reconnect_attempts" times
        client_.reconnect()->wait();
    }
}

void ActionCallback::message_arrived(mqtt::const_message_ptr msg) {
    const std::string topic_name = msg->get_topic();
    const std::string payload = msg->get_payload_str();
    // Forward the message to the frontend
    emit message_received(topic_name, payload);

}


