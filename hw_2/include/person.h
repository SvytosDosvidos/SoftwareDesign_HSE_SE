#pragma once

#include "academic_subject.h"
#include "console_controller.h"

#include <string>
#include <vector>
#include <memory>

class IPersonUniversity {
public:
    IPersonUniversity(int idPass, std::string name);
    virtual ~IPersonUniversity() = 0;

protected:
    int idPass_;
    std::string name_;
};

class Lecturer : public IPersonUniversity {
public:
    Lecturer(int idPass, std::string name);
    void addSubjectTeach();
private:
    std::vector<std::unique_ptr<Subject>> subjectsTeach_;
};

class Student : public IPersonUniversity {
public:
    Student(int idPass, std::string name);
    void addEductionDirection();
private:
    std::vector<std::unique_ptr<EducationDirection>> educationDirections_;
};