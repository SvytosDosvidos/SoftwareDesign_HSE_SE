#pragma once

#include <sstream>
#include <string>
#include <optional>

class Parser {
public:
    static bool parseStudyProgram(std::stringstream& input, std::string& name,
                                  std::optional<std::string>& description, std::string& errorStr);

    static bool parsePerson(std::stringstream& input, int& idPass,
                            std::string& name, std::string& errorStr);

    static bool parseSubject(std::stringstream& input, std::string& name,
                             std::string& nameStudyProgram, std::optional<std::string>& description, std::string& errorStr);

    static bool parseTeachSubject(std::stringstream& input, int& idPassLecturer,
                                  std::string& nameStudyProgram, std::string& nameSubject, std::string& errorStr);

    static bool parseStudyProgramStudent(std::stringstream& input, int& idPassStudent,
                                         std::string& nameStudyProgram, std::string& errorStr);
};