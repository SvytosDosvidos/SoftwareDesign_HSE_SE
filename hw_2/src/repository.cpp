#include "../include/repository.h"

void InMemoryPOSRepository::saveStudent(std::shared_ptr<Student> student) {
    studentMap_[student->getIdPass()] = student;
    studentList_.push_back(student);
}

std::shared_ptr<Student> InMemoryPOSRepository::findStudent(int idPass) const {
    auto it = studentMap_.find(idPass);
    if(it != studentMap_.end()) {
        return it->second;
    }
    return nullptr;
}

bool InMemoryPOSRepository::existsStudent(int idPass) const {
    return studentMap_.find(idPass) != studentMap_.end();
}

const std::vector<std::shared_ptr<Student>>& InMemoryPOSRepository::getAllStudents() const {
    return studentList_;
}

void InMemoryPOSRepository::saveLecturer(std::shared_ptr<Lecturer> lecturer) {
    lecturerMap_[lecturer->getIdPass()] = lecturer;
    lecturerList_.push_back(lecturer);
}

std::shared_ptr<Lecturer> InMemoryPOSRepository::findLecturer(int idPass) const {
    auto it = lecturerMap_.find(idPass);
    if(it != lecturerMap_.end()) {
        return it->second;
    }
    return nullptr;
}

bool InMemoryPOSRepository::existsLecturer(int idPass) const {
    return lecturerMap_.find(idPass) != lecturerMap_.end();
}

size_t InMemoryPOSRepository::getCntLecturers() const {
    return lecturerMap_.size();
}

const std::vector<std::shared_ptr<Lecturer>>& InMemoryPOSRepository::getAllLecturers() const {
    return lecturerList_;
}

void InMemoryPOSRepository::saveStudyProgram(std::shared_ptr<StudyProgram> program) {
    programMap_[program->getNameStudyProgram()] = program;
}

std::shared_ptr<StudyProgram> InMemoryPOSRepository::findStudyProgram(const std::string& name) const {
    auto it = programMap_.find(name);
    if(it != programMap_.end()) {
        return it->second;
    }
    return nullptr;
}

bool InMemoryPOSRepository::existsStudyProgram(const std::string& name) const {
    return programMap_.find(name) != programMap_.end();
}