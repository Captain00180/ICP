//
// Created by filipjanuska on 4/26/21.
//

#ifndef ICP_TOPIC_H
#define ICP_TOPIC_H

#include "mqtt/message.h"


class topic {
public:
    std::string name;
    std::vector<std::string> history;

    topic(const std::string& name_);

};


#endif //ICP_TOPIC_H
