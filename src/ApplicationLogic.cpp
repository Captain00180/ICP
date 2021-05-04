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
    active_client_->subscribe(topic, 1, nullptr, *active_callback_);
    return 0;
}

int ApplicationLogic::unsubscribe(const std::string &topic) {
    auto it = subscribed_topics.begin();
    while(it != subscribed_topics.end())
    {
        const std::string found = (*it)->name;
        std::cout << "Checking topic " << found << std::endl;
        if(found.rfind(topic, 0) == 0)
        {
            std::cout << topic << " found in subtopic " << found << std::endl;
            active_client_->unsubscribe(found);
            it = subscribed_topics.erase(it);
        }
        else
        {
            ++it;
        }
    }

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

void ApplicationLogic::add_topic_message(const std::string& topic, const std::string &payload) {
    if (topic_subscribed(topic))
    {
        for (auto i : subscribed_topics)
        {
            if (i->name == topic)
            {
                if (i->history.size() >= 5)
                {
                    i->history.erase(i->history.begin());
                }
                time_t timestamp = time(0);
                std::string dt = ctime(&timestamp);
                std::pair<std::string, std::string> data(dt, payload);
                i->history.push_back(data);
            }
        }
    }
}

std::vector<std::pair<std::string, std::string>> ApplicationLogic::get_topic_history(const std::string &topic) {
    if (topic_subscribed(topic))
    {
        std::cout << topic << " topic is subscribed\n";
        for (auto i : subscribed_topics)
        {
            if (i->name == topic)
            {
                return i->history;
            }
        }
    }
    return std::vector<std::pair<std::string, std::string>>();
}

bool ApplicationLogic::is_file_selected() {
    return file_selected;
}

int ApplicationLogic::publish(const std::string &topic, const std::string &payload, int qos, bool retain) {
    if (file_selected)
    {
        auto message = mqtt::make_message(topic, file_content, qos, retain);
        active_client_->publish(message, nullptr, *active_callback_);
    }
    else
    {
        auto message = mqtt::make_message(topic, payload, qos, retain);
        active_client_->publish(message, nullptr, *active_callback_);
    }

    return 0;
}

void ApplicationLogic::reset_file_status() {
    file_selected = false;
    file_content = "";
}


bool ApplicationLogic::open_file(const std::string &file_path) {
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open())
    {
        return false;
    }

    std::string content((std::istreambuf_iterator<char>(file_stream)),
                        (std::istreambuf_iterator<char>()));
    std::cout << "File content: " << content << std::endl;
    file_stream.close();
    file_content = content;
    file_selected = true;
    return true;

}

ApplicationLogic::ApplicationLogic() {
    active_client_ = nullptr;
    active_callback_ = nullptr;
    active_con_opts = nullptr;
    reset_file_status();
}

ApplicationLogic::~ApplicationLogic() {
    delete_callback();
    delete_con_opts();
    delete_client();
}