#include "../include/parser.h"

#include <cctype>

bool Parser::parseStudyProgram(std::stringstream& input, std::string& name,
    std::optional<std::string>& description, std::string& errorStr) {
    std::string descriptionStr;
    if(!(input >> name)) {
        errorStr += "invalid name value";
        return false;
    }
    input >> descriptionStr;
    if(!descriptionStr.empty()) {
        description = descriptionStr;
    }
    return true;
}

bool Parser::parsePerson(std::stringstream& input, int& idPass,
    std::string& name, std::string& errorStr) {
    if(!(input >> idPass)) {
        errorStr += "invalid idPass value";
        return false;
    }
    if(!(input >> name)) {
        errorStr += "invalid name value";
        return false;
    }
    return true;
}

bool Parser::parseSubject(std::stringstream& input, std::string& name,
    std::string& nameStudyProgram, std::optional<std::string>& description, std::string& errorStr) {
    std::string descriptionStr;
    if(!(input >> name)) {
        errorStr += "invalid name value";
        return false;
    }
    if(!(input >> nameStudyProgram)) {
        errorStr += "invalid nameStudyProgram value";
        return false;
    }
    input >> descriptionStr;
    if(!descriptionStr.empty()) {
        description = descriptionStr;
    }
    return true;
}

bool Parser::parseTeachSubject(std::stringstream& input, int& idPassLecturer,
    std::string& nameStudyProgram, std::string& nameSubject, std::string& errorStr) {
    if(!(input >> idPassLecturer)) {
        errorStr += "invalid idPassLecturer value";
        return false;
    }
    if(!(input >> nameStudyProgram)) {
        errorStr += "invalid nameStudyProgram value";
        return false;
    }
    if(!(input >> nameSubject)) {
        errorStr += "invalid nameSubject value";
        return false;
    }
    return true;
}

bool Parser::parseStudyProgramStudent(std::stringstream& input, int& idPassStudent,
    std::string& nameStudyProgram, std::string& errorStr) {
    if(!(input >> idPassStudent)) {
        errorStr += "invalid name idPassStudent";
        return false;
    }
    if(!(input >> nameStudyProgram)) {
        errorStr += "invalid nameStudyProgram value";
        return false;
    }
    return true;
}

bool Parser::parseAssessmentSubject(std::stringstream& input, std::string& nameSubject, std::string& nameStudyProgam,
    double& weigth, std::optional<std::pair<int, int>>& range, std::optional<std::string>& description, std::string& errorStr) {
    if(!(input >> nameSubject)) {
        errorStr += "invalid nameSubject value";
        return false;
    }

    if(!(input >> nameStudyProgam)) {
        errorStr += "invalid nameStudyProgam value";
        return false;
    }

    if(!(input >> weigth)) {
        errorStr += "invalid weigth value";
        return false;
    }

    range.reset();
    description.reset();
    input >> std::ws;
    if(input.eof()) {
        return true;
    }

    std::pair<int, int> rangeValue;
    if(!(input >> rangeValue.first >> rangeValue.second)) {
        errorStr += "expected min and max score";
        return false;
    }
    // A numeric prefix such as "100abc" is not a valid range boundary.
    if(!input.eof() && !std::isspace(static_cast<unsigned char>(input.peek()))) {
        errorStr += "invalid max score";
        return false;
    }
    range = rangeValue;

    std::string descriptionStr;
    if(std::getline(input >> std::ws, descriptionStr) && !descriptionStr.empty()) {
        description = descriptionStr;
    }
    return true;
}
