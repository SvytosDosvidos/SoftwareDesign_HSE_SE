#pragma once

#include "academic_subject.h"

#include <string>
#include <vector>
#include <memory>

class IPersonUniversity {
public:
    IPersonUniversity(int idPass, std::string name);
    virtual ~IPersonUniversity() = default;

    int getIdPass() const;
protected:
    int idPass_;
    std::string name_;
};

class Lecturer : public IPersonUniversity {
public:
    ~Lecturer() override = default;
    Lecturer(int idPass, std::string name);
    void addSubjectTeach();
private:
    std::vector<std::shared_ptr<Subject>> subjectsTeach_;
};

class Student : public IPersonUniversity {
public:
    ~Student() override = default;
    Student(int idPass, std::string name);
    void addEductionDirection();
private:
    std::vector<std::unique_ptr<StudyProgram>> educationDirections_;
};