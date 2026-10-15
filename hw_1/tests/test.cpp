#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../includes/OwnerPark.h"

Value OwnerPark::getCntElectricity() const {
    return park_->getCntElectricity();
}

void createWheel(std::string &name, int inventoryId, int simplicity,
    int typeObject, int typeWheel, Value radius, std::stringstream &ss) {
    if(!ss.str().empty()) {
        ss = std::stringstream();
    }

    ss << name << " ";
    ss << inventoryId << " ";
    ss << simplicity << " ";
    ss << typeObject << " ";
    ss << typeWheel << " ";
    ss << radius;
}

void createScooter(std::string &name, int inventoryId, int simplicity,
    int typeObject, int inventoryIdWheel_1, int inventoryIdWheel_2, Value weight,
        std::stringstream &ss) {
    if(!ss.str().empty()) {
        ss = std::stringstream();
    }

    ss << name << " ";
    ss << inventoryId << " ";
    ss << simplicity << " ";
    ss << typeObject << " ";
    ss << inventoryIdWheel_1 << " ";
    ss << inventoryIdWheel_2 << " ";
    ss << weight;
}

void createElectricScooter(std::string &name, int inventoryId, int simplicity,
    int typeObject, Value cntElectricity, int inventoryIdWheel_1, int inventoryIdWheel_2,
        Value weight, std::stringstream &ss) {
    if(!ss.str().empty()) {
        ss = std::stringstream();
    }

    ss << name << " ";
    ss << inventoryId << " ";
    ss << simplicity << " ";
    ss << typeObject << " ";
    ss << cntElectricity << " ";
    ss << inventoryIdWheel_1 << " ";
    ss << inventoryIdWheel_2 << " ";
    ss << weight;
}

