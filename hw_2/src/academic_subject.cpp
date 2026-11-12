#include "../include/academic_subject.h"

Subject::Subject(std::string name, std::optional<std::string> description,
    std::string nameProgramReading) : name_(name), description_(description),
    nameProgramReading_(nameProgramReading) {}

StudyProgram::StudyProgram(int idStudyProgam, std::string name,
    std::optional<std::string> description) : idStudyProgam_(idStudyProgam),
    name_(name), description_(description) {}

void StudyProgram::addSubject(std::string name, std::optional<std::string> description,
    std::string nameProgramReading) {
        //if(add subject)
        subjects_.push_back(std::make_unique<Subject>(name, description, nameProgramReading));
    }

int StudyProgram::getIdStudyProgam() const {
    return idStudyProgam_;
}