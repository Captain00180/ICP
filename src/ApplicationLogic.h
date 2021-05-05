/**
 * @file ApplicationLogic.h
 * @brief Header for the ApplicationLogic class
 * @author Filip Januška
 */

#ifndef ICP_APPLICATION_LOGIC_H
#define ICP_APPLICATION_LOGIC_H

#include <ctime>
#include <string>
#include <fstream>
#include "mqtt/async_client.h"
#include "ActionCallback.h"
#include "Topic.h"

/**
 * @class ApplicationLogic
 * @brief Handles the backend logic of the application
 *
 * This class provides an interface for the MQTT communication.
 * It uses the Eclipse Paho MQTT library to encapsulate the client
 * and basic mqtt routines. The client is asynchronous and uses
 * a callback class (ActionCallback) to check the outcome and notify
 * the frontend GUI.
 */
class ApplicationLogic {


public:
    mqtt::async_client* active_client_;     /**< Pointer to the client connected to the mqtt broker */
    ActionCallback* active_callback_;       /**< Pointer to the callback class, used to catch results of async operations */
    mqtt::connect_options* active_con_opts;/**< Pointer to the connection options class */

    std::vector<Topic*> subscribed_topics;  /**< Vector of all subscribed topics and their message history */

    /**
     * Creates a new async client
     * @param server Name of the mqtt broker server
     * @return 0 if action was successful, else 1
     */
    void create_client(const std::string &server);

    /**
     * Creates a new ActionCallback object and binds it to the client
     * @pre An existing client in the ApplicationLogic instance
     * @return 0 if action was successful, else 1
     */
    void create_callback();

    /**
     * Creates a new connection options instance and binds it to the client
     * @pre An existing client in the ApplicationLogic instance
     * @return 0 if action was successful, else 1
     */
    void create_con_opts();

    /**
     * Deletes the async client of the app
     */
    void delete_client();

    /**
     * Deletes the callback listener of the app
     */
    void delete_callback();

    /**
     * Deletes the connection options of the app
     */
    void delete_con_opts();

    /**
     * Connects the client to an mqtt broker. The function block control until the connection attempt is successful, or times out
     * @pre An existing client in the Appl  icationLogic instance
     * @return 0 if action was successful, else 1
     */
    int connect();

    /**
     * Disconnects the client from an mqtt broker. The function block control until the disconnect attempt is successful, or times out
     * @pre An existing client in the ApplicationLogic instance
     * @return 0 if action was successful, else 1
     */
    int disconnect();

    /**
     * Subscribes the active client to a topic, specified by the parameter
     * @param topic_name Name of the topic to which to be subscribed to
     */
    void subscribe(const std::string& topic_name);

    /**
     * Unsubscribes the active client from a topic and all subtopics of the given topic
     * @param topic_name Name of the topic
     */
    void unsubscribe(const std::string& topic_name);

    /**
     * Creates and adds a new topic to the subscribed_topics vector,
     * only if the topic is not already present
     * @param topic_name Name of the topic
     */
    void add_topic(const std::string& topic_name);

    /**
     * Adds a message to the specified's topic history
     * @param topic_name Name of the topic
     * @param payload The message to be saved
     */
    void add_topic_message(const std::string& topic_name, const std::string& payload);

    /**
     * Returns the history of messages of the specified topic
     * @param topic_name Name of the topic
     * @return Vector of timestamp-payload pair representing the history of topic messages
     */
    std::vector<std::pair<std::string, std::string>> get_topic_history(const std::string& topic_name);

    /**
     * Checks whether client is already subscribed to the given topic
     * @param topic_name Topic name
     * @return true/false if the topic is subscribed
     */
    bool topic_subscribed(const std::string& topic_name);

    /**
     * Publishes a message to the specified topic, with specified qos and retain option.
     * @param topic_name Name of the topic
     * @param payload Message to be sent
     * @param qos Quality of service option - may be 0/1/2
     * @param retain Whether to retain the message on the broker
     */
    void publish(const std::string& topic_name, const std::string& payload, int qos= 0, bool retain= false);

    /**
     * Sets the file_content and file_selected attributes to a safe value
     */
    void reset_file_status();

    /**
     * @return Whether a file is selected for uploading in a message
     */
    bool is_file_selected() const;

    /**
     * Attempts to open and read a file specified by the file_path parameter
     * Sets the members file_selected to true and file_content to the content of the file
     * @param file_path Path to the file to be opened
     * @return Whether the action was successful or not
     */
    bool open_file(const std::string& file_path);

    /**
     * ApplicationLogic constructor
     */
    ApplicationLogic();

    /**
     * ApplicationLogic destructor
     */
    ~ApplicationLogic();

private:
    std::string file_content;   /**< Holds the content of a selected file, which will be published */
    bool file_selected;         /**< Indicates whether a file is selected for upload or not */

};


#endif //ICP_APPLICATION_LOGIC_H
