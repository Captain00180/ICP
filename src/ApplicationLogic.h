/****************************************************************
 * @file ApplicationLogic.h
 * @brief Header for the ApplicationLogic class
 *
 */

#ifndef ICP_APPLICATION_LOGIC_H
#define ICP_APPLICATION_LOGIC_H

#include <map>

#include "mqtt/async_client.h"
#include "ActionCallback.h"
#include "topic.h"

/**
 * @class ApplicationLogic
 * @brief Handles the backend logic of the application
 * This class provides an interface for the MQTT communication.
 * It uses the Eclipse Paho MQTT library to encapsulate the client
 * and basic mqtt routines. The client is asynchronous and uses
 * a callback class (ActionCallback) to check the outcome and notify
 * the frontend GUI.
 */
class ApplicationLogic {


public:
    mqtt::async_client* active_client_;
    ActionCallback* active_callback_;
    mqtt::connect_options* active_con_opts;

    std::vector<topic*> subscribed_topics;  // contains all subscribed topics and their message history

    /**
     * Creates a new async client
     * @param server Name of the mqtt broker server
     * @param clientID Client ID TODO Generate randomly
     * @return 0 if action was successful, else 1
     */
    int create_client(const std::string& server, const std::string& clientID);

    /**
     * Creates a new ActionCallback object and binds it to the client
     * @pre An existing client in the ApplicationLogic instance
     * @return 0 if action was successful, else 1
     */
    int create_callback();

    int create_con_opts();

    void delete_client();

    void delete_callback();

    void delete_con_opts();

    int connect();

    int disconnect();

    int subscribe(const std::string& topic);

    int unsubscribe(const std::string& topic);

    /**
     * Creates and adds a new topic to the subscribed_topics vector,
     * only if the topic is not already present
     * @param name Name of the topic
     */
    void add_topic(const std::string& name);

    /**
     * Checks whether client is already subscribed to the given topic
     * @param name Topic name
     * @return true/false if the topic is subscribed
     */
    bool topic_subscribed(const std::string& name);

    int publish(const std::string& topic, const std::string& payload);

    ApplicationLogic();

    ~ApplicationLogic();


};


#endif //ICP_APPLICATION_LOGIC_H
