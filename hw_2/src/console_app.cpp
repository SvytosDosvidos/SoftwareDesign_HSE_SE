#include "../include/console_app.h"

#include <iostream>
#include <format>
#include <sstream>
#include <string>
#include <stdexcept>

ConsoleApp::ConsoleApp() {
    posApplicationFacade_ = std::make_unique<POSApplicationFacade>();
}

constexpr int kMaxSymbols = 200;

std::stringstream getStr() {
    std::string str;
    std::stringstream ss;

    while(std::cin && str.size() < kMaxSymbols) {
        char c = std::cin.get();
        if(c == '\n') {
            break;
        }
        str.push_back(c);
    }

    ss << str;
    return ss;
}

int getCommand() {
    std::stringstream ss = getStr();
    int n;
    if(ss >> n) {
        return n;
    }
    return -1;
}

void ConsoleApp::init() {
    mapСreatorPrint_["studyProgram"] = "[nameStudyProgram](description)";
    mapСreatorPrint_["subject"] = "[nameSubject][nameProgramReading](description)";
    mapСreatorPrint_["lecturer"] = "[idPass][name]";
    mapСreatorPrint_["student"] = "[idPass][name]";

    mapBinderPrint_["add_subject_lecturer"] = "[nameLecturer][nameStudyProgram][nameSubject]";
    mapBinderPrint_["add_studyProgam_student"] = "[nameStudent][nameStudyProgram]";
    mapBinderPrint_["add_assessment"] = "[subject] [program] [weight] (min max (description)); default range: 0 10";

    mapBinderPrint_["criterion"] = "[program] [subject] [criterion] [maxScore] [weight]";
    mapBinderPrint_["evaluate"] = "[program] [subject] [studentId] [criterion] [score]";
    mapBinder_["criterion"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string&) {
        std::string program, subject, criterion;
        int maxScore;
        double weight;
        if(!(input >> program >> subject >> criterion >> maxScore >> weight) || !(input >> std::ws).eof()) {
            throw std::invalid_argument("expected: criterion program subject name maxScore weight");
        }
        raw->addCriterion(program, subject, criterion, maxScore, weight);
    };
    mapBinder_["evaluate"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string&) {
        std::string program, subject, criterion;
        int studentId, score;
        if(!(input >> program >> subject >> studentId >> criterion >> score) || !(input >> std::ws).eof()) {
            throw std::invalid_argument("expected: evaluate program subject studentId criterion score");
        }
        raw->setEvaluation(program, subject, studentId, criterion, score);
    };

    mapBinderPrint_["final"] = "[program] [subject] [studentId] [strict|zero]";
    mapBinder_["final"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string&) {
        std::string program, subject, mode;
        int studentId;
        if(!(input >> program >> subject >> studentId >> mode) || !(input >> std::ws).eof()) {
            throw std::invalid_argument("expected: final program subject studentId strict|zero");
        }
        RequireAllEvaluations strict;
        MissingAsZero zero;
        const IMissingEvaluationStrategy* strategy = nullptr;
        if(mode == "strict") {
            strategy = &strict;
        } else if(mode == "zero") {
            strategy = &zero;
        } else {
            throw std::invalid_argument("unknown final score policy: use strict or zero");
        }
        const auto result = raw->calculateFinal(program, subject, studentId, *strategy);
        std::cout << std::format("Final score: {:.2f}/10 (graded: {}/{})\n",
                                 result.value, result.gradedCriteria, result.totalCriteria);
    };

    mapCreator_["studyProgram"] = [raw = posApplicationFacade_.get()](std::stringstream &input, std::string& errorStr) {
        raw->openStudyProgram(input, errorStr);
    };
    mapCreator_["lecturer"] = [raw = posApplicationFacade_.get()](std::stringstream &input, std::string& errorStr) {
        raw->appointLecturere(input, errorStr);
    };
    mapCreator_["student"] = [raw = posApplicationFacade_.get()](std::stringstream &input, std::string& errorStr) {
        raw->enrollStudent(input, errorStr);
    };
    mapCreator_["subject"] = [raw = posApplicationFacade_.get()](std::stringstream &input, std::string& errorStr) {
        raw->addSubject(input, errorStr);
    };

    mapBinder_["add_assessment"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string& errorStr) {
        raw->addAssessmentSubject(input, errorStr);
    };

    mapBinder_["add_subject_lecturer"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string& errorStr) {
        raw->addTeachSubject(input, errorStr);
    };

    mapBinder_["add_studyProgam_student"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string& errorStr) {
        raw->addStudyProgramStudent(input, errorStr);
    };
}

