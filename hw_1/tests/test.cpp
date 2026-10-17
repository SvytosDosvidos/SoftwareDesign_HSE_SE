#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <memory>
#include <sstream>

#include "../includes/OwnerPark.h"
#include "../includes/DIContainer.h"
#include "../includes/ServiceCenter.h"

void createWheel(std::string &name, int inventoryId,
                 int typeObject, int typeWheel, Value radius, std::stringstream &ss) {
    if(!ss.str().empty()) {
        ss = std::stringstream();
    }
    ss << name << " " << inventoryId << " " << typeObject << " " << typeWheel << " " << radius;
}

void createScooter(std::string &name, int inventoryId, int simplicity,
                   int typeObject, int inventoryIdWheel_1, int inventoryIdWheel_2, Value weight,
                   std::stringstream &ss) {
    if(!ss.str().empty()) {
        ss = std::stringstream();
    }
    ss << name << " " << inventoryId << " " << simplicity << " " << typeObject << " "
       << inventoryIdWheel_1 << " " << inventoryIdWheel_2 << " " << weight;
}

void createElectricScooter(std::string &name, int inventoryId, int simplicity,
                           int typeObject, Value cntElectricity, int inventoryIdWheel_1, int inventoryIdWheel_2,
                           Value weight, std::stringstream &ss) {
    if(!ss.str().empty()) {
        ss = std::stringstream();
    }
    ss << name << " " << inventoryId << " " << simplicity << " " << typeObject << " "
       << cntElectricity << " " << inventoryIdWheel_1 << " " << inventoryIdWheel_2 << " " << weight;
}

class AlwaysRejectServiceCenterMock : public IServiceCenter {
public:
    bool inspect(const IInventoryItem& /*item*/, std::string& strError) override {
        strError += "Inspection failed: Rejected by AlwaysRejectServiceCenterMock for testing\n";
        return false;
    }
};

class DefectiveIdServiceCenterMock : public IServiceCenter {
public:
    explicit DefectiveIdServiceCenterMock(int defectiveId) : defectiveId_(defectiveId) {}

    bool inspect(const IInventoryItem& item, std::string& strError) override {
        if(item.getInventoryId() == defectiveId_) {
            strError += "Inspection failed: Defective unit detected by mock\n";
            return false;
        }
        return true;
    }

private:
    int defectiveId_;
};

