#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../includes/OwnerPark.h"

void createWheel(std::string &name, int inventoryId, int simplicity,
    int typeObject, int typeWheel, Value radius, std::stringstream &ss)
{
    ss << name << " ";
    ss << inventoryId << " ";
    ss << simplicity << " ";
    ss << typeObject << " ";
    ss << typeWheel << " ";
    ss << radius;
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
    int typeObjectCorrect = 4;
    int typeWheelCorrect = 1;
    Value radius = 15;

    OwnerPark* ownerPark = new OwnerPark();
    std::stringstream ss;

    SECTION("Correct wheel") {
        createWheel(nameCorrect, inventoryId, simplicity, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(ownerPark->addObject(ss));
    }
    SECTION("Not Correct Wheel, wrong with name") {
        std::string nameNoCorrect = "wheel1";
        createWheel(nameNoCorrect, inventoryId, simplicity, typeObjectCorrect, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss));
    }
    SECTION("Not Correct Wheel, wrong with typeObject") {
        int typeObjectNoCorrect = 13;
        createWheel(nameCorrect, inventoryId, simplicity, typeObjectNoCorrect, typeWheelCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss));
    }
    SECTION("Not Correct Wheel, wrong with typeWheel") {
        int typeWheelNoCorrect = 3;
        createWheel(nameCorrect, inventoryId, simplicity, typeObjectCorrect, typeWheelNoCorrect, radius, ss);
        CHECK(!ownerPark->addObject(ss));
    }

    delete ownerPark;
}