void ConsoleApp::run() {
    bool isWorkProgram = true;
    init();
    printCommand();

    while(isWorkProgram) {
        int idCommand = getCommand();

        switch(idCommand) {
            case 1: {
                printCommand();
                break;
            } case 2: {
                printStudents();
                break;
            } case 3: {
                printLecturers();
                break;
            } case 4: {
                std::cout << "Input data:\n";
                std::stringstream input = getStr();

                std::string strError = execute(input);
                if(strError.empty()) {
                    std::cout << "Operation completed.\n";
                } else {
                    std::cout << "Incorrect data, because:\n";
                    std::cout << strError << "\n";
                }
                break;
            } case 5: {
                printCommand4Add();
                break;
            } case 6: {
                isWorkProgram = false;
                break;
            } default: {
                std::cout << "Unknown command!\n";
                break;
            }
        }
    }
}

std::string ConsoleApp::execute(std::stringstream& input) {
    std::string name;
    input >> name;

    std::string errorStr;
    if(mapCreator_.find(name) != mapCreator_.end()) {
        mapCreator_[name](input, errorStr);
    } else if(mapBinder_.find(name) != mapBinder_.end()) {
        try {
            mapBinder_[name](input, errorStr);
        } catch(const std::invalid_argument& error) {
            errorStr = error.what();
        }
    } else {
        errorStr = "Invalid name for add object";
    }

    return errorStr;
}

void ConsoleApp::printCommand() const {
    std::cout << std::format("+{:-^128}+\n", "");
    std::cout << std::format("|{: ^128}|\n", "All command:");
    std::cout << std::format("|{: ^128}|\n", "");
    std::cout << std::format("|{: ^128}|\n", "1 - Instructions for all commands");
    std::cout << std::format("|{: ^128}|\n", "2 - Displaying the entire students in the university");
    std::cout << std::format("|{: ^128}|\n", "3 - Displaying the entire lecturer, and what they teach");
    std::cout << std::format("|{: ^128}|\n", "4 - Create objects, manage evaluations or calculate final score");
    std::cout << std::format("|{: ^128}|\n", "5 - Instructions on how to add student/lecturer/subject/educationDirection");
    std::cout << std::format("|{: ^128}|\n", "6 - End program");
    std::cout << std::format("+{:-^128}+\n", "");
}

void ConsoleApp::printCommand4Add() const {
    std::cout << std::format("+{:-^128}+\n", "");
    std::cout << std::format("|{: ^128}|\n", "Instructions on how to add an object:");
    std::cout << std::format("|{: ^128}|\n", "");
    std::cout << std::format("|{: ^128}|\n", "If the parameter is in [], then it is required");
    std::cout << std::format("|{: ^128}|\n", "If the parameter is in (), then it is optional");
    std::cout << std::format("|{: ^128}|\n", "");

    for(const auto &it : mapСreatorPrint_) {
        std::cout << std::format("|{: ^128}|\n", it.first + " - " + it.second);
    }
    std::cout << std::format("|{: ^128}|\n", "");

    for(const auto &it : mapBinderPrint_) {
        std::cout << std::format("|{: ^128}|\n", it.first + " - " + it.second);
    }
}

void ConsoleApp::printStudents() const {
    posApplicationFacade_->printStudents();
}

void ConsoleApp::printLecturers() const {
    posApplicationFacade_->printLecturers();
}