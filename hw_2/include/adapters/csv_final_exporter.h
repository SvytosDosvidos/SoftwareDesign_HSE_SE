#pragma once
#include "application/final_exporter.h"
#include <ostream>

class CsvFinalExporter : public IFinalExporter {
public:
    explicit CsvFinalExporter(std::ostream& output) : output_(output) {}
    void write(const std::vector<FinalReportRow>& rows) override;
private:
    std::ostream& output_;
};
