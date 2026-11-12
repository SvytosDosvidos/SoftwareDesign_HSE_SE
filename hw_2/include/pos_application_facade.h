#pragma once

#include "person.h"
#include "academic_subject.h"

#include<sstream>
#include<memory>
#include<functional>

class POSApplicationFacade {
public:
    POSApplicationFacade() = default;
    void openStudyProgram(std::stringstream& ss, std::string& errorStr);
    void appointLecturere(std::stringstream& ss, std::string& errorStr);
    void enrollStudent(std::stringstream& ss, std::string& errorStr);

    bool checkUniqueIdPass(int idPass);
    bool checkUniqueNameSubject(std::string name);
    bool checkUniqueIdProgram(int idStudyProgam);

    void printStudents() const;
    void printLecturers() const;
private:
    std::vector<std::unique_ptr<Lecturer>> lecturers_;
    std::vector<std::unique_ptr<Student>> students_;
    std::vector<std::unique_ptr<StudyProgram>> studyPrograms_;
};