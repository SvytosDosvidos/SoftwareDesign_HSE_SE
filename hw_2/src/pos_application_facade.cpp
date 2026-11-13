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

    if(!checkUniqueNameSubject(nameStudyProgram)) {
        errorStr += "not unique nameStudyProgram\n";
        return;
    }

    std::shared_ptr<Subject> subject = std::make_shared<Subject>(Subject(name, nameStudyProgram, description));
    studyPrograms_[indStudyProgam.value()]->addSubject(subject);
}

void POSApplicationFacade::addTeachSubject(std::stringstream& input, std::string& errorStr) {
    std::string nameSubject;
    std::string nameStudyProgram;
    if(!(input >> nameSubject)) {
        errorStr += "invalid nameSubject value\n";
        return;
    }

    if(!(input >> nameStudyProgram)) {
        errorStr += "invalid nameStudyProgram value\n";
        return;
    }


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

bool POSApplicationFacade::checkUniqueNameSubject(std::string name) const {
    for(const auto &program : studyPrograms_) {
        for(const auto& subject : program->getSubjects()) {
            if(subject->getName() == name) {
                return false;
            }
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

std::optional<int> POSApplicationFacade::getIndStudyProgram(std::string nameStudyProgam) const {
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