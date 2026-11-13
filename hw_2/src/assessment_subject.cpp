#include "../include/assessment_subject.h"

#include<stdexcept>

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

AssessmentSubject::AssessmentSubject(std::pair<int, int> range, std::optional<std::string> description) :
    score_(range), description_(description) {}

AssessmentSubject::AssessmentSubject(std::optional<std::string> description) :
    score_(), description_(description) {}