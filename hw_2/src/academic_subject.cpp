#include "../include/academic_subject.h"

Subject::Subject(std::string name, std::string nameStudyProgram,
    std::optional<std::string> description) : name_(name), nameStudyProgram_(nameStudyProgram),
        description_(description) {}

std::string Subject::getName() const {
    return name_;
}

StudyProgram::StudyProgram(int idStudyProgam, std::string name,
    std::optional<std::string> description) : idStudyProgam_(idStudyProgam),
    name_(name), description_(description) {}

void StudyProgram::addSubject(std::shared_ptr<Subject>& subject) {
    subjects_.push_back(subject);
}

int StudyProgram::getIdStudyProgam() const {
    return idStudyProgam_;
}

std::string StudyProgram::getNameStudyProgram() const {
    return name_;
}

const std::vector<std::shared_ptr<Subject>>& StudyProgram::getSubjects() const {
    return subjects_;
}