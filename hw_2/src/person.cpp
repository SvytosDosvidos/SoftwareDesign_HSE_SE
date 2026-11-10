#include "../include/person.h"

IPersonUniversity::IPersonUniversity(int idPass, std::string name) :
    idPass_(idPass), name_(name) {}

ManagerUniversity::ManagerUniversity(int idPass, std::string name) :
        IPersonUniversity(idPass, name) {}

Lecturer::Lecturer(int idPass, std::string name) :
    IPersonUniversity(idPass, name) {}

Student::Student(int idPass, std::string name) :
    IPersonUniversity(idPass, name) {}