TEST_CASE("Test for create Wheel", "[Create Wheel]") {
    std::string nameCorrect = "wheel";
    int inventoryId = 1;
    int typeObjectCorrect = (int)TypeObject::SparePart;
    int typeWheelCorrect = 1;
    Value radius = 15;

    OwnerPark* ownerPark = new OwnerPark();
    std::stringstream ss;
    std::string strError;

    SECTION("Correct wheel") {
        createWheel(nameCorrect, inventoryId, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(ownerPark->addObject(ss, strError));

        createWheel(nameCorrect, inventoryId + 1, typeObjectCorrect, typeWheelCorrect + 1, radius, ss);
        CHECK(ownerPark->addObject(ss, strError));
    }
    SECTION("Not Correct Wheel, wrong with name") {
        std::string nameNoCorrect = "wheel1";
        createWheel(nameNoCorrect, inventoryId, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }
    SECTION("Not Correct Wheel, wrong with typeObject") {
        int typeObjectNoCorrect = 13;
        createWheel(nameCorrect, inventoryId, typeObjectNoCorrect, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }
    SECTION("Not Correct Wheel, wrong with typeWheel") {
        int typeWheelNoCorrect = 3;
        createWheel(nameCorrect, inventoryId, typeObjectCorrect, typeWheelNoCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }
    SECTION("Create 2 wheels with one id") {
        createWheel(nameCorrect, inventoryId, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(ownerPark->addObject(ss, strError));

        createWheel(nameCorrect, inventoryId, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }

    delete ownerPark;
}

TEST_CASE("Test for create Scooter", "[Create Scooter]") {
    std::string nameCorrectScooter = "scooter", nameCorrectWheel = "wheel";
    int inventoryId = 1, simplicity = 2;
    int typeObjectScooterCorrect = (int)TypeObject::TransportNoElectric;
    Value weight = 15;
    int typeWheel = 1;
    int typeObjectWheel = (int)TypeObject::SparePart;
    Value radius = 5;

    int inventoryIdWheel_1 = 2;
    int inventoryIdWheel_2 = 3;

    std::stringstream ss;
    std::string strError;
    OwnerPark* ownerPark = new OwnerPark();

    createWheel(nameCorrectWheel, inventoryIdWheel_1, typeObjectWheel, typeWheel, radius, ss);
    CHECK(ownerPark->addObject(ss, strError));
    createWheel(nameCorrectWheel, inventoryIdWheel_2, typeObjectWheel, typeWheel, radius, ss);
    CHECK(ownerPark->addObject(ss, strError));

    SECTION("Correct Scooter") {
        createScooter(nameCorrectScooter, inventoryId, simplicity, typeObjectScooterCorrect,
                      inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(ownerPark->addObject(ss, strError));
    }

    SECTION("Not Correct Scooter, wrong with wheel used") {
        createScooter(nameCorrectScooter, inventoryId, simplicity, typeObjectScooterCorrect,
                      inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(ownerPark->addObject(ss, strError));

        createScooter(nameCorrectScooter, inventoryId + 1, simplicity, typeObjectScooterCorrect,
                      inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }

    SECTION("Not Correct Scooter, wrong with wheel id used") {
        createScooter(nameCorrectScooter, inventoryId, simplicity, typeObjectScooterCorrect,
                      inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(ownerPark->addObject(ss, strError));

        createWheel(nameCorrectWheel, inventoryIdWheel_1, typeObjectWheel, typeWheel, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));

        createWheel(nameCorrectWheel, inventoryIdWheel_2, typeObjectWheel, typeWheel, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }

    SECTION("Not correct Scooter, wrong simplicity value") {
        createScooter(nameCorrectScooter, inventoryId, 15, typeObjectScooterCorrect,
                      inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }

    delete ownerPark;
}

TEST_CASE("Test for create electric Scooter", "[Create Electric Scooter]") {
    std::string nameCorrectScooterElectric = "scooter_electric", nameCorrectWheel = "wheel";
    int inventoryId = 1, simplicity = 2;
    int typeObjectScooterCorrect = (int)TypeObject::TransportElectric;

    Value cntElectricity = 15;
    Value weight = 15;
    int typeWheel = 1;
    int typeObjectWheel = (int)TypeObject::SparePart;
    Value radius = 5;

    int inventoryIdWheel_1 = 2;
    int inventoryIdWheel_2 = 3;

    std::stringstream ss;
    std::string strError;
    OwnerPark* ownerPark = new OwnerPark();

    createWheel(nameCorrectWheel, inventoryIdWheel_1, typeObjectWheel, typeWheel, radius, ss);
    CHECK(ownerPark->addObject(ss, strError));
    createWheel(nameCorrectWheel, inventoryIdWheel_2, typeObjectWheel, typeWheel, radius, ss);
    CHECK(ownerPark->addObject(ss, strError));

    SECTION("Correct Scooter Electric") {
        createElectricScooter(nameCorrectScooterElectric, inventoryId, simplicity, typeObjectScooterCorrect,
                              cntElectricity, inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(ownerPark->addObject(ss, strError));
        CHECK(ownerPark->getCntElectricity() == cntElectricity);
    }

    SECTION("Not Correct Scooter Electric, wrong with wheel used") {
        createElectricScooter(nameCorrectScooterElectric, inventoryId, simplicity, typeObjectScooterCorrect,
                              cntElectricity, inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(ownerPark->addObject(ss, strError));

        createElectricScooter(nameCorrectScooterElectric, inventoryId + 1, simplicity, typeObjectScooterCorrect,
                              cntElectricity, inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(!ownerPark->addObject(ss, strError));

        CHECK(ownerPark->getCntElectricity() == cntElectricity);
    }

    SECTION("Not correct Scooter Electric, wrong simplicity value") {
        createElectricScooter(nameCorrectScooterElectric, inventoryId, 15, typeObjectScooterCorrect,
                              cntElectricity, inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(!ownerPark->addObject(ss, strError));

        CHECK(ownerPark->getCntElectricity() == 0);
    }

    delete ownerPark;
}

TEST_CASE("ServiceCenter inspection via DI Container (Mock / Stub)", "[DI][ServiceCenter]") {
    std::string nameScooter = "scooter";
    std::string nameWheel = "wheel";
    std::string strError;
    std::stringstream ss;

    SECTION("Mock completely rejects addition of vehicles") {
        DIContainer container;
        container.registerSingleton<IServiceCenter, AlwaysRejectServiceCenterMock>();

        OwnerPark owner(container);

        createWheel(nameWheel, 10, (int)TypeObject::SparePart, 1, 10, ss);
        bool result = owner.addObject(ss, strError);

        CHECK_FALSE(result);
        CHECK(strError.find("Rejected by AlwaysRejectServiceCenterMock") != std::string::npos);
        CHECK(owner.getCntElectricity() == 0);
    }

    SECTION("Conditional mock rejects only defective vehicle by ID") {
        const int defectiveScooterId = 77;
        const int healthyScooterId = 88;

        DIContainer container;
        container.registerInstance<IServiceCenter>(
                std::make_shared<DefectiveIdServiceCenterMock>(defectiveScooterId)
        );

        OwnerPark owner(container);

        createWheel(nameWheel, 1, (int)TypeObject::SparePart, 1, 10, ss);
        CHECK(owner.addObject(ss, strError));
        createWheel(nameWheel, 2, (int)TypeObject::SparePart, 1, 10, ss);
        CHECK(owner.addObject(ss, strError));
        createWheel(nameWheel, 3, (int)TypeObject::SparePart, 1, 10, ss);
        CHECK(owner.addObject(ss, strError));
        createWheel(nameWheel, 4, (int)TypeObject::SparePart, 1, 10, ss);
        CHECK(owner.addObject(ss, strError));

        createScooter(nameScooter, defectiveScooterId, 5, (int)TypeObject::TransportNoElectric, 1, 2, 12, ss);
        CHECK_FALSE(owner.addObject(ss, strError));
        CHECK(strError.find("Defective unit detected") != std::string::npos);

        createScooter(nameScooter, healthyScooterId, 5, (int)TypeObject::TransportNoElectric, 3, 4, 12, ss);
        CHECK(owner.addObject(ss, strError));
    }
}

TEST_CASE("Behavior test: Beginner rules and energy calculation", "[Behavior]") {
    std::string nameScooter = "scooter";
    std::string nameElectric = "scooter_electric";
    std::string nameWheel = "wheel";
    std::stringstream ss;
    std::string strError;

    OwnerPark owner;

    createWheel(nameWheel, 101, (int)TypeObject::SparePart, 1, 10, ss);
    CHECK(owner.addObject(ss, strError));
    createWheel(nameWheel, 102, (int)TypeObject::SparePart, 1, 10, ss);
    CHECK(owner.addObject(ss, strError));

    createElectricScooter(nameElectric, 1, 8, (int)TypeObject::TransportElectric, 25, 101, 102, 14, ss);
    CHECK(owner.addObject(ss, strError));
    CHECK(owner.getCntElectricity() == 25);

    createWheel(nameWheel, 103, (int)TypeObject::SparePart, 1, 10, ss);
    CHECK(owner.addObject(ss, strError));
    createWheel(nameWheel, 104, (int)TypeObject::SparePart, 1, 10, ss);
    CHECK(owner.addObject(ss, strError));

    createElectricScooter(nameElectric, 2, 2, (int)TypeObject::TransportElectric, 40, 103, 104, 18, ss);
    CHECK(owner.addObject(ss, strError));

    CHECK(owner.getCntElectricity() == 65);
}

TEST_CASE("Test for Items on Balance: Helmet and ChargingStation", "[ItemsOnBalance]") {
    OwnerPark owner;
    std::string strError;
    std::stringstream ss;

    SECTION("Add Helmet on balance") {
        ss << "helmet 201 5 M";
        CHECK(owner.addObject(ss, strError));
        CHECK(owner.getCntElectricity() == 0);
    }

    SECTION("Add ChargingStation with energy consumption") {
        ss << "charging_station 301 3 150 10";
        CHECK(owner.addObject(ss, strError));
        CHECK(owner.getCntElectricity() == 150);
    }

    SECTION("Reject duplicate ID between transport and helmet") {
        ss << "helmet 500 5 L";
        CHECK(owner.addObject(ss, strError));

        std::stringstream ssWheel;
        ssWheel << "wheel 500 4 1 10";
        CHECK_FALSE(owner.addObject(ssWheel, strError));
        CHECK(strError.find("already in use") != std::string::npos);
    }
}