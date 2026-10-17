#include "../includes/Park.h"

Park::Park() {
    creatorObject_ = new CreatorObject();
    storageCenter_ = new StorageCenter();
    serviceCenter_ = new StandardServiceCenter();
}

Park::~Park() {
    delete creatorObject_;
    delete storageCenter_;
    delete serviceCenter_;
}

void Park::printObjectEasy(const std::map<std::string, std::string>& mapCommand) const {
    storageCenter_->printObjectEasy(mapCommand);
}

void Park::printObjectNoEasy(const std::map<std::string, std::string>& mapCommand) const {
    storageCenter_->printObjectNoEasy(mapCommand);
}

bool Park::addObject(std::stringstream& ss, std::string& strError) {
    std::optional<IInventoryItem*> obj = creatorObject_->createObject(ss, storageCenter_, strError);
    if(!obj.has_value()) {
        return false;
    }

    if(!serviceCenter_->inspect(**obj, strError)) {
        delete *obj;
        return false;
    }

    storageCenter_->addObject(*obj);
    return true;
}

Value Park::getCntElectricity() const {
    return storageCenter_->getCntElectrcity();
}