TEST_CASE("Test for create Wheel", "[Create Wheel]") {
    /*
        std::string name;
        int inventoryId;
        int simplicity;
        TypeObject typeObject;
        TypeWheel typeWheel;
        Value radius;
    */

    std::string nameCorrect = "wheel";
    int inventoryId = 1, simplicity = 2;
    int typeObjectCorrect = (int)TypeObject::SparePart;
    int typeWheelCorrect = 1;
    Value radius = 15;

    OwnerPark* ownerPark = new OwnerPark();
    std::stringstream ss;
    std::string strError;
    SECTION("Correct wheel") {
        createWheel(nameCorrect, inventoryId, simplicity, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(ownerPark->addObject(ss, strError));

        createWheel(nameCorrect, inventoryId + 1, simplicity, typeObjectCorrect, typeWheelCorrect + 1, radius, ss);
        CHECK(ownerPark->addObject(ss, strError));
    }
    SECTION("Not Correct Wheel, wrong with name") {
        std::string nameNoCorrect = "wheel1";
        createWheel(nameNoCorrect, inventoryId, simplicity, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }
    SECTION("Not Correct Wheel, wrong with typeObject") {
        int typeObjectNoCorrect = 13;
        createWheel(nameCorrect, inventoryId, simplicity, typeObjectNoCorrect, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));

        createWheel(nameCorrect, inventoryId, simplicity, (int)TypeObject::Other, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));

        createWheel(nameCorrect, inventoryId, simplicity, (int)TypeObject::OtherElectric, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));

        createWheel(nameCorrect, inventoryId, simplicity, (int)TypeObject::TransportElectric, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));

        createWheel(nameCorrect, inventoryId, simplicity, (int)TypeObject::TransportNoElectric, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }
    SECTION("Not Correct Wheel, wrong with typeWheel") {
        int typeWheelNoCorrect = 3;
        createWheel(nameCorrect, inventoryId, simplicity, typeObjectCorrect, typeWheelNoCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }
    SECTION("Create 2 wheels with one id") {
        createWheel(nameCorrect, inventoryId, simplicity, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(ownerPark->addObject(ss, strError));

        createWheel(nameCorrect, inventoryId, simplicity, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));

        createWheel(nameCorrect, inventoryId + 1, simplicity, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(ownerPark->addObject(ss, strError));
    }

    delete ownerPark;
}

TEST_CASE("Test for create Scooter", "[Create Scooter]") {
    /*
        std::string name
        int inventoryId
        int simplicity
        TypeObject typeObject
        std::vector<Wheel*> wheels
        Value weight
    */
    std::string nameCorrectScooter = "scooter", nameCorrectWheel = "wheel";
    int inventoryId = 1, simplicity = 2;
    int typeObjectScooterCorrect = (int)TypeObject::TransportNoElectric;

    std::vector<Wheel*> wheels;
    Value weight = 15;

    int typeWheel = 1;
    int typeObjectWheel = (int)TypeObject::SparePart;
    Value radius = 5;

    int inventoryIdWheel_1 = 2;
    int inventoryIdWheel_2 = 3;

    std::stringstream ss;
    std::string strError;

    OwnerPark* ownerPark = new OwnerPark();

    createWheel(nameCorrectWheel, inventoryIdWheel_1, simplicity, typeObjectWheel, typeWheel, radius, ss);
    CHECK(ownerPark->addObject(ss, strError));
    createWheel(nameCorrectWheel, inventoryIdWheel_2, simplicity, typeObjectWheel, typeWheel, radius, ss);
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

        createScooter(nameCorrectScooter, inventoryId + 1, 10, typeObjectScooterCorrect,
                      inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }

    SECTION("Not Correct Scooter, wrong with wheel id used") {
        createScooter(nameCorrectScooter, inventoryId, simplicity, typeObjectScooterCorrect,
                      inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(ownerPark->addObject(ss, strError));

        createWheel(nameCorrectWheel, inventoryIdWheel_1, simplicity, typeObjectWheel, typeWheel, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));

        createWheel(nameCorrectWheel, inventoryIdWheel_2, simplicity, typeObjectWheel, typeWheel, radius, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }

    SECTION("Not correct Scooter, wrong with wheel is not simple") {
        createScooter(nameCorrectScooter, inventoryId, 10, typeObjectScooterCorrect,
                      inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(!ownerPark->addObject(ss, strError));
    }

    delete ownerPark;
}

TEST_CASE("Test for create electric Scooter", "[Create Electric Scooter]") {
    /*
        std::string name
        int inventoryId
        int simplicity
        TypeObject typeObject
        Value cntElectricity
        std::vector<Wheel*> wheels
        Value weight
    */
    std::string nameCorrectScooterElectric = "scooter_electric", nameCorrectWheel = "wheel";
    int inventoryId = 1, simplicity = 2;
    int typeObjectScooterCorrect = (int)TypeObject::TransportElectric;

    Value cntElectricity = 15;
    std::vector<Wheel*> wheels;
    Value weight = 15;

    int typeWheel = 1;
    int typeObjectWheel = (int)TypeObject::SparePart;
    Value radius = 5;

    int inventoryIdWheel_1 = 2;
    int inventoryIdWheel_2 = 3;

    std::stringstream ss;
    std::string strError;

    OwnerPark* ownerPark = new OwnerPark();

    createWheel(nameCorrectWheel, inventoryIdWheel_1, simplicity, typeObjectWheel, typeWheel, radius, ss);
    CHECK(ownerPark->addObject(ss, strError));
    createWheel(nameCorrectWheel, inventoryIdWheel_2, simplicity, typeObjectWheel, typeWheel, radius, ss);
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

    SECTION("Not correct Scooter Electric, wrong with wheel is not simple") {
        createElectricScooter(nameCorrectScooterElectric, inventoryId, 10, typeObjectScooterCorrect,
            cntElectricity, inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(!ownerPark->addObject(ss, strError));

        CHECK(ownerPark->getCntElectricity() == 0);
    }

    SECTION("Correct 2 Scooter Electric") {
        createElectricScooter(nameCorrectScooterElectric, inventoryId, simplicity, typeObjectScooterCorrect,
                              cntElectricity, inventoryIdWheel_1, inventoryIdWheel_2, weight, ss);
        CHECK(ownerPark->addObject(ss, strError));

        createWheel(nameCorrectWheel, 4, simplicity, typeObjectWheel, typeWheel, radius, ss);
        CHECK(ownerPark->addObject(ss, strError));
        createWheel(nameCorrectWheel, 5, simplicity, typeObjectWheel, typeWheel, radius, ss);
        CHECK(ownerPark->addObject(ss, strError));

        createElectricScooter(nameCorrectScooterElectric, 6, simplicity, typeObjectScooterCorrect,
                              cntElectricity, 4, 5, weight, ss);
        CHECK(ownerPark->addObject(ss, strError));
        CHECK(ownerPark->getCntElectricity() == 2 * cntElectricity);
    }

    delete ownerPark;
}