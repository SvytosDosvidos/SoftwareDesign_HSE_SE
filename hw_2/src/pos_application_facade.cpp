#include "../include/pos_application_facade.h"

#include <stdexcept>

POSApplicationFacade::POSApplicationFacade(std::shared_ptr<IPOSRepository> repository) :
        repository_(repository) {
    if(!repository_) throw std::invalid_argument("repository must not be null");
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
    if(name.find_first_not_of(" \t\r\n") == std::string::npos) {
        errorStr += "invalid person id or name";
        return false;
    }
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
    if(idPass < 0 || name.find_first_not_of(" \t\r\n") == std::string::npos) {
        errorStr += "invalid person id or name";
        return false;
    }
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
    try {
        auto assessment = std::make_unique<AssessmentSubject>(weigth, range, description);
        subject->addAssessmentSubject(std::move(assessment));
    } catch(const std::invalid_argument& error) {
        errorStr += error.what();
        return false;
    }

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

std::shared_ptr<Subject> POSApplicationFacade::findSubject(
    const std::string& program, const std::string& subject) const {
    auto studyProgram = repository_->findStudyProgram(program);
    if(!studyProgram) {
        throw std::invalid_argument("studyProgram does not exist");
    }
    auto index = studyProgram->getIndSubject(subject);
    if(!index) {
        throw std::invalid_argument("subject does not exist");
    }
    return studyProgram->getSubjects()[*index];
}

void POSApplicationFacade::addCriterion(const std::string& program, const std::string& subject,
    const std::string& criterion, int maxScore, double weight) {
    findSubject(program, subject)->addCriterion(criterion, maxScore, weight);
}

void POSApplicationFacade::setEvaluation(const std::string& program, const std::string& subject,
    int studentId, const std::string& criterion, int score) {
    if(!repository_->existsStudent(studentId)) {
        throw std::invalid_argument("student does not exist");
    }
    findSubject(program, subject)->setEvaluation(studentId, criterion, score);
}

FinalScore POSApplicationFacade::calculateFinal(const std::string& program, const std::string& subject,
    int studentId, const IMissingEvaluationStrategy& strategy) const {
    if(!repository_->existsStudent(studentId)) {
        throw std::invalid_argument("student does not exist");
    }
    return FinalScoreService(strategy).calculate(*findSubject(program, subject), studentId);
}