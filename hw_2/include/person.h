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

class ManagerUniversity : public IPersonUniversity {
public:
    ManagerUniversity(int idPass, std::string name);
    void printCommand() const;
    void printCommand4Add() const;
private:
    std::unique_ptr<ConsoleController> consoleController_;
};

class Lecturer : public IPersonUniversity {
public:
    Lecturer(int idPass, std::string name);
    void AddSubjectTeach();
private:
    std::vector<std::unique_ptr<Subject>> subjectsTeach_;
};

class Student : public IPersonUniversity {
public:
    Student(int idPass, std::string name);
    void AddEductionDirection();
private:
    std::vector<std::unique_ptr<EducationDirection>> educationDirections_;
};