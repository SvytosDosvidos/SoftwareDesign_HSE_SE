#include "../include/person.h"

IPersonUniversity::IPersonUniversity(int idPass, std::string name) :
    idPass_(idPass), name_(name) {}

Lecturer::Lecturer(int idPass, std::string name) :
    IPersonUniversity(idPass, name) {}

void Lecturer::addSubjectTeach() {

}

Student::Student(int idPass, std::string name) :
    IPersonUniversity(idPass, name) {}