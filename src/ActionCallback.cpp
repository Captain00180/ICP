/**
 * @file ActionCallback.cpp
 * @brief Implementation of the ActionCallback class
 * @author Filip Januška
 */

#include "ActionCallback.h"


ActionCallback::ActionCallback(mqtt::async_client &client)
                : client_(client) {}

void ActionCallback::on_success(const mqtt::token &tok){
    std::cout << "Action '" << tok.get_type() << "' Successful!" << std::endl;
    if (tok.get_type() == mqtt::token::SUBSCRIBE)
    {
        // Notify the frontend that subscribe action has been successful
        emit subscribe_success();
    }
}

void ActionCallback::on_failure(const mqtt::token &tok){
    std::cout << "ERROR: Action '" << tok.get_type() << "' Failed!" << std::endl;
    if (tok.get_type() == mqtt::token::SUBSCRIBE)
    {
        // Notify the frontend that subscribe action has failed
        emit subscribe_failed();
    }
}

void ActionCallback::connected(const std::string& /*cause*/) {
    std::cout << "Client connected! - " << std::endl;
}

void ActionCallback::connection_lost(const std::string& /*cause*/) {
    std::cout << "Client lost connection! - " << std::endl;
    int reconnect_attempts = 5;

    while(!client_.is_connected() && reconnect_attempts-- > 0)
    {
        // Attempt to reconnect for "reconnect_attempts" times
        std::cout << "Retrying connection..." << std::endl;
        client_.reconnect()->wait();
    }
}

void ActionCallback::message_arrived(mqtt::const_message_ptr msg) {
    std::cout << "Message arrived!" << std::endl;
    std::cout << "\tTopic: " << msg->get_topic() << std::endl;
    std::cout << "\tPayload: " << msg->get_payload() << std::endl;
    const std::string topic_name = msg->get_topic();
    const std::string payload = msg->get_payload_str();
    // Forward the message to the frontend
    emit message_received(topic_name, payload);

}

void ActionCallback::delivery_complete(mqtt::delivery_token_ptr tok) {
    std::cout << "Message '" << tok->get_message() << "' delivered!" << std::endl;
}

