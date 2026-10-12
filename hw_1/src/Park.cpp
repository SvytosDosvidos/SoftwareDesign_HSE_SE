#include <iostream>

#include "../includes/Park.h"

Park::Park() {
    creatorObject_ = new CreatorObject();
    storageCenter_ = new StorageCenter();
}

void Park::printObjectEasy(const std::map<std::string, std::string> &mapCommand) const {
    storageCenter_->printObjectEasy(mapCommand);
}

void Park::printObjectNoEasy(const std::map<std::string, std::string>& mapCommand) const {
    storageCenter_->printObjectNoEasy(mapCommand);
}

bool Park::addObject(std::stringstream& ss, std::string& strError) {
    std::optional<ObjectPark*> obj = creatorObject_->createObject(ss, storageCenter_, strError);
    if(!obj.has_value()) {
        return false;
    }

    storageCenter_->addObject(*obj);
    return true;
}