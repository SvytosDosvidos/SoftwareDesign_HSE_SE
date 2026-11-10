#pragma once

#include "person.h"
#include "academic_subject.h"

#include<memory>

class POSApplicationFacade {
public:
    POSApplicationFacade() = default;
    void addEducationDirection();
    void addLecturere();
    void addStudent();

    void printStudents() const;
    void printLecturers() const;
private:
    std::vector<std::unique_ptr<Lecturer>> lecturers_;
    std::vector<std::unique_ptr<EducationDirection>> educationDirections_;
};