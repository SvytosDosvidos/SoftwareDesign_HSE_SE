#include "../include/pos_application_facade.h"
#include "../include/parser.h"

#include <iostream>

POSApplicationFacade::POSApplicationFacade() :
        repository_(std::make_shared<InMemoryPOSRepository>()) {}

POSApplicationFacade::POSApplicationFacade(std::shared_ptr<IPOSRepository> repository) :
        repository_(repository) {}

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

bool POSApplicationFacade::openStudyProgram(const std::string& name, const std::optional<std::string>& description, std::string& errorStr) {
    if(repository_->existsStudyProgram(name)) {
        errorStr += "not unique nameStudyProgram";
        return false;
    }
    repository_->saveStudyProgram(std::make_shared<StudyProgram>(name, description));
    return true;
}

bool POSApplicationFacade::appointLecturere(int idPass, const std::string& name, std::string& errorStr) {
    if(idPass < 0) {
        errorStr += "invalid IdPass value(>0)";
        return false;
    }
    if(repository_->existsLecturer(idPass) || repository_->existsStudent(idPass)) {
        errorStr += "not unique idPass";
        return false;
    }
    repository_->saveLecturer(std::make_shared<Lecturer>(idPass, name));
    return true;
}

bool POSApplicationFacade::enrollStudent(int idPass, const std::string& name, std::string& errorStr) {
    if(repository_->existsStudent(idPass) || repository_->existsLecturer(idPass)) {
        errorStr += "not unique idPass";
        return false;
    }
    repository_->saveStudent(std::make_shared<Student>(idPass, name));
    return true;
}

bool POSApplicationFacade::addSubject(const std::string& name, const std::string& nameStudyProgram, const std::optional<std::string>& description, std::string& errorStr) {
    auto program = repository_->findStudyProgram(nameStudyProgram);
    if(!program) {
        errorStr += "there is no such nameStudyProgram";
        return false;
    }
    if(program->getIndSubject(name).has_value()) {
        errorStr += "not unique name";
        return false;
    }
    auto subject = std::make_shared<Subject>(name, nameStudyProgram, description);
    program->addSubject(subject);
    return true;
}

bool POSApplicationFacade::addTeachSubject(int idPassLecturer, const std::string& nameStudyProgram, const std::string& nameSubject, std::string& errorStr) {
    auto lecturer = repository_->findLecturer(idPassLecturer);
    if(!lecturer) {
        errorStr += "lecturer does not exist";
        return false;
    }
    auto program = repository_->findStudyProgram(nameStudyProgram);
    if(!program) {
        errorStr += "studyProgram does not exist";
        return false;
    }
    auto indSubject = program->getIndSubject(nameSubject);
    if(!indSubject.has_value()) {
        errorStr += "subject does not exist";
        return false;
    }
    lecturer->addSubjectTeach(program->getSubjects()[indSubject.value()]);
    return true;
}

bool POSApplicationFacade::addStudyProgramStudent(int idPassStudent, const std::string& nameStudyProgram, std::string& errorStr) {
    auto student = repository_->findStudent(idPassStudent);
    if(!student) {
        errorStr += "student does not exist";
        return false;
    }
    auto program = repository_->findStudyProgram(nameStudyProgram);
    if(!program) {
        errorStr += "studyProgram does not exist";
        return false;
    }
    student->addStudyProgram(program);
    return true;
}

bool POSApplicationFacade::addAssessmentSubject(const std::string& nameSubject, const std::string& nameStudyProgam,
    double weigth, std::optional<std::pair<int, int>> range,
    std::optional<std::string>& description, std::string& errorStr) {

    auto studyProgram = repository_->findStudyProgram(nameStudyProgam);
    if(!studyProgram) {
        errorStr += "studyProgram does not exist";
        return false;
    }

    auto indSubject = studyProgram->getIndSubject(nameSubject);
    if(!indSubject.has_value()) {
        errorStr += "subject does not exist";
        return false;
    }

    auto subject = studyProgram->getSubjects()[indSubject.value()];
    subject->addAssessmentSubject(std::make_unique<AssessmentSubject>(weigth, range, description));

    return true;
}

size_t POSApplicationFacade::getCntSubjectInStudyProgram(const std::string& nameStudyProgram) const {
    auto program = repository_->findStudyProgram(nameStudyProgram);
    if(program) {
        return program->getSubjects().size();
    }
    return 0;
}

size_t POSApplicationFacade::getCntLecturers() const {
    return repository_->getCntLecturers();
}

void POSApplicationFacade::printStudents() const {
    for(const auto& student : repository_->getAllStudents()) {
        std::cout << student->getIdPass() << "\n";
    }
}

void POSApplicationFacade::printLecturers() const {
    for(const auto& lecturer : repository_->getAllLecturers()) {
        std::cout << lecturer->getIdPass() << "\n";
    }
}