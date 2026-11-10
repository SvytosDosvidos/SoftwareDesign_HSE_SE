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

class EducationDirection {
public:
    EducationDirection(int idDirection, std::string name,
                       std::optional<std::string> description);
    void addSubject(std::string name, std::optional<std::string> description,
                    std::string nameProgramReading);
private:
    int idDirection_;
    std::string name_;
    std::vector<std::unique_ptr<Subject>> subjects_;
    std::optional<std::string> description_;
};