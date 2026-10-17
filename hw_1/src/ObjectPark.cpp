#include "../includes/ObjectPark.h"

std::ostream& operator<<(std::ostream& os, TypeObject s) {
    switch(s) {
        using enum TypeObject;
        case TransportElectric:   return os << "TransportElectric";
        case TransportNoElectric: return os << "TransportNoElectric";
        case OtherElectric:       return os << "OtherElectric";
        case SparePart:           return os << "SparePart";
        case Other:               return os << "Other";
    }
    return os << "Unknown";
}

std::istream& operator>>(std::istream& is, TypeObject& s) {
    int raw_value;
    if(is >> raw_value) {
        switch(raw_value) {
            case 1: s = TypeObject::TransportElectric; break;
            case 2: s = TypeObject::TransportNoElectric; break;
            case 3: s = TypeObject::OtherElectric; break;
            case 4: s = TypeObject::SparePart; break;
            case 5: s = TypeObject::Other; break;
            default: is.setstate(std::ios_base::failbit); break;
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, TypeWheel s) {
    switch(s) {
        using enum TypeWheel;
        case ScooterWheel: return os << "ScooterWheel";
        case BicycleWheel: return os << "Bicycle";
    }
    return os << "Unknown";
}

std::istream& operator>>(std::istream& is, TypeWheel& s) {
    int raw_value;
    if(is >> raw_value) {
        switch(raw_value) {
            case 1: s = TypeWheel::ScooterWheel; break;
            case 2: s = TypeWheel::BicycleWheel; break;
            default: is.setstate(std::ios_base::failbit); break;
        }
    }
    return is;
}

std::vector<int> IInventoryItem::getSubItemIds() const {
    return {};
}

bool IRentable::isForBeginners() const {
    return getSimplicity() >= 6;
}

int BaseRentable::getInventoryId() const {
    return inventoryId_;
}

std::string BaseRentable::getName() const {
    return name_;
}

int BaseRentable::getSimplicity() const {
    return simplicity_;
}

BaseRentable::BaseRentable(std::string name, int inventoryId, int simplicity,
                           TypeObject typeObject)
        : name_(std::move(name)), inventoryId_(inventoryId), simplicity_(simplicity),
          typeObject_(typeObject) {}

Wheel::Wheel(std::string name, int inventoryId, TypeObject typeObject,
             TypeWheel typeWheel, Value radius)
        : name_(std::move(name)), inventoryId_(inventoryId),
          typeObject_(typeObject), typeWheel_(typeWheel), radius_(radius) {}

int Wheel::getInventoryId() const {
    return inventoryId_;
}

std::string Wheel::getName() const {
    return name_;
}

void Wheel::printObject() const {
    std::cout << "[" << name_ << "][" << inventoryId_ << "]["
              << typeObject_ << "][" << typeWheel_ << "][" << radius_ << "]\n";
}

Scooter::Scooter(std::string name, int inventoryId, int simplicity,
                 TypeObject typeObject, std::vector<Wheel*> wheels, Value weight)
        : BaseRentable(std::move(name), inventoryId, simplicity, typeObject),
          wheels_(std::move(wheels)), weight_(weight) {}

Scooter::~Scooter() {
    for(auto* w : wheels_) {
        delete w;
    }
}

std::vector<int> Scooter::getSubItemIds() const {
    std::vector<int> ids;
    for(const auto* w : wheels_) {
        if(w) {
            ids.push_back(w->getInventoryId());
        }
    }
    return ids;
}

void Scooter::printObject() const {
    std::cout << "[" << name_ << "][" << inventoryId_ << "][" << simplicity_ << "]["
              << typeObject_ << "][" << weight_ << "]\n";

    std::cout << "Wheels count = " << wheels_.size() << "\n";
    for(const auto* it : wheels_) {
        if(it) {
            it->printObject();
        }
    }
}

ScooterElectric::ScooterElectric(std::string name, int inventoryId, int simplicity,
                                 TypeObject typeObject, Value electricityValue,
                                 std::vector<Wheel*> wheels, Value weight)
        : BaseRentable(std::move(name), inventoryId, simplicity, typeObject),
          electricityValue_(electricityValue), wheels_(wheels), weight_(weight) {}

ScooterElectric::~ScooterElectric() {
    for(auto* w : wheels_) {
        delete w;
    }
}

Value ScooterElectric::getDailyEnergyConsumption() const {
    return electricityValue_;
}

std::vector<int> ScooterElectric::getSubItemIds() const {
    std::vector<int> ids;
    for(const auto* w : wheels_) {
        if(w) {
            ids.push_back(w->getInventoryId());
        }
    }
    return ids;
}

void ScooterElectric::printObject() const {
    std::cout << "[" << name_ << "][" << inventoryId_ << "][" << simplicity_ << "]["
              << typeObject_ << "][" << electricityValue_ << "][" << weight_ << "]\n";

    std::cout << "Wheels count = " << wheels_.size() << "\n";
    for(const auto* it : wheels_) {
        if(it) {
            it->printObject();
        }
    }
}