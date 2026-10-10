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

class ObjectPark {
public:
    ObjectPark(std::string name, int inventoryId, int simplicity, TypeObject typeObject);

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