#pragma once

#include "assessment_subject.h"
#include "domain/evaluation.h"

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <map>

class Subject {
public:
    Subject(std::string name, std::string nameProgramReading,
            std::optional<std::string> description);

    void addAssessmentSubject(std::unique_ptr<AssessmentSubject>&& assessmentSubject);

    std::string getName() const;
    const AssessmentSubject* getAssessmentSubject() const;
    void addCriterion(const std::string& name, int maxScore, double weight);
    void setEvaluation(int studentId, const std::string& criterion, int score);
    std::optional<int> getEvaluation(int studentId, const std::string& criterion) const;
    const std::map<std::string, AssessmentSubject>& getCriteria() const;
    void cancelEvaluation(int studentId, const std::string& criterion);
private:
    std::string name_;
    std::string nameStudyProgram_;
    std::optional<std::string> description_;
    std::map<std::string, AssessmentSubject> criteria_;
    std::map<std::pair<int, std::string>, EvaluationScore> evaluations_;
};

class StudyProgram {
public:
    StudyProgram() = default;
    StudyProgram(std::string name,
                 std::optional<std::string> description);
    void addSubject(std::shared_ptr<Subject>& subject);

    std::string getNameStudyProgram() const;
    std::optional<int> getIndSubject(const std::string& name) const;

    const std::vector<std::shared_ptr<Subject>>& getSubjects() const;
private:
    std::string name_;
    std::vector<std::shared_ptr<Subject>> subjects_;
    std::optional<std::string> description_;
};