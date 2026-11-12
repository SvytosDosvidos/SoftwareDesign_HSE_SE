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

    if(!checkUniqueIdProgram(idPass)) {
        errorStr += "not unique idPass\n";
        return;
    }

    lecturers_.push_back(std::make_unique<Lecturer>(idPass, name));
}

void POSApplicationFacade::enrollStudent(std::stringstream& input, std::string& errorStr) {

}

bool POSApplicationFacade::checkUniqueIdPass(int idPass) {
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

bool POSApplicationFacade::checkUniqueNameSubject(std::string name) {

}

bool POSApplicationFacade::checkUniqueIdProgram(int idStudyProgam) {
    for(const auto &program : studyPrograms_) {
        if(program->getIdStudyProgam() == idStudyProgam) {
            return false;
        }
    }

    return true;
}


void POSApplicationFacade::printStudents() const {

}

void POSApplicationFacade::printLecturers() const {

}