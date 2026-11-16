#include "../include/academic_subject.h"

#include <stdexcept>

Subject::Subject(std::string name, std::string nameStudyProgram,
                 std::optional<std::string> description) : name_(name), nameStudyProgram_(nameStudyProgram),
                                                           description_(description) {}

void Subject::addAssessmentSubject(std::unique_ptr<AssessmentSubject>&& assessmentSubject) {
    if(!assessmentSubject) {
        throw std::invalid_argument("assessment must not be null");
    }
    const auto range = assessmentSubject->getRange();
    for(const auto& [key, score] : evaluations_) {
        if(key.second == "default" && (score.value() < range.first || score.value() > range.second)) {
            throw std::invalid_argument("new range excludes existing evaluations");
        }
    }
    criteria_.insert_or_assign("default", *assessmentSubject);
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

const AssessmentSubject* Subject::getAssessmentSubject() const {
    auto it = criteria_.find("default");
    return it == criteria_.end() ? nullptr : &it->second;
}

void Subject::addCriterion(const std::string& name, int maxScore, double weight) {
    if(name.find_first_not_of(" \t\r\n") == std::string::npos || maxScore <= 0) {
        throw std::invalid_argument("criterion needs a name and positive max score");
    }
    if(criteria_.contains(name)) {
        throw std::invalid_argument("criterion already exists");
    }
    criteria_.emplace(name, AssessmentSubject(weight, std::make_pair(0, maxScore), std::nullopt));
}

void Subject::setEvaluation(int studentId, const std::string& criterion, int score) {
    auto it = criteria_.find(criterion);
    if(studentId < 0 || it == criteria_.end()) {
        throw std::invalid_argument("invalid student id or unknown criterion");
    }
    const auto range = it->second.getRange();
    const auto evaluation = EvaluationFactory::create(studentId, score, range);
    evaluations_.insert_or_assign(std::make_pair(studentId, criterion), evaluation);
}

std::optional<int> Subject::getEvaluation(int studentId, const std::string& criterion) const {
    auto it = evaluations_.find(std::make_pair(studentId, criterion));
    return it == evaluations_.end() ? std::nullopt : std::optional<int>(it->second.value());
}

const std::map<std::string, AssessmentSubject>& Subject::getCriteria() const {
    return criteria_;
}

void Subject::cancelEvaluation(int studentId, const std::string& criterion) {
    if(studentId < 0 || !criteria_.contains(criterion)) {
        throw std::invalid_argument("invalid student id or unknown criterion");
    }
    evaluations_.erase({studentId, criterion});
}
