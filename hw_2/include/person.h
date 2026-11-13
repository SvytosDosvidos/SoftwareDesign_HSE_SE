#pragma once

#include "academic_subject.h"

#include <string>
#include <vector>
#include <memory>

class IPersonUniversity {
public:
    IPersonUniversity(int idPass, std::string name);
    virtual ~IPersonUniversity() = default;

    int getIdPass() const;
protected:
    int idPass_;
    std::string name_;
};

class Lecturer : public IPersonUniversity {
public:
    ~Lecturer() override = default;
    Lecturer(int idPass, std::string name);
    void addSubjectTeach(std::shared_ptr<Subject> subjectTeach);
private:
    std::vector<std::shared_ptr<Subject>> subjectsTeach_;
};

class Student : public IPersonUniversity {
public:
    ~Student() override = default;
    Student(int idPass, std::string name);
    void addStudyProgram(std::shared_ptr<StudyProgram> studyProgram);
private:
    std::vector<std::shared_ptr<StudyProgram>> studyPrograms_;
};