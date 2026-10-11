#include <iostream>

#include "../includes/Park.h"

Park::Park() {
    creatorObject_ = new CreatorObject();
    storageCenter_ = new StorageCenter();
}

void Park::printObjectEasy() const {
    storageCenter_->printObjectEasy();
}

void Park::printObjectNoEasy() const {
    storageCenter_->printObjectNoEasy();
}

bool Park::addObject(std::stringstream& ss) {
    std::optional<ObjectPark*> obj = creatorObject_->createObject(ss, storageCenter_);
    if(!obj.has_value()) {
        return false;
    }

    storageCenter_->addObject(*obj);
    return true;
}