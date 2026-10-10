#include <iostream>

#include "../includes/ObjectPark.h"

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

void ObjectPark::printObject() const {
    std::cout << name_ << " " << inventoryId_ << " "
        << simplicity_ << " " << typeObject_ << "\n";
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