#pragma once

#include <map>
#include <string>

#include "ObjectPark.h"

using creator = std::function<ObjectPark(std::string)>;

class CreatorObject {
public:
    CreatorObject();
    void addCreator();
    std::optional<ObjectPark> findCreator(std::string);
private:
    std::map<std::string, creator> creators_;
};