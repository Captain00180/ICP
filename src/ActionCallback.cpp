/**
 * @file ActionCallback.cpp
 * @brief Implementation of the ActionCallback class
 */

#include "ActionCallback.h"


ActionCallback::ActionCallback(mqtt::async_client &client)
                : client_(client) {}

void ActionCallback::on_success(const mqtt::token &tok){
    std::cout << "Action '" << tok.get_type() << "' Successful!" << std::endl;
    switch (tok.get_type()) {
        case mqtt::token::SUBSCRIBE:
            emit subscribe_success();
            return;

        case mqtt::token::UNSUBSCRIBE:
            std::cout << "UNSUBSCRIBE SUCCESSFUL\n";
        default:
            return;

    }
}

void ActionCallback::on_failure(const mqtt::token &tok){
    std::cout << "ERROR: Action '" << tok.get_type() << "' Failed!" << std::endl;
    switch (tok.get_type()) {
        case mqtt::token::SUBSCRIBE:
            emit subscribe_failed();
            return;
        default:
            return;

    }
    //emit connection_failed();
}

void ActionCallback::connected(const std::string &cause) {
    std::cout << "Client connected! - " << cause << std::endl;
}

void ActionCallback::connection_lost(const std::string &cause) {
    std::cout << "Client lost connection! - " << cause << std::endl;

    while(!client_.is_connected())
    {
        std::cout << "Retrying connection..." << std::endl;
        client_.reconnect();
    }
}

void ActionCallback::message_arrived(mqtt::const_message_ptr msg) {
    if(print_messages) {
        std::cout << "Message arrived!" << std::endl;
        std::cout << "\tTopic: " << msg->get_topic() << std::endl;
        std::cout << "\tPayload: " << msg->get_payload() << std::endl;
    }
    const std::string topic_name = msg->get_topic();
    const std::string payload = msg->get_payload_str();
    std::ofstream oot ("output.bmp");
    if (oot.is_open())
    {
        oot << payload;
        oot.close();
    }
    emit message_received(topic_name, payload);

}


void ActionCallback::delivery_complete(mqtt::delivery_token_ptr tok) {
    std::cout << "Message '" << tok->get_message() << "' delivered!" << std::endl;
}

