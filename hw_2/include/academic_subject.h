#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>

class Subject {
public:
    Subject(std::string name, std::optional<std::string> description,
        std::string nameProgramReading);
private:
    std::string name_;
    std::string nameProgramReading_;
    std::optional<std::string> description_;
};

class StudyProgram {
public:
    StudyProgram(int idStudyProgam, std::string name,
        std::optional<std::string> description);
    void addSubject(std::string name, std::optional<std::string> description,
        std::string nameProgramReading);

    int getIdStudyProgam() const;
private:
    int idStudyProgam_;
    std::string name_;
    std::vector<std::unique_ptr<Subject>> subjects_;
    std::optional<std::string> description_;
};