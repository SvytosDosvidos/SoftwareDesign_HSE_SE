#pragma once

#include<optional>
#include<string>

class ScoreInt {
public:
    ScoreInt();
    ScoreInt(std::pair<int, int> range);

    void updateScore(int score);
private:
    std::optional<int> score_;
    std::pair<int, int> range_;
};

class AssessmentSubject {
public:
    AssessmentSubject(std::pair<int, int> range, std::optional<std::string> description);
    AssessmentSubject(std::optional<std::string> description);
private:
    ScoreInt score_;
    std::optional<std::string> description_;
};