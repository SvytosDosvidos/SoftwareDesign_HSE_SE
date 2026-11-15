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

    void addTeachSubject(std::stringstream& input, std::string& errorStr);
    void addStudyProgramStudent(std::stringstream& input, std::string& errorStr);

    void printStudents() const;
    void printLecturers() const;

    size_t getCntSubjectInStudyProgram(std::string&& nameStudyProgram) const;
private:
    bool checkUniqueIdPass(int idPass) const;
    bool checkUniqueNameSubject(const std::string& name, int indStudyProgam) const;
    bool checkUniqueNameStudyProgram(const std::string& name) const;

    std::optional<int> getIndLecturer(int idPass) const;
    std::optional<int> getIndStudent(int idPass) const;
    std::optional<int> getIndStudyProgram(const std::string& nameStudyProgam) const;

    std::vector<std::unique_ptr<Lecturer>> lecturers_;
    std::vector<std::unique_ptr<Student>> students_;
    std::vector<std::shared_ptr<StudyProgram>> studyPrograms_;
};