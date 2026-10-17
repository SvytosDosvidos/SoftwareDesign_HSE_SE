#include "../includes/StorageCenter.h"

StorageCenter::StorageCenter() : cntElectrcity_(0) {
    init();
}

void StorageCenter::init() {
    types_["wheel"] = TypeObject::SparePart;
    types_["scooter"] = TypeObject::TransportNoElectric;
    types_["scooter_electric"] = TypeObject::TransportElectric;
    types_["helmet"] = TypeObject::Other;
    types_["charging_station"] = TypeObject::OtherElectric;
}

void StorageCenter::printObject(const std::vector<BaseRentable*>& objects,
    const std::map<std::string, std::string>& mapCommand) const {
    if(!objects.empty()) {
        std::cout << "\nObjects:\n";
    }
    for(const auto& name : orderPrint_) {
        bool firstPrint = false;
        int count = 0;
        for(const auto* it : objects) {
            if (it->getName() == name) count++;
        }
        for(const auto* it : objects) {
            if(it->getName() == name) {
                if(!firstPrint) {
                    std::cout << it->getName() << ", count = " << count << "\n";
                    if(mapCommand.find(name) != mapCommand.end()) {
                        std::cout << mapCommand.at(name) << ":\n";
                    }
                    firstPrint = true;
                }
                it->printObject();
            }
        }
    }
}

void StorageCenter::printObjectEasy(const std::map<std::string, std::string>& mapCommand) const {
    printObject(objectsEasy_, mapCommand);
}

void StorageCenter::printObjectNoEasy(const std::map<std::string, std::string>& mapCommand) const {
    printObject(objectsNoEasy_, mapCommand);
}

void StorageCenter::printObjectOther(const std::map<std::string, std::string>& mapCommand) const {
    if(other_.empty()) {
        return;
    }
    std::cout << "\nThings and Parts on balance (Other):\n";
    for(const auto& name : orderPrint_) {
        bool firstPrint = false;
        int count = 0;
        for(const auto* it : other_) {
            if (it->getName() == name) count++;
        }
        for(const auto* it : other_) {
            if(it->getName() == name) {
                if(!firstPrint) {
                    std::cout << it->getName() << ", count = " << count << "\n";
                    if(mapCommand.find(name) != mapCommand.end()) {
                        std::cout << mapCommand.at(name) << ":\n";
                    }
                    firstPrint = true;
                }
                it->printObject();
            }
        }
    }
}

void StorageCenter::addObject(IInventoryItem* objectPark) {
    if(auto* rentable = dynamic_cast<BaseRentable*>(objectPark)) {
        if(rentable->isForBeginners()) {
            objectsEasy_.push_back(rentable);
        } else {
            objectsNoEasy_.push_back(rentable);
        }
    } else {
        other_.push_back(objectPark);
    }
}

std::optional<IInventoryItem*> StorageCenter::getObject(const std::string& name, int inventoryId) {
    for(auto* it : other_) {
        if(it->getName() == name && it->getInventoryId() == inventoryId) {
            return it;
        }
    }
    for(auto* it : objectsEasy_) {
        if(it->getName() == name && it->getInventoryId() == inventoryId) {
            return it;
        }
    }
    for(auto* it : objectsNoEasy_) {
        if(it->getName() == name && it->getInventoryId() == inventoryId) {
            return it;
        }
    }
    return std::nullopt;
}

void StorageCenter::deleteObject(int inventoryId) {
    auto eraseFrom = [inventoryId](auto& vec) {
        for(auto it = vec.begin(); it != vec.end(); ++it) {
            if((*it)->getInventoryId() == inventoryId) {
                vec.erase(it);
                return true;
            }
        }
        return false;
    };

    if(eraseFrom(other_)) {
        return;
    }
    if(eraseFrom(objectsEasy_)) {
        return;
    }

    eraseFrom(objectsNoEasy_);
}

bool StorageCenter::checkSimplicity(int simplicity, std::string& strError) const {
    if(simplicity < 1 || simplicity > 10) {
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
    auto checkList = [&](const auto& list) {
        for(const auto* item : list) {
            if(item->getInventoryId() == inventoryId) {
                strError += "InventoryId is already in use\n";
                return false;
            }

            for(int subId : item->getSubItemIds()) {
                if(subId == inventoryId) {
                    strError += "InventoryId is already in use\n";
                    return false;
                }
            }
        }
        return true;
    };

    if(!checkList(objectsEasy_)) {
        return false;
    }
    if(!checkList(objectsNoEasy_)) {
        return false;
    }
    if(!checkList(other_)) {
        return false;
    }

    return true;
}

bool StorageCenter::checkTypeObject(const std::string& name,
    TypeObject typeObject, std::string& strError) const {
    if(types_.find(name) == types_.end()) {
        strError += "Object not declared\n";
        return false;
    }

    if(types_.at(name) != typeObject) {
        std::stringstream ss;
        ss << types_.at(name);
        strError += "Invalid value for TypeObject: " + ss.str() + "\n";
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