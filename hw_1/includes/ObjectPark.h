#pragma once

#include <iostream>
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

class IInventoryItem {
public:
    virtual ~IInventoryItem() = default;
    virtual int getInventoryId() const = 0;
    virtual std::string getName() const = 0;

    virtual std::vector<int> getSubItemIds() const;

    virtual void printObject() const = 0;
};

class IRentable {
public:
    virtual ~IRentable() = default;
    virtual int getSimplicity() const = 0;
    virtual bool isForBeginners() const;
};

class BaseRentable : public virtual IInventoryItem, public IRentable {
public:
    BaseRentable(std::string name, int inventoryId, int simplicity);

    int getInventoryId() const override;
    std::string getName() const override;
    int getSimplicity() const override;

protected:
    std::string name_;
    int inventoryId_;
    int simplicity_;
    TypeObject typeObject_;
};

class IElectric : public BaseRentable {
public:
    IElectric(std::string name, int inventoryId, int simplicity,
        TypeObject typeObject, Value electricityValue);
protected:
    Value electricityValue_;
};

class Wheel : public IInventoryItem {
public:
    ~Wheel() override = default;

    Wheel(std::string name, int inventoryId,
        TypeObject typeObject, TypeWheel typeWheel, Value radius);

    void printObject() const override;
private:
    std::string name_;
    int inventoryId_;
    TypeObject typeObject_;
    TypeWheel typeWheel_;
    Value radius_;
};

class ScooterElectric : public IElectric {
public:
    ~ScooterElectric() override = default;

    ScooterElectric(std::string name, int inventoryId, int simplicity,
                    TypeObject typeObject, Value electricityValue,
                    std::vector<Wheel*> wheels, Value weight);

    int getInventoryIDWheel1() const;
    int getInventoryIDWheel2() const;

    void printObject() const override;
private:
    std::vector<Wheel*> wheels_;
    Value weight_;
};

class Scooter : public IElectric {
public:
    ~Scooter() override = default;

    Scooter(std::string name, int inventoryId, int simplicity,
            TypeObject typeObject,
            std::vector<Wheel*> wheels, Value weight);

    int getInventoryIDWheel1() const;
    int getInventoryIDWheel2() const;

    void printObject() const override;
private:
    std::vector<Wheel*> wheels_;
    Value weight_;
};