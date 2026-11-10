#include "../include/academic_subject.h"

Subject::Subject(std::string name, std::optional<std::string> description,
    std::string nameProgramReading) : name_(name), description_(description),
    nameProgramReading_(nameProgramReading) {}

EducationDirection::EducationDirection(int idDirection, std::string name,
    std::optional<std::string> description) : idDirection_(idDirection),
    name_(name), description_(description) {}

void EducationDirection::addSubject(std::string name, std::optional<std::string> description,
    std::string nameProgramReading) {
        //if(add subject)
        subjects_.push_back(std::make_unique<Subject>(name, description, nameProgramReading));
    }