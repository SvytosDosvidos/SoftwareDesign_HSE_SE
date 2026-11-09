#pragma once

#include <format>
#include <memory>

#include "Park.h"
#include "StorageCenter.h"
#include "DIContainer.h"

class OwnerPark {
public:
    OwnerPark();
    explicit OwnerPark(const DIContainer& container);
    explicit OwnerPark(std::shared_ptr<IServiceCenter> serviceCenter);
    ~OwnerPark();

    void init();

    void printCommand() const;
    void printAllObjects() const;
    void printCommand4Add() const;

    bool addObject(std::stringstream& ss, std::string& strError);

    Value getCntElectricity() const; // for test
private:
    Park* park_;
    std::map<std::string, std::string> mapCommand_;
};