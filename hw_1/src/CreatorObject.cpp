#include "../includes/CreatorObject.h"

std::optional<ObjectPark*> CreatorObject::createObject(std::stringstream& ss,
    StorageCenter* storageCenter) {
    std::string name;
    ss >> name;
    if(creators_.find(name) == creators_.end()) {
        return std::nullopt;
    }
    return creators_[name](ss, storageCenter);
}

void CreatorObject::addCreator(std::string str, Creator creator) {
    creators_[str] = std::move(creator);
}

std::optional<ObjectPark*> CreatorWheel(std::stringstream& ss,
    StorageCenter* storageCenter) {
    int inventoryId;
    int simplicity;
    TypeObject typeObject;

    TypeWheel typeWheel;
    Value radius;
    if(!(ss >> inventoryId)) {
        return std::nullopt;
    }
    if(!(ss >> simplicity)) {
        return std::nullopt;
    }
    if(!(ss >> typeObject)) {
        return std::nullopt;
    }
    if(!(ss >> typeWheel)) {
        return std::nullopt;
    }
    if(!(ss >> radius)) {
        return std::nullopt;
    }

    return new Wheel("wheel", inventoryId, simplicity, typeObject, typeWheel, radius);
}

std::optional<ObjectPark*> CreatorScooter(std::stringstream& ss,
    StorageCenter* storageCenter) {
    int inventoryId;
    int simplicity;
    TypeObject typeObject;

    Value electricityValue;
    int ind_1, ind_2;
    std::vector<Wheel> wheels;
    Value weight;

    if(!(ss >> inventoryId)) {
        return std::nullopt;
    }
    if(!(ss >> simplicity)) {
        return std::nullopt;
    }
    if(!(ss >> typeObject)) {
        return std::nullopt;
    }
    if(!(ss >> electricityValue)) {
        return std::nullopt;
    }
    if(!(ss >> ind_1)) {
        return std::nullopt;
    }
    if(!(ss >> ind_2)) {
        return std::nullopt;
    }
    if(!(ss >> weight)) {
        return std::nullopt;
    }

    return new Scooter("scooter", inventoryId, simplicity, typeObject,
        electricityValue, wheels, weight);
}

CreatorObject::CreatorObject() {
    initCreator();
}

void CreatorObject::initCreator() {
    addCreator("wheel", CreatorWheel);
    addCreator("scooter", CreatorScooter);
}