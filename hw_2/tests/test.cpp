#include <catch2/catch_test_macros.hpp>

#include <random>

#include "../include/pos_application_facade.h"

void createSubject(std::string&& name, std::string&& nameStudyProgram,
    std::optional<std::string>&& description, std::stringstream& input) {
    input << name << " " << nameStudyProgram;
    if(description.has_value()) {
        input << " " << description.value();
    }
}

void createStudyProgram(std::string&& name,
    std::optional<std::string>&& description, std::stringstream& input) {
    input << name;
    if(description.has_value()) {
        input << " " << description.value();
    }
}

void createLecturer(int&& idPass, std::string&& name,
    std::stringstream& input) {
    input << idPass << " " << name;
}

std::string createRandStr(size_t&& size, std::uniform_int_distribution<size_t>& distChar, std::mt19937& rnd) {
    static std::vector<char> symbols;
    if(symbols.empty()) {
        symbols.resize(2 * 26);
        for(size_t i = 0; i < 2 * 26; ++i) {
             if(i < 26) {
                symbols[i] = 'a' + i;
             } else {
                symbols[i] = 'A' + (i - 26);
             }
        }
    }

    std::string result;
    result.reserve(size);
    for(size_t i = 0; i < size; ++i) {
        result[i] = symbols[distChar(rnd)];
    }

    return result;
}

TEST_CASE("Test logic for correct parser") {
    std::unique_ptr<POSApplicationFacade> posApplicationFacade = std::make_unique<POSApplicationFacade>();

    std::mt19937 rnd(42);
    std::uniform_int_distribution<long long> distLongLong(0, std::numeric_limits<long long>::max());
    std::uniform_int_distribution<size_t> distCntPars(0, 5);
    std::uniform_int_distribution<size_t> distChar(0, 2 * 26 - 1);
    std::uniform_int_distribution<size_t> distSizeStr(1, 100);
    std::uniform_int_distribution<size_t> typeAdd(1, 2);

    SECTION("") {
        for(size_t ind = 0; ind < 1000; ++ind) {
            size_t sizePars = distCntPars(rnd);
            std::stringstream input;
            std::string strError;
            for(size_t i = 0; i < sizePars; ++i) {
                size_t type = typeAdd(rnd);
                if(type == 1) {
                    input << distLongLong(rnd) << " ";
                } else {
                    input << createRandStr(distSizeStr(rnd), distChar, rnd) << " ";
                }
            }

            std::stringstream input_1(input.str());
            std::stringstream input_2(input.str());
            std::stringstream input_3(input.str());
            std::stringstream input_4(input.str());
            std::stringstream input_5(input.str());
            std::stringstream input_6(input.str());

            posApplicationFacade->openStudyProgram(input_1, strError);
            posApplicationFacade->appointLecturere(input_2, strError);
            posApplicationFacade->enrollStudent(input_3, strError);
            posApplicationFacade->addSubject(input_4, strError);
            posApplicationFacade->addTeachSubject(input_5, strError);
            posApplicationFacade->addStudyProgramStudent(input_6, strError);
        }
    }
}

TEST_CASE("Test logic with studyPogram and studyProgram") {
    std::unique_ptr<POSApplicationFacade> posApplicationFacade = std::make_unique<POSApplicationFacade>();

    std::stringstream inputStudyProgram;
    std::string errorStrStudyProgram;
    createStudyProgram("se", std::nullopt, inputStudyProgram);
    posApplicationFacade->openStudyProgram(inputStudyProgram, errorStrStudyProgram);
    REQUIRE(errorStrStudyProgram.empty());

    SECTION("") {
        std::stringstream inputSubject;
        std::string errorStrSubject;
        createSubject("math", "ami", std::optional<std::string>(std::nullopt), inputSubject);
        posApplicationFacade->addSubject(inputSubject, errorStrSubject);
        CHECK(errorStrSubject == "there is no such nameStudyProgram");
        CHECK(posApplicationFacade->getCntSubjectInStudyProgram("se") == 0);
        CHECK(posApplicationFacade->getCntSubjectInStudyProgram("ami") == 0);
    }

    SECTION("") {
        std::stringstream inputSubject_1;
        std::string errorStrSubject_1;
        createSubject("math", "se", std::optional<std::string>(std::nullopt), inputSubject_1);
        posApplicationFacade->addSubject(inputSubject_1, errorStrSubject_1);
        REQUIRE(posApplicationFacade->getCntSubjectInStudyProgram("se") == 1);

        std::stringstream inputSubject_2;
        std::string errorStrSubject_2;
        createSubject("math", "se", std::optional<std::string>(std::nullopt), inputSubject_2);
        posApplicationFacade->addSubject(inputSubject_2, errorStrSubject_2);
        CHECK(posApplicationFacade->getCntSubjectInStudyProgram("se") == 1);
        CHECK(errorStrSubject_2 == "not unique name");
    }

    SECTION("") {
        std::stringstream inputSubject_1;
        std::string errorStrSubject_1;
        createSubject("math", "se", std::optional<std::string>(std::nullopt), inputSubject_1);
        posApplicationFacade->addSubject(inputSubject_1, errorStrSubject_1);

        std::stringstream inputSubject_2;
        std::string errorStrSubject_2;
        createSubject("c++", "se", std::optional<std::string>(std::nullopt), inputSubject_2);
        posApplicationFacade->addSubject(inputSubject_2, errorStrSubject_2);

        CHECK(posApplicationFacade->getCntSubjectInStudyProgram("se") == 2);
    }
}

TEST_CASE("Test logic with Lecturer") {
    std::unique_ptr<POSApplicationFacade> posApplicationFacade = std::make_unique<POSApplicationFacade>();

    std::stringstream inputStudyProgram;
    std::string errorStrStudyProgram;
    createStudyProgram("se", std::nullopt, inputStudyProgram);
    posApplicationFacade->openStudyProgram(inputStudyProgram, errorStrStudyProgram);

    std::stringstream inputLecturer_1;
    std::string errorStrLecturer_1;
    createLecturer(1, "IvanGenrihovich", inputLecturer_1);
    posApplicationFacade->appointLecturere(inputLecturer_1, errorStrLecturer_1);
    REQUIRE(posApplicationFacade->getCntLecturers() == 1);

    SECTION("") {
        std::stringstream inputLecturer_2;
        std::string errorStrLecturer_2;
        createLecturer(1, "EvgeniyDashkov", inputLecturer_2);
        posApplicationFacade->appointLecturere(inputLecturer_2, errorStrLecturer_2);
        CHECK(posApplicationFacade->getCntLecturers() == 1);
        CHECK(errorStrLecturer_2 == "not unique idPass");
    }

    SECTION("") {
        std::stringstream inputLecturer_2;
        std::string errorStrLecturer_2;
        createLecturer(2, "EvgeniyDashkov", inputLecturer_2);
        posApplicationFacade->appointLecturere(inputLecturer_2, errorStrLecturer_2);
        CHECK(posApplicationFacade->getCntLecturers() == 2);
    }
}