#pragma once

#include <string>
#include <vector>
#include <cstdint>

using Value = long long;

enum class TypeObject : uint8_t {
    TransportElectric = 1,
    TransportNoElectric = 2,
    OtherElectric = 3,
    SparePart = 4,
    Other = 5
};

std::ostream& operator<<(std::ostream& os, TypeObject s);
std::istream& operator>>(std::istream& is, TypeObject& s);

enum class TypeWheel : uint8_t {
    ScooterWheel = 1,
    BicycleWheel = 2
};

std::ostream& operator<<(std::ostream& os, TypeWheel s);
std::istream& operator>>(std::istream& is, TypeWheel& s);

class ObjectPark {
public:
    ObjectPark(std::string name, int inventoryId, int simplicity, TypeObject typeObject);
    virtual ~ObjectPark() = default;

    int getSimplicity() const;
    int getInventoryId() const;
    std::string getName() const;
    void virtual printObject() const = 0;

protected:
    std::string name_;
    int inventoryId_;
    int simplicity_;
    TypeObject typeObject_;
};

class ObjectElectric : public ObjectPark {
public:
    ObjectElectric(std::string name, int inventoryId, int simplicity,
        TypeObject typeObject, Value electricityValue);
protected:
    Value electricityValue_;
};

class Wheel : public ObjectPark {
public:
    ~Wheel() override = default;

    Wheel(std::string name, int inventoryId, int simplicity,
        TypeObject typeObject, TypeWheel typeWheel, Value radius);

    void printObject() const override;
private:
    TypeWheel typeWheel_;
    Value radius_;
};

class ScooterElectirc : public ObjectElectric {
public:
    ~ScooterElectirc() override = default;

    ScooterElectirc(std::string name, int inventoryId, int simplicity,
        TypeObject typeObject, Value electricityValue,
        std::vector<Wheel*> wheels, Value weight);

    void printObject() const override;
private:
    std::vector<Wheel*> wheels_;
    Value weight_;
};

class Scooter : public ObjectPark {
public:
    ~Scooter() override = default;

    Scooter(std::string name, int inventoryId, int simplicity,
            TypeObject typeObject,
            std::vector<Wheel*> wheels, Value weight);

    void printObject() const override;
private:
    std::vector<Wheel*> wheels_;
    Value weight_;
};