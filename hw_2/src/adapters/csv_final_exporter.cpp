#include "adapters/csv_final_exporter.h"
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdexcept>

namespace {
std::string quote(const std::string& value) {
    std::string result = "\"";
    for(char c : value) {
        if(c == '"') result += '"';
        result += c;
    }
    return result + '"';
}
}
void CsvFinalExporter::write(const std::vector<FinalReportRow>& rows) {
    std::ostringstream csv;
    csv.imbue(std::locale::classic());
    csv << "student_id,student_name,final_score,graded,total\n" << std::fixed << std::setprecision(2);
    for(const auto& row : rows) {
        csv << row.studentId << ',' << quote(row.studentName) << ',' << row.final.value
            << ',' << row.final.gradedCriteria << ',' << row.final.totalCriteria << '\n';
    }
    output_ << csv.str();
    output_.flush();
    if(!output_) throw std::runtime_error("cannot write CSV output");
}
