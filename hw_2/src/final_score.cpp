#include "final_score.h"

#include <algorithm>
#include <stdexcept>

int RequireAllEvaluations::resolve(std::optional<int> score) const {
    if(!score) {
        throw std::invalid_argument("not all criteria have evaluations");
    }
    return *score;
}

int MissingAsZero::resolve(std::optional<int> score) const {
    return score.value_or(0);
}

FinalScoreService::FinalScoreService(const IMissingEvaluationStrategy& strategy) : strategy_(strategy) {}

FinalScore FinalScoreService::calculate(const Subject& subject, int studentId) const {
    const auto& criteria = subject.getCriteria();
    if(studentId < 0 || criteria.empty()) {
        throw std::invalid_argument("invalid student id or empty rubric");
    }
    double largestWeight = 0;
    for(const auto& [name, criterion] : criteria) {
        largestWeight = std::max(largestWeight, criterion.getWeight());
    }
    double weightedScore = 0;
    double totalWeight = 0;
    size_t graded = 0;
    for(const auto& [name, criterion] : criteria) {
        const int maximum = criterion.getRange().second;
        if(maximum <= 0) {
            throw std::invalid_argument("criterion max score must be positive");
        }
        const auto score = subject.getEvaluation(studentId, name);
        graded += score.has_value();
        // Scaling preserves relative weights and prevents overflow of their sum.
        const double weight = criterion.getWeight() / largestWeight;
        weightedScore += weight * strategy_.resolve(score) / maximum;
        totalWeight += weight;
    }
    return {std::clamp(10 * weightedScore / totalWeight, 0.0, 10.0), graded, criteria.size()};
}
