#pragma once

#include <map>
#include <string>
#include <functional>
#include <optional>
#include <sstream>

#include "ObjectPark.h"

using Creator = std::function<std::optional<ObjectPark>(std::stringstream&)>;

class CreatorObject {
public:
    CreatorObject();

    void initCreator();
    void addCreator(std::string str, Creator creator);
    std::optional<ObjectPark> createObject(std::stringstream& ss);
private:
    std::map<std::string, Creator> creators_;
};