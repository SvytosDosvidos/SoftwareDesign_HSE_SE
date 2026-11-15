#include "../include/pos_application_facade.h"

void POSApplicationFacade::openStudyProgram(std::stringstream& input, std::string& errorStr) {
    std::string name;
    std::string descriptionStr;
    std::optional<std::string> description;
    if(!(input >> name)) {
        errorStr += "invalid name value";
        return;
    }
    input >> descriptionStr;
    if(!descriptionStr.empty()) {
        description = descriptionStr;
    }

    if(!checkUniqueNameStudyProgram(name)) {
        errorStr += "not unique nameStudyProgram";
        return;
    }
    studyPrograms_.push_back(std::make_unique<StudyProgram>(name, description));
}

void POSApplicationFacade::appointLecturere(std::stringstream& input, std::string& errorStr) {
    int idPass;
    std::string name;
    if(!(input >> idPass)) {
        errorStr += "invalid idPass value";
        return;
    }
    if(!(input >> name)) {
        errorStr += "invalid name value";
        return;
    }

    if(!checkUniqueIdPass(idPass)) {
        errorStr += "not unique idPass";
        return;
    }

    lecturers_.push_back(std::make_unique<Lecturer>(idPass, name));
}

void POSApplicationFacade::enrollStudent(std::stringstream& input, std::string& errorStr) {
    int idPass;
    std::string name;
    if(!(input >> idPass)) {
        errorStr += "invalid idPass value";
        return;
    }
    if(!(input >> name)) {
        errorStr += "invalid name value";
        return;
    }

    if(!checkUniqueIdPass(idPass)) {
        errorStr += "not unique idPass";
        return;
    }

    students_.push_back(std::make_unique<Student>(idPass, name));
}

void POSApplicationFacade::addSubject(std::stringstream& input, std::string& errorStr) {
    std::string name;
    std::string nameStudyProgram;
    std::optional<std::string> description;
    std::string descriptionStr;
    if(!(input >> name)) {
        errorStr += "invalid name value";
        return;
    }

    if(!(input >> nameStudyProgram)) {
        errorStr += "invalid nameStudyProgram value";
        return;
    }

    input >> descriptionStr;
    description = descriptionStr;

    std::optional<int> indStudyProgam = getIndStudyProgram(nameStudyProgram);
    if(!indStudyProgam.has_value()) {
        errorStr += "there is no such nameStudyProgram";
        return;
    }

    if(!checkUniqueNameSubject(name, indStudyProgam.value())) {
        errorStr += "not unique name";
        return;
    }

    std::shared_ptr<Subject> subject = std::make_shared<Subject>(Subject(name, nameStudyProgram, description));
    studyPrograms_[indStudyProgam.value()]->addSubject(subject);
}

void POSApplicationFacade::addTeachSubject(std::stringstream& input, std::string& errorStr) {
    int idPassLecturer;
    std::string nameStudyProgram;
    std::string nameSubject;

    if(!(input >> idPassLecturer)) {
        errorStr += "invalid idPassLecturer value";
        return;
    }

    if(!(input >> nameStudyProgram)) {
        errorStr += "invalid nameStudyProgram value";
        return;
    }

    if(!(input >> nameSubject)) {
        errorStr += "invalid nameSubject value";
        return;
    }

    std::optional<int> indLecturer = getIndLecturer(idPassLecturer);
    if(!indLecturer.has_value()) {
        errorStr += "lecturer does not exist";
        return;
    }

    std::optional<int> indStudyProgram = getIndStudyProgram(nameStudyProgram);
    if(!indStudyProgram.has_value()) {
        errorStr += "studyProgram does not exist";
        return;
    }

    std::optional<int> indSubject = studyPrograms_[indStudyProgram.value()]->getIndSubject(nameSubject);
    if(!indSubject.has_value()) {
        errorStr += "subject does not exist";
        return;
    }

    lecturers_[indLecturer.value()]->addSubjectTeach((
        studyPrograms_[indStudyProgram.value()]->getSubjects())[indSubject.value()]);
}

void POSApplicationFacade::addStudyProgramStudent(std::stringstream& input, std::string& errorStr) {
    int idPassStudent;
    std::string nameStudyProgram;

    if(!(input >> idPassStudent)) {
        errorStr += "invalid name idPassStudent";
        return;
    }

    if(!(input >> nameStudyProgram)) {
        errorStr += "invalid nameStudyProgram value";
        return;
    }

    std::optional<int> indStudent = getIndStudent(idPassStudent);
    if(!indStudent.has_value()) {
        errorStr += "student does not exist";
        return;
    }

    std::optional<int> indStudyProgram = getIndStudyProgram(nameStudyProgram);
    if(!indStudyProgram.has_value()) {
        errorStr += "studyProgram does not exist";
        return;
    }

    students_[indStudent.value()]->addStudyProgram(studyPrograms_[indStudyProgram.value()]);
}

bool POSApplicationFacade::checkUniqueIdPass(int idPass) const {
    for(const auto &lecturer : lecturers_) {
        if(lecturer->getIdPass() == idPass) {
            return false;
        }
    }

    for(const auto &student : students_) {
        if(student->getIdPass() == idPass) {
            return false;
        }
    }

    return true;
}

size_t POSApplicationFacade::getCntSubjectInStudyProgram(std::string&& nameStudyProgram) const {
    for(const auto&studyProgram : studyPrograms_) {
        if(studyProgram->getNameStudyProgram() == nameStudyProgram) {
            return studyProgram->getSubjects().size();
        }
    }

    return 0;
}

bool POSApplicationFacade::checkUniqueNameSubject(const std::string& name, int indStudyProgam) const {
    for(const auto& subject : studyPrograms_[indStudyProgam]->getSubjects()) {
        if(subject->getName() == name) {
            return false;
        }
    }

    return true;
}

bool POSApplicationFacade::checkUniqueNameStudyProgram(const std::string &name) const {
    for(const auto &program : studyPrograms_) {
        if(program->getNameStudyProgram() == name) {
            return false;
        }
    }

    return true;
}

std::optional<int> POSApplicationFacade::getIndLecturer(int idLecturer) const {
    for(size_t i = 0; i < lecturers_.size(); ++i) {
        if(lecturers_[i]->getIdPass() == idLecturer) {
            return i;
        }
    }

    return std::nullopt;
}

std::optional<int> POSApplicationFacade::getIndStudent(int idStudent) const {
    for(size_t i = 0; i < students_.size(); ++i) {
        if(students_[i]->getIdPass() == idStudent) {
            return i;
        }
    }

    return std::nullopt;
}

std::optional<int> POSApplicationFacade::getIndStudyProgram(const std::string& nameStudyProgam) const {
    for(size_t i = 0; i < studyPrograms_.size(); ++i) {
        if(studyPrograms_[i]->getNameStudyProgram() == nameStudyProgam) {
            return static_cast<int>(i);
        }
    }

    return std::nullopt;
}

void POSApplicationFacade::printStudents() const {

}

void POSApplicationFacade::printLecturers() const {

}