/**
 * @file ApplicationLogic.cpp
 * @brief Implementation of the ApplicationLogic class
 * @author Filip Januška
 */
#include "ApplicationLogic.h"

#define TOPIC_HISTORY_RANGE 5 /**< Defines how many messages will be saved in a topic history */

void ApplicationLogic::create_client(const std::string &server) {
    delete_client();
    // Generate a pseudo-random client ID
    std::string num = std::to_string(rand() % 1000);
    active_client_ = new mqtt::async_client(server, "ICP_client_" + num);
}

void ApplicationLogic::create_callback() {
    delete_callback();
    active_callback_ = new ActionCallback(*active_client_);
    active_client_->set_callback(*active_callback_);
}

void ApplicationLogic::create_con_opts() {
    delete_con_opts();
    active_con_opts = new mqtt::connect_options;
}

void ApplicationLogic::delete_client() {
    delete active_client_;
    active_client_ = nullptr;
}

void ApplicationLogic::delete_callback() {
    delete active_callback_;
    active_callback_ = nullptr;
}

void ApplicationLogic::delete_con_opts() {
    delete active_con_opts;
    active_con_opts = nullptr;
}

int ApplicationLogic::connect() {
    try {
        active_client_->connect(*active_con_opts, nullptr, *active_callback_)->wait();
    }
    catch (const mqtt::exception& exc) {
        // Connection attempt was unsuccessful
        return 1;
    }
    if (!active_client_->is_connected())
    {
        // Connection attempt was unsuccessful
        return 1;
    }
    // Client is connected to a server
    return 0;
}

int ApplicationLogic::disconnect() {
    active_client_->disconnect()->wait();
    if (active_client_->is_connected())
    {
        return 1;
    }
    return 0;
}

void ApplicationLogic::subscribe(const std::string &topic_name) {
    active_client_->subscribe(topic_name, 1, nullptr, *active_callback_);
}

void ApplicationLogic::unsubscribe(const std::string &topic_name) {
    auto it = subscribed_topics.begin();
    // Iterate through the subscribed topics to find all subtopics of the topic, which is to be unsubscribed from
    while(it != subscribed_topics.end())
    {
        const std::string found = (*it)->name;
        if(found.rfind(topic_name, 0) == 0)
        {
            // Current topic's name begins with the path of the requested topic.
            // That means, that the found topic is a subtopic and needs to be unsubscribed as well
            active_client_->unsubscribe(found);
            it = subscribed_topics.erase(it);
        }
        else
        {
            ++it;
        }
    }

}

bool ApplicationLogic::topic_subscribed(const std::string &topic_name) {
    // iterate through all subscribed topics, look for the given topic name
    for (auto i : subscribed_topics)
    {
        if (i->name == topic_name)
            return true;
    }
    return false;
}

void ApplicationLogic::add_topic(const std::string& topic_name)
{
    if (!topic_subscribed(topic_name))
    {
        auto* new_topic = new Topic(topic_name);
        subscribed_topics.push_back(new_topic);
     }
}

void ApplicationLogic::add_topic_message(const std::string& topic_name, const std::string &payload) {
    if (topic_subscribed(topic_name))
    {
        for (auto i : subscribed_topics)
        {
            if (i->name == topic_name)
            {
                if (i->history.size() >= TOPIC_HISTORY_RANGE)
                {
                    // Simulates a queue of a fixed size - oldest messages get deleted when the vector fills up
                    i->history.erase(i->history.begin());
                }
                // Generate a current timestamp
                time_t timestamp = time(nullptr);
                std::string dt = ctime(&timestamp);
                // Saves the mssage with a timestamp
                std::pair<std::string, std::string> data(dt, payload);
                i->history.push_back(data);
            }
        }
    }
}

std::vector<std::pair<std::string, std::string>> ApplicationLogic::get_topic_history(const std::string &topic_name) {
    if (topic_subscribed(topic_name))
    {
        for (auto i : subscribed_topics)
        {
            if (i->name == topic_name)
            {
                return i->history;
            }
        }
    }
    return std::vector<std::pair<std::string, std::string>>();
}

bool ApplicationLogic::is_file_selected() const {
    return file_selected;
}

void ApplicationLogic::publish(const std::string &topic_name, const std::string &payload, int qos, bool retain) {
    if (file_selected)
    {
        // Creates and publishes a message with data previously read from a file
        auto message = mqtt::make_message(topic_name, file_content, qos, retain);
        active_client_->publish(message, nullptr, *active_callback_);
        reset_file_status();
    }
    else
    {
        // Creates and publishes a message with data from the user
        auto message = mqtt::make_message(topic_name, payload, qos, retain);
        active_client_->publish(message, nullptr, *active_callback_);
    }
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

    // Read the file content
    std::string content((std::istreambuf_iterator<char>(file_stream)),
                        (std::istreambuf_iterator<char>()));
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

    // Generate a random seed, for user ID generation
    srand(time(nullptr));
}

ApplicationLogic::~ApplicationLogic() {
    delete_callback();
    delete_con_opts();
    delete_client();
}



















