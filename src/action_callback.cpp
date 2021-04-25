//
// Created by filipjanuska on 4/11/21.
//

#include "action_callback.h"


action_callback::action_callback(mqtt::async_client &client)
                : client_(client) {}

void action_callback::on_success(const mqtt::token &tok){
    std::cout << "Action '" << tok.get_type() << "' Successful!" << std::endl;
}

void action_callback::on_failure(const mqtt::token &tok){
    std::cout << "ERROR: Action '" << tok.get_type() << "' Failed!" << std::endl;
    if (tok.get_type() == 0)
    {
        exit(1);
    }
}

void action_callback::connected(const std::string &cause) {
    std::cout << "Client connected! - " << cause << std::endl;
}

void action_callback::connection_lost(const std::string &cause) {
    std::cout << "Client lost connection! - " << cause << std::endl;

    while(!client_.is_connected())
    {
        std::cout << "Retrying connection..." << std::endl;
        client_.reconnect();
    }
}

void action_callback::message_arrived(mqtt::const_message_ptr msg) {
    if(print_messages) {
        std::cout << "Message arrived!" << std::endl;
        std::cout << "\tTopic: " << msg->get_topic() << std::endl;
        std::cout << "\tPayload: " << msg->get_payload() << std::endl;
    }
}

void action_callback::delivery_complete(mqtt::delivery_token_ptr tok) {
    std::cout << "Message '" << tok->get_message() << "' delivered!" << std::endl;
}

