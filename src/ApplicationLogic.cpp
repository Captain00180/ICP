/********************************************************
 * @file ApplicationLogic.cpp
 * @brief Implementation of  the ApplicationLogic class
 */
#include "ApplicationLogic.h"

int ApplicationLogic::create_client(const std::string &server, const std::string &clientID) {
    delete_client();
    active_client_ = new mqtt::async_client(server, clientID);
    return 0;
}

int ApplicationLogic::create_callback() {
    delete_callback();
    active_callback_ = new ActionCallback(*active_client_);
    active_client_->set_callback(*active_callback_);
    return 0;
}

int ApplicationLogic::create_con_opts() {
    delete_con_opts();
    active_con_opts = new mqtt::connect_options;
    return 0;
}

void ApplicationLogic::delete_client() {
    if (active_client_ != nullptr)
        delete active_client_;
    active_client_ = nullptr;
}

void ApplicationLogic::delete_callback() {
    if (active_callback_ != nullptr)
        delete active_callback_;
    active_callback_ = nullptr;
}

void ApplicationLogic::delete_con_opts() {
    if (active_con_opts != nullptr)
        delete active_con_opts;
    active_con_opts = nullptr;
}

int ApplicationLogic::connect() {
    std::cout << "Connecting to the server..." << std::flush;
    try {
        active_client_->connect(*active_con_opts, nullptr, *active_callback_)->wait();
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "\nError: Unable to connect to MQTT server: \t" << exc << std::endl;
        return 1;
    }
    if (!active_client_->is_connected())
    {
        std::cerr << "\nError: Unable to connect to MQTT server" << std::endl;
        return 1;
    }
    return 0;
}

int ApplicationLogic::disconnect() {
    std::cout << "Disconnecting from the MQTT server..." << std::endl << std::flush;
    active_client_->disconnect()->wait();
    if (active_client_->is_connected())
    {
        std::cerr << "Error: Couldn't disconnect\n";
        return 1;
    }
    std::cout << "Disconnect succesful" << std::endl;
    return 0;
}

int ApplicationLogic::subscribe(const std::string &topic) {
    active_client_->subscribe(topic, 1, nullptr, *active_callback_)->wait();
    return 0;
}

int ApplicationLogic::unsubscribe(const std::string &topic) {
    active_client_->unsubscribe(topic);
    return 0;
}

bool ApplicationLogic::topic_subscribed(const std::string &name) {
    for (auto i : subscribed_topics)
    {
        if (i->name == name)
            return true;
    }
    return false;
}

void ApplicationLogic::add_topic(const std::string& name)
{
    if (!topic_subscribed(name))
    {
        topic* new_topic = new topic(name);
        subscribed_topics.push_back(new_topic);
     }
}

int ApplicationLogic::publish(const std::string &topic, const std::string &payload) {
    auto message = mqtt::make_message(topic, payload);
    active_client_->publish(message, nullptr, *active_callback_);
    return 0;
}

ApplicationLogic::ApplicationLogic() {
    active_client_ = nullptr;
    active_callback_ = nullptr;
    active_con_opts = nullptr;
}

ApplicationLogic::~ApplicationLogic() {
    delete_callback();
    delete_con_opts();
    delete_client();
}