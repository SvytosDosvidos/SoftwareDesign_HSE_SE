#include "../includes/CreatorObject.h"

std::optional<ObjectPark*> CreatorObject::createObject(std::stringstream& ss) {
    std::string name;
    ss >> name;
    if(creators_.find(name) == creators_.end()) {
        return std::nullopt;
    }
    return creators_[name](ss);
}

void CreatorObject::addCreator(std::string str, Creator creator) {
    creators_[str] = std::move(creator);
}

std::optional<ObjectPark*> CreatorWheel(std::stringstream& ss) {
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

    /*
    if(!ss.str().empty()) {
        return std::nullopt;
    }*/

    return new Wheel("wheel", inventoryId, simplicity, typeObject, typeWheel, radius);
}

CreatorObject::CreatorObject() {
    initCreator();
}

void CreatorObject::initCreator() {
    addCreator("wheel", CreatorWheel);
}