#pragma once

#include <string>
#include <vector>
#include <memory>
#include "academic_subject.h"

class IPerson {
public:

    virtual ~IPerson() = 0;
private:
    std::string name_;
};

class Lecturer : public IPerson {
public:

private:
    std::vector<std::unique_ptr<Subject>> subjectsTeach_;
};

class Student : public IPerson {
public:

private:
    std::vector<std::unique_ptr<EducationDirection>> educationDirections_;
};