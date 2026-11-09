#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>

class Subject {
public:

private:
    std::string name_;
    std::optional<std::string> description_;
    std::string nameProgramReading_;
};

class EducationDirection {
public:

private:
    std::string name_;
    std::optional<std::string> description_;
    std::vector<std::unique_ptr<Subject>> subjects_;
};