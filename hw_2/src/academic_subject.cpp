#include "../include/academic_subject.h"

Subject::Subject(std::string name, std::string nameStudyProgram,
                 std::optional<std::string> description) : name_(name), nameStudyProgram_(nameStudyProgram),
                                                           description_(description) {}

void Subject::addAssessmentSubject(std::unique_ptr<AssessmentSubject>& assessmentSubject) {
    assessmentSubject_ = std::move(assessmentSubject);
}

std::string Subject::getName() const {
    return name_;
}

StudyProgram::StudyProgram(std::string name,
                           std::optional<std::string> description) :
        name_(name), description_(description) {}

void StudyProgram::addSubject(std::shared_ptr<Subject>& subject) {
    subjects_.push_back(subject);
}

std::string StudyProgram::getNameStudyProgram() const {
    return name_;
}

std::optional<int> StudyProgram::getIndSubject(const std::string& name) const {
    for(size_t i = 0; i < subjects_.size(); ++i) {
        if(subjects_[i]->getName() == name) {
            return static_cast<int>(i);
        }
    }

    return std::nullopt;
}

const std::vector<std::shared_ptr<Subject>>& StudyProgram::getSubjects() const {
    return subjects_;
}