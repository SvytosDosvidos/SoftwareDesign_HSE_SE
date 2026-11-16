#include "../include/assessment_subject.h"

#include <stdexcept>

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

AssessmentSubject::AssessmentSubject(double weigth, std::optional<std::pair<int, int>> range,
    std::optional<std::string> description) {
        if(range.has_value()) {
            AssessmentSubject(weigth, range.value(), description);
        } else {
            AssessmentSubject(weigth, description);
        }
    }

AssessmentSubject::AssessmentSubject(double weigth, std::pair<int, int> range,
    std::optional<std::string> description) :
        weigth_(weigth), score_(range), description_(description) {}

AssessmentSubject::AssessmentSubject(double weigth, std::optional<std::string> description) :
    weigth_(weigth), score_(), description_(description) {}