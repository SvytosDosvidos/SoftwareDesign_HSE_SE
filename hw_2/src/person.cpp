#include "../include/person.h"
#include <stdexcept>

IPersonUniversity::IPersonUniversity(int idPass, std::string name) :
        idPass_(idPass), name_(name) {
    if(idPass < 0 || name.find_first_not_of(" \t\r\n") == std::string::npos)
        throw std::invalid_argument("person needs a nonnegative id and a name");
}

int IPersonUniversity::getIdPass() const {
    return idPass_;
}

Lecturer::Lecturer(int idPass, std::string name) :
        IPersonUniversity(idPass, name) {}

void Lecturer::addSubjectTeach(std::shared_ptr<Subject> subjectTeach) {
    subjectsTeach_.push_back(std::move(subjectTeach));
}

Student::Student(int idPass, std::string name) :
        IPersonUniversity(idPass, name) {}

void Student::addStudyProgram(std::shared_ptr<StudyProgram> studyProgram) {
    studyPrograms_.push_back(std::move(studyProgram));
}