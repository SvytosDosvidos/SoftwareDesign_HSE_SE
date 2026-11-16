#pragma once

#include "person.h"
#include "academic_subject.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

class IPOSRepository {
public:
    virtual ~IPOSRepository() = default;

    virtual void saveStudent(std::shared_ptr<Student> student) = 0;
    virtual std::shared_ptr<Student> findStudent(int idPass) const = 0;
    virtual bool existsStudent(int idPass) const = 0;
    virtual const std::vector<std::shared_ptr<Student>>& getAllStudents() const = 0;

    virtual void saveLecturer(std::shared_ptr<Lecturer> lecturer) = 0;
    virtual std::shared_ptr<Lecturer> findLecturer(int idPass) const = 0;
    virtual bool existsLecturer(int idPass) const = 0;
    virtual size_t getCntLecturers() const = 0;
    virtual const std::vector<std::shared_ptr<Lecturer>>& getAllLecturers() const = 0;

    virtual void saveStudyProgram(std::shared_ptr<StudyProgram> program) = 0;
    virtual std::shared_ptr<StudyProgram> findStudyProgram(const std::string& name) const = 0;
    virtual bool existsStudyProgram(const std::string& name) const = 0;
};

class InMemoryPOSRepository : public IPOSRepository {
public:
    ~InMemoryPOSRepository() override = default;

    void saveStudent(std::shared_ptr<Student> student) override;
    std::shared_ptr<Student> findStudent(int idPass) const override;
    bool existsStudent(int idPass) const override;
    const std::vector<std::shared_ptr<Student>>& getAllStudents() const override;

    void saveLecturer(std::shared_ptr<Lecturer> lecturer) override;
    std::shared_ptr<Lecturer> findLecturer(int idPass) const override;
    bool existsLecturer(int idPass) const override;
    size_t getCntLecturers() const override;
    const std::vector<std::shared_ptr<Lecturer>>& getAllLecturers() const override;

    void saveStudyProgram(std::shared_ptr<StudyProgram> program) override;
    std::shared_ptr<StudyProgram> findStudyProgram(const std::string& name) const override;
    bool existsStudyProgram(const std::string& name) const override;
private:
    std::unordered_map<int, std::shared_ptr<Student>> studentMap_;
    std::vector<std::shared_ptr<Student>> studentList_;

    std::unordered_map<int, std::shared_ptr<Lecturer>> lecturerMap_;
    std::vector<std::shared_ptr<Lecturer>> lecturerList_;

    std::unordered_map<std::string, std::shared_ptr<StudyProgram>> programMap_;
};