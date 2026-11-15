#include <catch2/catch_test_macros.hpp>

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

TEST_CASE("Test with studyPogram and studyProgram") {
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
        REQUIRE(errorStrSubject == "there is no such nameStudyProgram");
        REQUIRE(posApplicationFacade->getCntSubjectInStudyProgram("se") == 0);
        REQUIRE(posApplicationFacade->getCntSubjectInStudyProgram("ami") == 0);
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
        REQUIRE(posApplicationFacade->getCntSubjectInStudyProgram("se") == 1);
        REQUIRE(errorStrSubject_2 == "not unique name");
    }
}