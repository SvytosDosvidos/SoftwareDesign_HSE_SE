#include "../includes/CreatorObject.h"

std::optional<ObjectPark> CreatorObject::findCreator(std::stringstream ss) {
    std::string name;
    ss >> name;
    if(creators_.find(name) == creators_.end()) {
        return std::nullopt;
    }
    //creators_(ss);
}

void CreatorObject::addCreator(std::string str, Creator creator) {
    creators_[str] = creator;
}

std::optional<ObjectPark> CreatorWheel(std::stringstream ss) {
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

    return Wheel("wheel", inventoryId, simplicity, typeObject, typeWheel, radius);
}