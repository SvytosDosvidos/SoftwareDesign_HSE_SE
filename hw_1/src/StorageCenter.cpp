#include "../includes/StorageCenter.h"

StorageCenter::StorageCenter() : cntElectrcity_(0) {}

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

std::optional<ObjectPark*> StorageCenter::getObject(std::string name,
    int inventoryId, int simplicity) {

    std::optional<ObjectPark*> result;
    //Всегда пытаюсь добавить в начале лёгкие детали, если объект сложный, а потом сложные,
    //а если объект лёгкие, то только лёгкие, чтобы не ломать логику, чтобы новичок
    //мог продолжать использовать этот объект
    for(int i = 0; i < objectsEasy_.size(); ++i) {
        if(objectsEasy_[i]->getName() == name &&
        objectsEasy_[i]->getInventoryId() == inventoryId) {
            result = objectsEasy_[i];
            objectsEasy_.erase(objectsEasy_.begin() + i);
            break;
        }
    }

    if(simplicity < 6) {
        for(int i = 0; i < objectsNoEasy_.size(); ++i) {
            if(objectsNoEasy_[i]->getName() == name &&
            objectsNoEasy_[i]->getInventoryId() == inventoryId) {
                result = objectsNoEasy_[i];
                objectsNoEasy_.erase(objectsNoEasy_.begin() + i);
                break;
            }
        }
    }

    return result;
}