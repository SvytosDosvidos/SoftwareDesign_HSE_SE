#include <iostream>

#include "../includes/ObjectPark.h"

void ObjectPark::printObject() const {
    std::cout << name_ << " " << inventoryId_ << " "
              << simplicity_ << " " << typeObject_ << "\n";
}

int ObjectPark::getSimplicity() const {
    return simplicity_;
}

std::ostream& operator<<(std::ostream& os, TypeObject s) {
    switch (s) {
        using enum TypeObject;
        case TransportElectric:  return os << "TransportElectric";
        case TransportNoElectric:  return os << "TransportNoElectric";
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
                s = TypeObject::SparePart;
                break;
            } case 4: {
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
        case Bicycle: return os << "Bicycle";
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
                s = TypeWheel::Bicycle;
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

Wheel::Wheel(std::string name, int inventoryId, int simplicity,
    TypeObject typeObject, TypeWheel typeWheel, Value radius) : ObjectPark(name,
        inventoryId, simplicity, typeObject), typeWheel_(typeWheel), radius_(radius) {}