#include "../include/pos_application_facade.h"

void POSApplicationFacade::openStudyProgram(std::stringstream& input, std::string& errorStr) {
    int idStudyProgam;
    std::string name;
    std::string descriptionStr;
    std::optional<std::string> description;
    if(!(input >> idStudyProgam)) {
        errorStr += "invalid idDirection value\n";
        return;
    }
    if(!(input >> name)) {
        errorStr += "invalid name value\n";
        return;
    }
    input >> descriptionStr;
    if(!descriptionStr.empty()) {
        description = descriptionStr;
    }

    if(!checkUniqueIdProgram(idStudyProgam)) {
        errorStr += "not unique idStudyProgam\n";
        return;
    }
    studyPrograms_.push_back(std::make_unique<StudyProgram>(idStudyProgam, name, description));
}

void POSApplicationFacade::appointLecturere(std::stringstream& input, std::string& errorStr) {
    int idPass;
    std::string name;
    if(!(input >> idPass)) {
        errorStr += "invalid idPass value\n";
        return;
    }
    if(!(input >> name)) {
        errorStr += "invalid name value\n";
        return;
    }

    if(!checkUniqueIdPass(idPass)) {
        errorStr += "not unique idPass\n";
        return;
    }

    lecturers_.push_back(std::make_unique<Lecturer>(idPass, name));
}

void POSApplicationFacade::enrollStudent(std::stringstream& input, std::string& errorStr) {
    int idPass;
    std::string name;
    if(!(input >> idPass)) {
        errorStr += "invalid idPass value\n";
        return;
    }
    if(!(input >> name)) {
        errorStr += "invalid name value\n";
        return;
    }

    if(!checkUniqueIdPass(idPass)) {
        errorStr += "not unique idPass\n";
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
        errorStr += "invalid name value\n";
        return;
    }

    if(!(input >> nameStudyProgram)) {
        errorStr += "invalid nameStudyProgram value\n";
        return;
    }

    input >> descriptionStr;
    description = descriptionStr;

    std::optional<int> indStudyProgam = getIndStudyProgram(nameStudyProgram);
    if(!indStudyProgam.has_value()) {
        errorStr += "there is no such nameStudyProgram\n";
        return;
    }

    if(!checkUniqueNameSubject(name, indStudyProgam.value())) {
        errorStr += "not unique name\n";
        return;
    }

    std::shared_ptr<Subject> subject = std::make_shared<Subject>(Subject(name, nameStudyProgram, description));
    studyPrograms_[indStudyProgam.value()]->addSubject(subject);
}

void POSApplicationFacade::addTeachSubject(std::stringstream& input, std::string& errorStr) {
    std::string nameLecturer;
    std::string nameStudyProgram;
    std::string nameSubject;

    if(!(input >> nameLecturer)) {
        errorStr += "invalid nameLecturer value\n";
        return;
    }

    if(!(input >> nameStudyProgram)) {
        errorStr += "invalid nameStudyProgram value\n";
        return;
    }

    if(!(input >> nameSubject)) {
        errorStr += "invalid nameSubject value\n";
        return;
    }

    std::optional<int> indLecturer = getIndLecturer(nameLecturer);
    if(!indLecturer.has_value()) {
        errorStr += "lecturer does not exist\n";
        return;
    }

    std::optional<int> indStudyProgram = getIndStudyProgram(nameStudyProgram);
    if(!indStudyProgram.has_value()) {
        errorStr += "studyProgram does not exist\n";
        return;
    }

    std::optional<int> indSubject = studyPrograms_[indStudyProgram.value()]->getIndSubject(nameSubject);
    if(!indSubject.has_value()) {
        errorStr += "subject does not exist\n";
        return;
    }

    lecturers_[indLecturer.value()]->addSubjectTeach((
        studyPrograms_[indStudyProgram.value()]->getSubjects())[indSubject.value()]);
}

void POSApplicationFacade::addStudyProgramStudent(std::stringstream& input, std::string& errorStr) {

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

bool POSApplicationFacade::checkUniqueNameSubject(std::string& name, int indStudyProgam) const {
    for(const auto& subject : studyPrograms_[indStudyProgam]->getSubjects()) {
        if(subject->getName() == name) {
            return false;
        }
    }

    return true;
}

bool POSApplicationFacade::checkUniqueIdProgram(int idStudyProgam) const {
    for(const auto &program : studyPrograms_) {
        if(program->getIdStudyProgam() == idStudyProgam) {
            return false;
        }
    }

    return true;
}

std::optional<int> POSApplicationFacade::getIndLecturer(std::string& nameLecturer) const {
    for(size_t i = 0; i < lecturers_.size(); ++i) {
        if(lecturers_[i]->getName() == nameLecturer) {
            return i;
        }
    }

    return std::nullopt;
}

std::optional<int> POSApplicationFacade::getIndStudyProgram(std::string& nameStudyProgam) const {
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