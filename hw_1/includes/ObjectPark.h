#pragma once

#include <string>
#include <cstdint>

using Value = long long;

enum class TypeObject : uint8_t {
    TransportElectric = 1,
    TransportNoElectric = 2,
    SparePart = 3,
    Other = 4
};

/*
std::ostream& operator<<(std::ostream& os, TypeObject s) {
    switch (s) {
        using enum TypeObject;
        case TransportElectric:  return os << "TransportElectric";
        case TransportNoElectric:  return os << "TransportNoElectric";
        case SparePart: return os << "SparePart";
        case Other: return os << "Other";
    }
    return os << "Unknown";
}*/

class ObjectPark {
public:
    ObjectPark(std::string name, int inventoryId, int simplicity, TypeObject typeObject);

    void printObject() const;
private:
    std::string name_;
    int inventoryId_;
    int simplicity_;
    TypeObject typeObject_;
};

class ITransportElectric : public ObjectPark {
public:

private:
    Value electricityValue_;
};