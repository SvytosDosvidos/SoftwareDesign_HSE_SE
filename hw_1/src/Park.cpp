#include "../includes/Park.h"

Park::Park(std::shared_ptr<IServiceCenter> serviceCenter)
        : serviceCenter_(std::move(serviceCenter)) {
    creatorObject_ = new CreatorObject();
    storageCenter_ = new StorageCenter();
}

Park::Park() : Park(std::make_shared<StandardServiceCenter>()) {}

Park::~Park() {
    delete creatorObject_;
    delete storageCenter_;
}

void Park::printObjectEasy(const std::map<std::string, std::string>& mapCommand) const {
    storageCenter_->printObjectEasy(mapCommand);
}

void Park::printObjectNoEasy(const std::map<std::string, std::string>& mapCommand) const {
    storageCenter_->printObjectNoEasy(mapCommand);
}

void Park::printObjectOther(const std::map<std::string, std::string>& mapCommand) const {
    storageCenter_->printObjectOther(mapCommand);
}

bool Park::addObject(std::stringstream& ss, std::string& strError) {
    std::optional<IInventoryItem*> obj = creatorObject_->createObject(ss, storageCenter_, strError);
    if (!obj.has_value()) {
        return false;
    }

    if (!serviceCenter_->inspect(**obj, strError)) {
        delete *obj;
        return false;
    }

    if(auto* consumer = dynamic_cast<IEnergyConsumer*>(*obj)) {
        storageCenter_->addCntElectrcity(consumer->getDailyEnergyConsumption());
    }

    storageCenter_->addObject(*obj);
    return true;
}

Value Park::getCntElectricity() const {
    return storageCenter_->getCntElectrcity();
}