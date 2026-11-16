#include "console_app.h"
#include "adapters/csv_final_exporter.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

void ConsoleApp::initReportingCommands() {
    mapBinderPrint_["criteria"] = "[program] [subject]";
    mapBinder_["criteria"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string&) {
        std::string program, subject;
        if(!(input >> program >> subject) || !(input >> std::ws).eof()) {
            throw std::invalid_argument("expected: criteria program subject");
        }
        for(const auto& [name, criterion] : raw->getCriteria(program, subject)) {
            std::cout << name << " max=" << criterion.getRange().second << " weight=" << criterion.getWeight() << "\n";
        }
    };
    mapBinderPrint_["evaluations"] = "[program] [subject] [studentId]";
    mapBinder_["evaluations"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string&) {
        std::string program, subject;
        int studentId;
        if(!(input >> program >> subject >> studentId) || !(input >> std::ws).eof()) {
            throw std::invalid_argument("expected: evaluations program subject studentId");
        }
        for(const auto& [name, score] : raw->getEvaluations(program, subject, studentId)) {
            std::cout << name << "=" << (score ? std::to_string(*score) : "missing") << "\n";
        }
    };
    mapBinderPrint_["cancel"] = "[program] [subject] [studentId] [criterion]";
    mapBinder_["cancel"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string&) {
        std::string program, subject, criterion;
        int studentId;
        if(!(input >> program >> subject >> studentId >> criterion) || !(input >> std::ws).eof()) {
            throw std::invalid_argument("expected: cancel program subject studentId criterion");
        }
        raw->cancelEvaluation(program, subject, studentId, criterion);
    };
    mapBinderPrint_["report"] = "[program] [subject]; missing grades count as zero";
    mapBinder_["report"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string&) {
        std::string program, subject;
        if(!(input >> program >> subject) || !(input >> std::ws).eof()) {
            throw std::invalid_argument("expected: report program subject");
        }
        for(const auto& row : raw->buildReport(program, subject, MissingAsZero())) {
            std::cout << row.studentId << " " << row.studentName << ": " << row.final.value << "/10\n";
        }
    };
    mapBinderPrint_["export"] = "[program] [subject] [new CSV path]; all grades required";
    mapBinder_["export"] = [raw = posApplicationFacade_.get()](std::stringstream& input, std::string&) {
        std::string program, subject, path;
        if(!(input >> program >> subject >> std::quoted(path)) || path.empty() || !(input >> std::ws).eof()) {
            throw std::invalid_argument("expected: export program subject path");
        }
        const auto rows = raw->buildReport(program, subject, RequireAllEvaluations());
        if(std::filesystem::exists(path)) {
            throw std::invalid_argument("output already exists; choose a new path");
        }
        std::ofstream output(path);
        if(!output) {
            throw std::runtime_error("cannot open CSV output");
        }
        CsvFinalExporter(output).write(rows);
        std::cout << "Export completed.\n";
    };
}
