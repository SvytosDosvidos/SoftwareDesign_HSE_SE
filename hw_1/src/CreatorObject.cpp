#include "../includes/CreatorObject.h"

void toLowerSymbols(std::string& str) {
    for(char& c : str) {
        c = static_cast<char>(tolower(c));
    }
}

std::optional<IInventoryItem*> CreatorObject::createObject(std::stringstream& ss,
    StorageCenter* storageCenter, std::string& strError) {
    std::string nameFirst;
    ss >> nameFirst;

    if(nameFirst.empty()) {
        return std::nullopt;
    }

    toLowerSymbols(nameFirst);
    if(creators_.find(nameFirst) == creators_.end()) {
        strError += "Unknown object type: " + nameFirst + "\n";
        return std::nullopt;
    }
    return creators_[nameFirst](ss, storageCenter, strError);
}

void CreatorObject::addCreator(std::string str, Creator creator) {
    creators_[std::move(str)] = std::move(creator);
}

std::optional<IInventoryItem*> CreatorWheel(std::stringstream& ss,
    StorageCenter* storageCenter, std::string& strError) {
    int inventoryId;
    TypeObject typeObject;
    TypeWheel typeWheel;
    Value radius;

    if(!(ss >> inventoryId)) {
        strError += "invalid inventoryId value\n";
        return std::nullopt;
    }
    if(!(ss >> typeObject)) {
        strError += "invalid typeObject value\n";
        return std::nullopt;
    }
    if(!(ss >> typeWheel)) {
        strError += "invalid typeWheel value\n";
        return std::nullopt;
    }
    if(!(ss >> radius)) {
        strError += "invalid radius value\n";
        return std::nullopt;
    }

    if(!storageCenter->checkUniqueId(inventoryId, strError)) {
        return std::nullopt;
    }
    if(!storageCenter->checkTypeObject("wheel", typeObject, strError)) {
        return std::nullopt;
    }


    return new Wheel("wheel", inventoryId, typeObject, typeWheel, radius);
}

std::optional<IInventoryItem*> CreatorScooter(std::stringstream& ss,
    StorageCenter* storageCenter, std::string& strError) {
    int inventoryId;
    int simplicity;
    TypeObject typeObject;
    int ind_1, ind_2;
    Value weight;

    if(!(ss >> inventoryId)) {
        strError += "invalid inventoryId value\n";
        return std::nullopt;
    }
    if(!(ss >> simplicity)) {
        strError += "invalid simplicity value\n";
        return std::nullopt;
    }
    if(!(ss >> typeObject)) {
        strError += "invalid typeObject value\n";
        return std::nullopt;
    }
    if(!(ss >> ind_1)) {
        strError += "invalid inventoryIdWheel_1 value\n";
        return std::nullopt;
    }
    if(!(ss >> ind_2)) {
        strError += "invalid inventoryIdWheel_2 value\n";
        return std::nullopt;
    }
    if(!(ss >> weight)) {
        strError += "invalid weight value\n";
        return std::nullopt;
    }

    if(!storageCenter->checkUniqueId(inventoryId, strError)) {
        return std::nullopt;
    }
    if(!storageCenter->checkSimplicity(simplicity, strError)) {
        return std::nullopt;
    }
    if(!storageCenter->checkTypeObject("scooter", typeObject, strError)) {
        return std::nullopt;
    }

    auto wheel_1 = storageCenter->getObject("wheel", ind_1);
    auto wheel_2 = storageCenter->getObject("wheel", ind_2);
    if(!wheel_1.has_value() || !wheel_2.has_value()) {
        strError += "Wheels with specified IDs not found in storage\n";
        return std::nullopt;
    }

    std::vector<Wheel*> wheels = {
        static_cast<Wheel*>(*wheel_1),
        static_cast<Wheel*>(*wheel_2)
    };

    storageCenter->deleteObject(ind_1);
    storageCenter->deleteObject(ind_2);

    return new Scooter("scooter", inventoryId, simplicity, typeObject, wheels, weight);
}

std::optional<IInventoryItem*> CreatorElectricScooter(std::stringstream& ss,
    StorageCenter* storageCenter, std::string& strError) {
    int inventoryId;
    int simplicity;
    TypeObject typeObject;
    Value electricityValue;
    int ind_1, ind_2;
    Value weight;

    if(!(ss >> inventoryId)) {
        strError += "invalid inventoryId value\n";
        return std::nullopt;
    }
    if(!(ss >> simplicity)) {
        strError += "invalid simplicity value\n";
        return std::nullopt;
    }
    if(!(ss >> typeObject)) {
        strError += "invalid inventoryId value\n";
        return std::nullopt;
    }
    if(!(ss >> electricityValue)) {
        strError += "invalid electricityValue value\n";
        return std::nullopt;
    }
    if(!(ss >> ind_1)) {
        strError += "invalid inventoryIdWheel_1 value\n";
        return std::nullopt;
    }
    if(!(ss >> ind_2)) {
        strError += "invalid inventoryIdWheel_2 value\n";
        return std::nullopt;
    }
    if(!(ss >> weight)) {
        strError += "invalid weight value\n";
        return std::nullopt;
    }

    if(!storageCenter->checkUniqueId(inventoryId, strError)) {
        return std::nullopt;
    }
    if(!storageCenter->checkCntElectrcity(electricityValue, strError)) {
        return std::nullopt;
    }
    if(!storageCenter->checkSimplicity(simplicity, strError)) {
        return std::nullopt;
    }
    if(!storageCenter->checkTypeObject("scooter_electric", typeObject, strError)) {
        return std::nullopt;
    }


    auto wheel_1 = storageCenter->getObject("wheel", ind_1);
    auto wheel_2 = storageCenter->getObject("wheel", ind_2);
    if(!wheel_1.has_value() || !wheel_2.has_value()) {
        strError += "Wheels with specified IDs not found in storage\n";
        return std::nullopt;
    }

    std::vector<Wheel*> wheels = {
        static_cast<Wheel*>(*wheel_1),
        static_cast<Wheel*>(*wheel_2)
    };

    storageCenter->addCntElectrcity(electricityValue);
    storageCenter->deleteObject(ind_1);
    storageCenter->deleteObject(ind_2);

    return new ScooterElectric("scooter_electric", inventoryId, simplicity, typeObject,
        electricityValue, wheels, weight);
}

CreatorObject::CreatorObject() {
    initCreator();
}

void CreatorObject::initCreator() {
    addCreator("wheel", CreatorWheel);
    addCreator("scooter", CreatorScooter);
    addCreator("scooter_electric", CreatorElectricScooter);
}