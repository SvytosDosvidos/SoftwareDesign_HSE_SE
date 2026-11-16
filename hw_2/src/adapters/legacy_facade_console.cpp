#include "pos_application_facade.h"
#include "parser.h"
#include <iostream>

void POSApplicationFacade::openStudyProgram(std::stringstream& input, std::string& errorStr) {
    std::string name;
    std::optional<std::string> description;
    if(Parser::parseStudyProgram(input, name, description, errorStr)) {
        openStudyProgram(name, description, errorStr);
    }
}

void POSApplicationFacade::appointLecturere(std::stringstream& input, std::string& errorStr) {
    int idPass;
    std::string name;
    if(Parser::parsePerson(input, idPass, name, errorStr)) {
        appointLecturere(idPass, name, errorStr);
    }
}

void POSApplicationFacade::enrollStudent(std::stringstream& input, std::string& errorStr) {
    int idPass;
    std::string name;
    if(Parser::parsePerson(input, idPass, name, errorStr)) {
        enrollStudent(idPass, name, errorStr);
    }
}

void POSApplicationFacade::addSubject(std::stringstream& input, std::string& errorStr) {
    std::string name;
    std::string nameStudyProgram;
    std::optional<std::string> description;
    if(Parser::parseSubject(input, name, nameStudyProgram, description, errorStr)) {
        addSubject(name, nameStudyProgram, description, errorStr);
    }
}

void POSApplicationFacade::addTeachSubject(std::stringstream& input, std::string& errorStr) {
    int idPassLecturer;
    std::string nameStudyProgram;
    std::string nameSubject;
    if(Parser::parseTeachSubject(input, idPassLecturer, nameStudyProgram, nameSubject, errorStr)) {
        addTeachSubject(idPassLecturer, nameStudyProgram, nameSubject, errorStr);
    }
}

void POSApplicationFacade::addStudyProgramStudent(std::stringstream& input, std::string& errorStr) {
    int idPassStudent;
    std::string nameStudyProgram;
    if(Parser::parseStudyProgramStudent(input, idPassStudent, nameStudyProgram, errorStr)) {
        addStudyProgramStudent(idPassStudent, nameStudyProgram, errorStr);
    }
}

void POSApplicationFacade::addAssessmentSubject(std::stringstream& input, std::string& errorStr) {
    std::string nameSubject;
    std::string nameStudyProgram;
    double weigth;
    std::optional<std::pair<int, int>> range;
    std::optional<std::string> description;

    if(Parser::parseAssessmentSubject(input, nameSubject, nameStudyProgram, weigth, range, description, errorStr)) {
        addAssessmentSubject(nameSubject, nameStudyProgram, weigth, range, description, errorStr);
    }
}

void POSApplicationFacade::printStudents() const {
    for(const auto& student : repository_->getAllStudents()) {
        std::cout << student->getIdPass() << " " << student->getName() << "\n";
    }
}

void POSApplicationFacade::printLecturers() const {
    for(const auto& lecturer : repository_->getAllLecturers()) {
        std::cout << lecturer->getIdPass() << "\n";
    }
}

