#pragma once
#include "final_score.h"
#include <string>
#include <vector>

struct FinalReportRow { int studentId; std::string studentName; FinalScore final; };

class IFinalExporter {
public:
    virtual ~IFinalExporter() = default;
    virtual void write(const std::vector<FinalReportRow>& rows) = 0;
};
