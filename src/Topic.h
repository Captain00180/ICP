/**
 * @file Topic.h
 * @brief Header for the topic class
 * @author Filip Januška
 */

#ifndef ICP_TOPIC_H
#define ICP_TOPIC_H

#include "mqtt/message.h"

/**
 * @class Topic
 * @brief
 * This class represents an mqtt topic, with a history of messages sent to this topic
 *  */
class Topic {
public:

    std::string name;   /**< Topic name */
    std::vector<std::pair<std::string, std::string>> history;   /**< History of the topic messages. The std::pair represents a
                                                                * timestamp-payload pair of the topic message */

    /**
     * Topic constructor
     * @param name_ Name of the topic
     */
    explicit Topic(std::string  name_);

};


#endif //ICP_TOPIC_H
