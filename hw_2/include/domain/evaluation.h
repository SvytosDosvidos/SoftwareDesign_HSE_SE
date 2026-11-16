#pragma once
#include <stdexcept>
#include <utility>

class EvaluationFactory;
class EvaluationScore {
public:
    int value() const { return value_; }
    bool operator==(const EvaluationScore&) const = default;
private:
    explicit EvaluationScore(int value) : value_(value) {}
    int value_;
    friend class EvaluationFactory;
};

// The aggregate supplies the range of a criterion already found in its rubric.
class EvaluationFactory {
public:
    static EvaluationScore create(int studentId, int score, std::pair<int, int> range) {
        if(studentId < 0 || range.first < 0 || range.first > range.second ||
           score < range.first || score > range.second) {
            throw std::invalid_argument("score is outside criterion range or invalid student id");
        }
        return EvaluationScore(score);
    }
};
