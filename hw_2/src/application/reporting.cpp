#include "pos_application_facade.h"
#include <stdexcept>

const std::map<std::string, AssessmentSubject>& POSApplicationFacade::getCriteria(
    const std::string& program, const std::string& subject) const {
    return findSubject(program, subject)->getCriteria();
}

std::map<std::string, std::optional<int>> POSApplicationFacade::getEvaluations(
    const std::string& program, const std::string& subject, int studentId) const {
    if(!repository_->existsStudent(studentId)) {
        throw std::invalid_argument("student does not exist");
    }
    auto course = findSubject(program, subject);
    std::map<std::string, std::optional<int>> result;
    for(const auto& [name, criterion] : course->getCriteria()) {
        result[name] = course->getEvaluation(studentId, name);
    }
    return result;
}

void POSApplicationFacade::cancelEvaluation(const std::string& program, const std::string& subject,
    int studentId, const std::string& criterion) {
    if(!repository_->existsStudent(studentId)) {
        throw std::invalid_argument("student does not exist");
    }
    findSubject(program, subject)->cancelEvaluation(studentId, criterion);
}
std::vector<FinalReportRow> POSApplicationFacade::buildReport(const std::string& program,
    const std::string& subject, const IMissingEvaluationStrategy& strategy) const {
    const auto course = findSubject(program, subject);
    if(course->getCriteria().empty()) {
        throw std::invalid_argument("empty rubric");
    }
    std::vector<FinalReportRow> rows;
    for(const auto& student : repository_->getAllStudents()) {
        rows.push_back({student->getIdPass(), student->getName(),
            FinalScoreService(strategy).calculate(*course, student->getIdPass())});
    }
    return rows;
}
void POSApplicationFacade::exportFinals(const std::string& program, const std::string& subject,
    const IMissingEvaluationStrategy& strategy, IFinalExporter& exporter) const {
    exporter.write(buildReport(program, subject, strategy));
}
