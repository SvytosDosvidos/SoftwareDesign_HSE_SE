#pragma once

#include "academic_subject.h"

class IMissingEvaluationStrategy {
public:
    virtual ~IMissingEvaluationStrategy() = default;
    virtual int resolve(std::optional<int> score) const = 0;
};

class RequireAllEvaluations : public IMissingEvaluationStrategy {
public:
    int resolve(std::optional<int> score) const override;
};

class MissingAsZero : public IMissingEvaluationStrategy {
public:
    int resolve(std::optional<int> score) const override;
};

struct FinalScore {
    double value;
    size_t gradedCriteria;
    size_t totalCriteria;
};

// Domain Service: 10 * sum(weight * score / maxScore) / sum(weight).
// The strategy changes missing-score handling without changing stored evaluations.
class FinalScoreService {
public:
    explicit FinalScoreService(const IMissingEvaluationStrategy& strategy);
    FinalScore calculate(const Subject& subject, int studentId) const;
private:
    const IMissingEvaluationStrategy& strategy_;
};
