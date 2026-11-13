#include "../include/person.h"

IPersonUniversity::IPersonUniversity(int idPass, std::string name) :
    idPass_(idPass), name_(name) {}

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