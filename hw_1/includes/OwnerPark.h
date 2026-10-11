#pragma once

#include "Park.h"
#include "ServiceCenter.h"

class OwnerPark {
public:
    OwnerPark();
    ~OwnerPark();

    void printCommand() const;
    void printAllObjects() const;
    void printCommand4Add() const;

    bool addObject(std::stringstream& ss);
private:
    Park* park_;
    ServiceCenter* serviceCenter_;
};