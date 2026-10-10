#include <iostream>

#include "../includes/Park.h"

Park::Park() {
    creatorObject_ = new CreatorObject();
}

void Park::printObjectEasy() const {
    for(const auto &it : objectsEasy_) {
        it.printObject();
    }
}

void Park::printObjectNoEasy() const {
    for(const auto &it : objectsNoEasy_) {
        it.printObject();
    }
}

void Park::addObject(std::stringstream ss) {
    std::optional<ObjectPark> obj = creatorObject_->createObject(ss);
    if(obj) {
        return;
    }
    if(obj->getSimplicity() >= 6) {
        objectsEasy_.push_back(*obj);
    } else {
        objectsNoEasy_.push_back(*obj);
    }
}