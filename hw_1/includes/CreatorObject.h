#pragma once

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <optional>
#include <sstream>

#include "ObjectPark.h"
#include "StorageCenter.h"

using Creator = std::function<std::optional<ObjectPark*>
    (std::stringstream&, StorageCenter* storageCenter)>;

class CreatorObject {
public:
    CreatorObject();

    void initCreator();
    void addCreator(std::string str, Creator creator);
    std::optional<ObjectPark*> createObject(std::stringstream& ss,
        StorageCenter* storageCenter);
private:
    std::map<std::string, Creator> creators_;
};