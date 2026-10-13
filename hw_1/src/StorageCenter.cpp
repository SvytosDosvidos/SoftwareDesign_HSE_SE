#include "../includes/StorageCenter.h"

StorageCenter::StorageCenter() : cntElectrcity_(0) {
    init();
}

void StorageCenter::init() {
    types_["wheel"] = TypeObject::SparePart;
    types_["scooter"] = TypeObject::TransportNoElectric;
    types_["scooter electric"] = TypeObject::TransportElectric;
}

void StorageCenter::printObject(const std::vector<ObjectPark*> objects, const std::map<std::string, std::string>& mapCommand) const {
    if(!objects.empty()) {
        std::cout << "\n";
        std::cout << "The objects is easy to use:\n";
    }
    for(const auto& name : orderPrint_) {
        bool firstPrint = false;
        int count = 0;
        for(const auto& it : objects) {
            if(it->getName() == name) {
                count++;
            }
        }
        for(const auto& it : objects) {
            if(it->getName() == name) {
                if(!firstPrint) {
                    std::cout << it->getName() << ", count = " << count << "\n";
                    std::cout << mapCommand.at(name);
                    std::cout << ":\n";
                    firstPrint = true;
                }
                it->printObject();
            }
        }
    }
}

bool StorageCenter::checkUniqueId(const std::vector<ObjectPark*>& objects,
    int inventoryId, std::string& strError) const {
    for(size_t i = 0; i < objectsNoEasy_.size(); ++i) {
        if(objectsNoEasy_[i]->getInventoryId() == inventoryId) {
            strError += "InventoryId is already in use\n";
            return false;
        }

        if(Scooter* scooter = dynamic_cast<Scooter*>(objectsNoEasy_[i])) {
            if(scooter->getInventoryIDWheel1() == inventoryId ||
               scooter->getInventoryIDWheel2() == inventoryId) {
                strError += "InventoryId is already in use\n";
                return false;
            }
        }

        if(ScooterElectirc* scooterElectric = dynamic_cast<ScooterElectirc*>(objectsNoEasy_[i])) {
            if(scooterElectric->getInventoryIDWheel1() == inventoryId ||
                    scooterElectric->getInventoryIDWheel2() == inventoryId) {
                strError += "InventoryId is already in use\n";
                return false;
            }
        }
    }

    return true;
}

void StorageCenter::printObjectEasy(const std::map<std::string, std::string>& mapCommand) const {
    printObject(objectsEasy_, mapCommand);
}

void StorageCenter::printObjectNoEasy(const std::map<std::string, std::string>& mapCommand) const {
    printObject(objectsNoEasy_, mapCommand);
}

void StorageCenter::addObject(ObjectPark* objectPark) {
    if(objectPark->getSimplicity() >= 6) {
        objectsEasy_.push_back(objectPark);
    } else {
        objectsNoEasy_.push_back(objectPark);
    }
}

std::optional<ObjectPark*> StorageCenter::getObject(std::string&& name,
    int inventoryId, int simplicity) {

    std::optional<ObjectPark*> result;
    //Всегда пытаюсь добавить в начале лёгкие детали, если объект сложный, а потом сложные,
    //а если объект лёгкие, то только лёгкие, чтобы не ломать логику, чтобы новичок
    //мог продолжать использовать этот объект
    for(size_t i = 0; i < objectsEasy_.size(); ++i) {
        if(objectsEasy_[i]->getName() == name &&
        objectsEasy_[i]->getInventoryId() == inventoryId) {
            result = objectsEasy_[i];
            break;
        }
    }

    if(simplicity < simplicityMin_ && !result.has_value()) {
        for(size_t i = 0; i < objectsNoEasy_.size(); ++i) {
            if(objectsNoEasy_[i]->getName() == name &&
            objectsNoEasy_[i]->getInventoryId() == inventoryId) {
                result = objectsNoEasy_[i];
                break;
            }
        }
    }

    return result;
}

void StorageCenter::deleteObject(int inventoryId) {
    for(int i = 0; i < objectsEasy_.size(); ++i) {
        if(objectsEasy_[i]->getInventoryId() == inventoryId) {
            objectsEasy_.erase(objectsEasy_.begin() + i);
            return;
        }
    }

    for(int i = 0; i < objectsNoEasy_.size(); ++i) {
        if(objectsNoEasy_[i]->getInventoryId() == inventoryId) {
            objectsNoEasy_.erase(objectsNoEasy_.begin() + i);
            return;
        }
    }
}

bool StorageCenter::checkSimplicity(int simplicity, std::string& strError) const {
    if(!(simplicity >= 1 && simplicity <= 10)) {
        strError += "Invalid value for simplicity([1, 10])\n";
        return false;
    }
    return true;
}

bool StorageCenter::checkCntElectrcity(Value cntElectrcity, std::string& strError) const {
    if(cntElectrcity <= 0) {
        strError += "Invalid value for cntElectricty(>0)\n";
        return false;
    }
    return true;
}

bool StorageCenter::checkUniqueId(int inventoryId, std::string& strError) const {
    if(!checkUniqueId(objectsEasy_, inventoryId, strError)) {
        return false;
    }

    return checkUniqueId(objectsNoEasy_, inventoryId, strError);
}

bool StorageCenter::checkTypeObject(std::string&& name,
    TypeObject typeObject, std::string& strError) const {

    if(types_.find(name) == types_.end()) {
        strError += "Object not diclarated\n";
        return false;
    }

    if(types_.at(name) != typeObject) {
        std::stringstream ss;
        ss << types_.at(name);
        strError += "Invalid value for TypeObject" + ss.str() + "\n";
        return false;
    }

    return true;
}

void StorageCenter::addCntElectrcity(Value cntElectrcity) {
    cntElectrcity_ += cntElectrcity;
}

Value StorageCenter::getCntElectrcity() const {
    return cntElectrcity_;
}