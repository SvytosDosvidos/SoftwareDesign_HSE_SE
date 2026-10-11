#include "../includes/StorageCenter.h"

void StorageCenter::printObjectEasy() const {
    for(const auto &it : objectsEasy_) {
        it->printObject();
    }
}

void StorageCenter::printObjectNoEasy() const {
    for(const auto &it : objectsNoEasy_) {
        it->printObject();
    }
}

void StorageCenter::addObject(ObjectPark* objectPark) {
    if(objectPark->getSimplicity() >= 6) {
        objectsEasy_.push_back(objectPark);
    } else {
        objectsNoEasy_.push_back(objectPark);
    }
}