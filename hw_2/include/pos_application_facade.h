#pragma once

#include "person.h"

class POSApplicationFacade {
public:
    POSApplicationFacade() = default;
    void addEducationDirection();
    void addLecturere();
    void addStudent();
private:
    std::vector<std::unique_ptr<Lecturer>> lecturers_;
    std::vector<std::unique_ptr<EducationDirection>> educationDirections_;
};