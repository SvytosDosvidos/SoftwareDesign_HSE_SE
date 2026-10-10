#pragma once

#include <map>
#include <string>
#include <functional>
#include <optional>
#include <sstream>

#include "ObjectPark.h"

using Creator = std::function<ObjectPark(std::string)>;

class CreatorObject {
public:
    CreatorObject();
    void addCreator(std::string str, Creator creator);
    std::optional<ObjectPark> findCreator(std::stringstream ss);
private:
    std::map<std::string, Creator> creators_;
};