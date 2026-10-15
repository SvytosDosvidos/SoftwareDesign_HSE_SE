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

std::vector<int> IInventoryItem::getSubItemIds() const {
    return {};
}

virtual bool IRentable::isForBeginners() const {
    return getSimplicity() >= 6;
}

IElectric::IElectric()

Wheel::Wheel(std::string name, int inventoryId,
    TypeObject typeObject, TypeWheel typeWheel, Value radius) : name_(name), inventoryId_(inventoryId),
        typeObject_(typeObject), typeWheel_(typeWheel), radius_(radius) {}

void Wheel::printObject() const {
    std::cout << "[" << name_ << "][" << inventoryId_ << "]["
        << typeObject_ << "][" << typeWheel_ << "][" << radius_ << "]\n";
}

ScooterElectric::ScooterElectric(std::string name, int inventoryId, int simplicity,
    TypeObject typeObject, Value electricityValue, std::vector<Wheel*> wheels, Value weight) :


int ScooterElectric::getInventoryIDWheel1() const {
    return wheels_[0]->getInventoryId();
}

int ScooterElectric::getInventoryIDWheel2() const {
    return wheels_[1]->getInventoryId();
}

void ScooterElectric::printObject() const {
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