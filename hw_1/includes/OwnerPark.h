#pragma once

#include "Park.h"
#include "StorageCenter.h"

class OwnerPark {
public:
    OwnerPark();
    ~OwnerPark();

    void init();

    void printCommand() const;
    void printAllObjects() const;
    void printCommand4Add() const;

    bool addObject(std::stringstream& ss, std::string& strError);
private:
    Park* park_;
    std::map<std::string, std::string> mapCommand_;
};