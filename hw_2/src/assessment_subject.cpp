#include "../include/assessment_subject.h"

#include <stdexcept>
#include <cmath>

ScoreInt::ScoreInt() : range_(std::make_pair(0, 10)) {}

ScoreInt::ScoreInt(std::pair<int, int> range) : range_(range) {
    if(range_.first < 0 || range_.first > range_.second) {
        throw std::invalid_argument("invalid value for range");
    }
}

void ScoreInt::updateScore(int score) {
    if(range_.first <= score && score <= range_.second) {
        score_ = score;
    }
}

std::pair<int, int> ScoreInt::getRange() const {
    return range_;
}

AssessmentSubject::AssessmentSubject(double weigth, std::optional<std::pair<int, int>> range,
    std::optional<std::string> description) :
        AssessmentSubject(weigth, range.value_or(std::make_pair(0, 10)), description) {}

AssessmentSubject::AssessmentSubject(double weigth, std::pair<int, int> range,
    std::optional<std::string> description) :
        score_(range), description_(description), weigth_(weigth) {
    if(!std::isfinite(weigth_) || weigth_ <= 0) {
        throw std::invalid_argument("weight must be finite and positive");
    }
}

AssessmentSubject::AssessmentSubject(double weigth, std::optional<std::string> description) :
    AssessmentSubject(weigth, std::make_pair(0, 10), description) {}

double AssessmentSubject::getWeight() const {
    return weigth_;
}

std::pair<int, int> AssessmentSubject::getRange() const {
    return score_.getRange();
}

const std::optional<std::string>& AssessmentSubject::getDescription() const {
    return description_;
}
