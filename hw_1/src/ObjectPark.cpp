#include "../includes/ObjectPark.h"

std::ostream& operator<<(std::ostream& os, TypeObject s) {
    switch (s) {
        using enum TypeObject;
        case TransportElectric:  return os << "TransportElectric";
        case TransportNoElectric:  return os << "TransportNoElectric";
        case OtherElectric: return os << "OtherElectric";
        case SparePart: return os << "SparePart";
        case Other: return os << "Other";
    }
    return os << "Unknown";
}

std::istream& operator>>(std::istream& is, TypeObject& s) {
    int raw_value;

    if (is >> raw_value) {
        switch (raw_value) {
            case 1: {
                s = TypeObject::TransportElectric;
                break;
            } case 2: {
                s = TypeObject::TransportNoElectric;
                break;
            } case 3: {
                s = TypeObject::OtherElectric;
                break;
            } case 4: {
                s = TypeObject::SparePart;
                break;
            } case 5: {
                s = TypeObject::Other;
                break;
            } default: {
                is.setstate(std::ios_base::failbit);
            }
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, TypeWheel s) {
    switch (s) {
        using enum TypeWheel;
        case ScooterWheel: return os << "ScooterWheel";
        case BicycleWheel: return os << "Bicycle";
    }
    return os << "Unknown";
}

std::istream& operator>>(std::istream& is, TypeWheel& s) {
    int raw_value;

    if (is >> raw_value) {
        switch (raw_value) {
            case 1: {
                s = TypeWheel::ScooterWheel;
                break;
            } case 2: {
                s = TypeWheel::BicycleWheel;
                break;
            } default: {
                is.setstate(std::ios_base::failbit);
            }
        }
    }

    return is;
}

ObjectPark::ObjectPark(std::string name, int inventoryId, int simplicity,
    TypeObject typeObject) : name_(name), inventoryId_(inventoryId),
        simplicity_(simplicity), typeObject_(typeObject) {}

int ObjectPark::getSimplicity() const {
    return simplicity_;
}

std::string ObjectPark::getName() const {
    return name_;
}

int ObjectPark::getInventoryId() const {
    return inventoryId_;
}

ObjectElectric::ObjectElectric(std::string name, int inventoryId, int simplicity,
    TypeObject typeObject, Value electricityValue) : ObjectPark(name, inventoryId,
        simplicity, typeObject), electricityValue_(electricityValue) {}

Wheel::Wheel(std::string name, int inventoryId, int simplicity,
    TypeObject typeObject, TypeWheel typeWheel, Value radius) : ObjectPark(name,
        inventoryId, simplicity, typeObject), typeWheel_(typeWheel), radius_(radius) {}

void Wheel::printObject() const {
    std::cout << "[" << name_ << "][" << inventoryId_ << "][" << simplicity_ << "]["
        << typeObject_ << "][" << typeWheel_ << "][" << radius_ << "]\n";
}

ScooterElectirc::ScooterElectirc(std::string name, int inventoryId, int simplicity, TypeObject typeObject,
    Value electricityValue, std::vector<Wheel*> wheels, Value weight) : ObjectElectric(name,
        inventoryId, simplicity, typeObject, electricityValue), wheels_(wheels), weight_(weight) {}

int ScooterElectirc::getInventoryIDWheel1() const {
    return wheels_[0]->getInventoryId();
}

int ScooterElectirc::getInventoryIDWheel2() const {
    return wheels_[1]->getInventoryId();
}

void ScooterElectirc::printObject() const {
    std::cout << "[" << name_ << "][" << inventoryId_ << "][" << simplicity_ << "][" <<
        typeObject_ << "][" << electricityValue_ << "][" << weight_ << "]\n";

    std::cout << "Wheels count = " << wheels_.size() << "\n";
    for(const auto &it : wheels_) {
        it->printObject();
    }
}

Scooter::Scooter(std::string name, int inventoryId, int simplicity, TypeObject typeObject,
    std::vector<Wheel*> wheels, Value weight) : ObjectPark(name, inventoryId, simplicity, typeObject),
        wheels_(wheels), weight_(weight) {}

void Scooter::printObject() const {
    std::cout << "[" << name_ << "][" << inventoryId_ << "][" << simplicity_ << "][" <<
              typeObject_ << "][" << weight_ << "]\n";

    std::cout << "Wheels count = " << wheels_.size() << "\n";
    for(const auto &it : wheels_) {
        it->printObject();
    }
}

int Scooter::getInventoryIDWheel1() const {
    return wheels_[0]->getInventoryId();
}

int Scooter::getInventoryIDWheel2() const {
    return wheels_[1]->getInventoryId();
}