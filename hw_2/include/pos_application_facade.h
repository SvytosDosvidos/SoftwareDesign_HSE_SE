#pragma once

#include "person.h"
#include "academic_subject.h"
#include "repository.h"

#include <sstream>
#include <memory>
#include <string>
#include <optional>

class POSApplicationFacade {
public:
    POSApplicationFacade();
    explicit POSApplicationFacade(std::shared_ptr<IPOSRepository> repository);

    void openStudyProgram(std::stringstream& input, std::string& errorStr);
    void appointLecturere(std::stringstream& input, std::string& errorStr);
    void enrollStudent(std::stringstream& input, std::string& errorStr);
    void addSubject(std::stringstream& input, std::string& errorStr);
    void addTeachSubject(std::stringstream& input, std::string& errorStr);
    void addStudyProgramStudent(std::stringstream& input, std::string& errorStr);
    void addAssessmentSubject(std::stringstream& input, std::string& errorStr);

    bool openStudyProgram(const std::string& name, const std::optional<std::string>& description,
        std::string& errorStr);

    bool appointLecturere(int idPass, const std::string& name, std::string& errorStr);

    bool enrollStudent(int idPass, const std::string& name, std::string& errorStr);

    bool addSubject(const std::string& name, const std::string& nameStudyProgram,
        const std::optional<std::string>& description, std::string& errorStr);

    bool addTeachSubject(int idPassLecturer, const std::string& nameStudyProgram,
        const std::string& nameSubject, std::string& errorStr);

    bool addStudyProgramStudent(int idPassStudent, const std::string& nameStudyProgram, std::string& errorStr);

    bool addAssessmentSubject(const std::string& nameSubject, const std::string& nameStudyProgam,
        double weigth, std::optional<std::pair<int, int>> range,
        std::optional<std::string>& description, std::string& errorStr);

    void printStudents() const;
    void printLecturers() const;

    size_t getCntSubjectInStudyProgram(const std::string& nameStudyProgram) const;
    size_t getCntLecturers() const;
private:
    std::shared_ptr<IPOSRepository> repository_;
};