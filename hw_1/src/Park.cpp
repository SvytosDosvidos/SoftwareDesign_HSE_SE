#include <iostream>

#include "../includes/Park.h"

Park::Park() {
    creatorObject_ = new CreatorObject();
    storageCenter_ = new StorageCenter();
}

void Park::printObjectEasy() const {
    std::cout << "The objects is easy to use:\n";
    storageCenter_->printObjectEasy();
}

void Park::printObjectNoEasy() const {
    std::cout << "The objects is not easy to use:\n";
    storageCenter_->printObjectNoEasy();
}

bool Park::addObject(std::stringstream& ss, std::string& strError) {
    std::optional<ObjectPark*> obj = creatorObject_->createObject(ss, storageCenter_, strError);
    if(!obj.has_value()) {
        return false;
    }

    storageCenter_->addObject(*obj);
    return true;
}