#pragma once

#include <vector>
#include <functional>

#include "person.h"
#include "academic_subject.h"

class University {
public:
    University() = default;
    void addManagerUniversity();
    void addLecturere();
    void addEducationDirection();
private:
    std::unique_ptr<ManagerUniversity> managerUniversity_;
    std::vector<std::unique_ptr<Lecturer>> lecturers_;
    std::vector<std::unique_ptr<EducationDirection>> educationDirections_;
};