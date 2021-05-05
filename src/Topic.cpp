/**
 * @file Topic.cpp
 * @brief Implementation of the topic class
 * @author Filip Januška
 */

#include "Topic.h"

#include <utility>

Topic::Topic(std::string  name_): name(std::move(name_)) {}

