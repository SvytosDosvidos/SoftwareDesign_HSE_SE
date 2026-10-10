#pragma once

#include <string>
#include <vector>
#include <cstdint>

using Value = long long;

enum class TypeObject : uint8_t {
    TransportElectric = 1,
    TransportNoElectric = 2,
    SparePart = 3,
    Other = 4
};

enum class TypeWheel : uint8_t {
    ScooterWheel = 1,
    Bicycle = 2
};

std::ostream& operator<<(std::ostream& os, TypeObject s);
std::istream& operator>>(std::istream& is, TypeObject& s);

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
private:
    Value electricityValue_;
};

class Wheel : public ObjectPark {

private:
    TypeWheel typeWheel_;
    Value radius_;
};

class Scooter : public ITransportElectric {

private:
    std::vector<Wheel> wheels_;
    Value weight_;
};