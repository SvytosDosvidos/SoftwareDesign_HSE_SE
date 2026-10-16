#pragma once

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <optional>
#include <sstream>
#include <cctype>

#include "ObjectPark.h"
#include "StorageCenter.h"

using Creator = std::function<std::optional<IInventoryItem*>
        (std::stringstream&, StorageCenter* storageCenter, std::string& strError)>;

class CreatorObject {
public:
    CreatorObject();

    void initCreator();
    void addCreator(std::string str, Creator creator);
    std::optional<IInventoryItem*> createObject(std::stringstream& ss,
        StorageCenter* storageCenter, std::string& strError);

private:
    std::map<std::string, Creator> creators_;
};