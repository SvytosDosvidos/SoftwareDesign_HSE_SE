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

class IEnergyConsumer {
public:
    virtual ~IEnergyConsumer() = default;
    virtual Value getDailyEnergyConsumption() const = 0;
};

class BaseRentable : public virtual IInventoryItem, public IRentable {
public:
    BaseRentable(std::string name, int inventoryId, int simplicity, TypeObject typeObject);

    int getInventoryId() const override;
    std::string getName() const override;
    int getSimplicity() const override;

protected:
    std::string name_;
    int inventoryId_;
    int simplicity_;
    TypeObject typeObject_;
};

class Wheel : public IInventoryItem {
public:
    ~Wheel() override = default;

    Wheel(std::string name, int inventoryId,
          TypeObject typeObject, TypeWheel typeWheel, Value radius);

    int getInventoryId() const override;
    std::string getName() const override;
    void printObject() const override;

private:
    std::string name_;
    int inventoryId_;
    TypeObject typeObject_;
    TypeWheel typeWheel_;
    Value radius_;
};

class Scooter : public BaseRentable {
public:
    ~Scooter() override;

    Scooter(std::string name, int inventoryId, int simplicity,
            TypeObject typeObject, std::vector<Wheel*> wheels, Value weight);

    std::vector<int> getSubItemIds() const override;
    void printObject() const override;

private:
    std::vector<Wheel*> wheels_;
    Value weight_;
};

class ScooterElectric : public BaseRentable, public IEnergyConsumer {
public:
    ~ScooterElectric() override;

    ScooterElectric(std::string name, int inventoryId, int simplicity,
                    TypeObject typeObject, Value electricityValue,
                    std::vector<Wheel*> wheels, Value weight);

    Value getDailyEnergyConsumption() const override;
    std::vector<int> getSubItemIds() const override;
    void printObject() const override;

private:
    Value electricityValue_;
    std::vector<Wheel*> wheels_;
    Value weight_;
};

class Helmet : public IInventoryItem {
public:
    ~Helmet() override = default;

    Helmet(std::string name, int inventoryId, TypeObject typeObject, std::string size);

    int getInventoryId() const override;
    std::string getName() const override;
    void printObject() const override;

private:
    std::string name_;
    int inventoryId_;
    TypeObject typeObject_;
    std::string size_;
};

class ChargingStation : public IInventoryItem, public IEnergyConsumer {
public:
    ~ChargingStation() override = default;

    ChargingStation(std::string name, int inventoryId, TypeObject typeObject,
                    Value electricityValue, int slotsCount);

    int getInventoryId() const override;
    std::string getName() const override;
    Value getDailyEnergyConsumption() const override;
    void printObject() const override;

private:
    std::string name_;
    int inventoryId_;
    TypeObject typeObject_;
    Value electricityValue_;
    int slotsCount_;
};