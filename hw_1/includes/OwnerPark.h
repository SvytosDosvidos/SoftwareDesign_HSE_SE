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
private:
    Park* park_;
    ServiceCenter* serviceCenter_;
};