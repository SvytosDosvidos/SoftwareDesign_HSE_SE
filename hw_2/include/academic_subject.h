#pragma once

#include "assessment_subject.h"

#include <string>
#include <vector>
#include <optional>
#include <memory>

class Subject {
public:
    Subject(std::string name, std::string nameProgramReading,
        std::optional<std::string> description);

    void addAssessmentSubject(std::unique_ptr<AssessmentSubject>& assessmentSubject);

    std::string getName() const;
private:
    std::string name_;
    std::string nameStudyProgram_;
    std::optional<std::string> description_;
    std::unique_ptr<AssessmentSubject> assessmentSubject_;
};

class StudyProgram {
public:
    StudyProgram(int idStudyProgam, std::string name,
        std::optional<std::string> description);
    void addSubject(std::shared_ptr<Subject>& subject);

    int getIdStudyProgam() const;
    std::string getNameStudyProgram() const;
    const std::vector<std::shared_ptr<Subject>>& getSubjects() const;
private:
    int idStudyProgam_;
    std::string name_;
    std::vector<std::shared_ptr<Subject>> subjects_;
    std::optional<std::string> description_;
};