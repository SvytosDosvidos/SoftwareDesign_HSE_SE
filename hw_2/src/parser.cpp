#include "../include/parser.h"

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

    std::pair<int, int> rangeValue;
    std::string descriptionStr;

    if(input >> rangeValue.first >> rangeValue.second) {
        rangeValue = {rangeValue.first, rangeValue.second};
    }

    input >> descriptionStr;

    return true;
}
