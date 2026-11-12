#pragma once

#include "person.h"
#include "academic_subject.h"

#include<sstream>
#include<memory>
#include<functional>

class POSApplicationFacade {
public:
    POSApplicationFacade() = default;
    void openStudyProgram(std::stringstream& input, std::string& errorStr);
    void appointLecturere(std::stringstream& input, std::string& errorStr);
    void enrollStudent(std::stringstream& input, std::string& errorStr);
    void addSubject(std::stringstream& input, std::string& errorStr);

    void printStudents() const;
    void printLecturers() const;
private:
    bool checkUniqueIdPass(int idPass) const;
    bool checkUniqueNameSubject(std::string name) const;
    bool checkUniqueIdProgram(int idStudyProgam) const;

    std::optional<int> getIndStudyProgram(std::string nameStudyProgam) const;

    std::vector<std::unique_ptr<Lecturer>> lecturers_;
    std::vector<std::unique_ptr<Student>> students_;
    std::vector<std::unique_ptr<StudyProgram>> studyPrograms_;
};