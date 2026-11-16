#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "final_score.h"
#include "bootstrap/application_container.h"
#include "adapters/csv_final_exporter.h"
#include "../include/console_app.h"

#include <random>
#include <sstream>
#include <limits>

#include "../include/pos_application_facade.h"
#include "../include/assessment_subject.h"
#include "../include/academic_subject.h"
#include "../include/person.h"

void createSubject(const std::string& name, const std::string& nameStudyProgram,
                   const std::optional<std::string>& description, std::stringstream& input) {
    input << name << " " << nameStudyProgram;
    if(description.has_value()) {
        input << " " << description.value();
    }
}

void createStudyProgram(const std::string& name,
                        const std::optional<std::string>& description, std::stringstream& input) {
    input << name;
    if(description.has_value()) {
        input << " " << description.value();
    }
}

void createLecturer(int idPass, const std::string& name, std::stringstream& input) {
    input << idPass << " " << name;
}

void createStudent(int idPass, const std::string& name, std::stringstream& input) {
    input << idPass << " " << name;
}

void createTeachSubject(int idPassLecturer, const std::string& nameStudyProgram,
                        const std::string& nameSubject, std::stringstream& input) {
    input << idPassLecturer << " " << nameStudyProgram << " " << nameSubject;
}

void createStudyProgramStudent(int idPassStudent, const std::string& nameStudyProgram,
                               std::stringstream& input) {
    input << idPassStudent << " " << nameStudyProgram;
}

std::string createRandStr(size_t size, std::uniform_int_distribution<size_t>& distChar, std::mt19937& rnd) {
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
    result.resize(size);
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

    SECTION("fuzzing with random string and numbers") {
        for(size_t ind = 0; ind < 200; ++ind) {
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

            REQUIRE_NOTHROW(posApplicationFacade->openStudyProgram(input_1, strError));
            REQUIRE_NOTHROW(posApplicationFacade->appointLecturere(input_2, strError));
            REQUIRE_NOTHROW(posApplicationFacade->enrollStudent(input_3, strError));
            REQUIRE_NOTHROW(posApplicationFacade->addSubject(input_4, strError));
            REQUIRE_NOTHROW(posApplicationFacade->addTeachSubject(input_5, strError));
            REQUIRE_NOTHROW(posApplicationFacade->addStudyProgramStudent(input_6, strError));
        }
    }
}

TEST_CASE("Test logic with studyProgram and Subject") {
    std::unique_ptr<POSApplicationFacade> posApplicationFacade = std::make_unique<POSApplicationFacade>();

    std::stringstream inputStudyProgram;
    std::string errorStrStudyProgram;
    createStudyProgram("se", std::nullopt, inputStudyProgram);
    posApplicationFacade->openStudyProgram(inputStudyProgram, errorStrStudyProgram);
    REQUIRE(errorStrStudyProgram.empty());

    SECTION("create studyProgram with description") {
        std::stringstream inputWithDesc;
        std::string errorWithDesc;
        createStudyProgram("ami", "applied_math_program", inputWithDesc);
        posApplicationFacade->openStudyProgram(inputWithDesc, errorWithDesc);
        CHECK(errorWithDesc.empty());
    }

    SECTION("not unique nameStudyProgram error") {
        std::stringstream inputStudyProgram_2;
        std::string errorStrStudyProgram_2;
        createStudyProgram("se", std::nullopt, inputStudyProgram_2);
        posApplicationFacade->openStudyProgram(inputStudyProgram_2, errorStrStudyProgram_2);
        CHECK(errorStrStudyProgram_2 == "not unique nameStudyProgram");
    }

    SECTION("there is no such nameStudyProgram for subject") {
        std::stringstream inputSubject;
        std::string errorStrSubject;
        createSubject("math", "ami", std::optional<std::string>(std::nullopt), inputSubject);
        posApplicationFacade->addSubject(inputSubject, errorStrSubject);
        CHECK(errorStrSubject == "there is no such nameStudyProgram");
        CHECK(posApplicationFacade->getCntSubjectInStudyProgram("se") == 0);
        CHECK(posApplicationFacade->getCntSubjectInStudyProgram("ami") == 0);
    }

    SECTION("check not unique name subject in same studyProgram") {
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

    SECTION("add subject with description") {
        std::stringstream inputSubjectWithDesc;
        std::string errorStrSubjectWithDesc;
        createSubject("discrete_math", "se", "hard_course", inputSubjectWithDesc);
        posApplicationFacade->addSubject(inputSubjectWithDesc, errorStrSubjectWithDesc);
        CHECK(errorStrSubjectWithDesc.empty());
        CHECK(posApplicationFacade->getCntSubjectInStudyProgram("se") == 1);
    }

    SECTION("add multiple different subjects in one studyProgram") {
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

TEST_CASE("Test logic with Lecturer and Student") {
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

    SECTION("invalid IdPass value less than zero") {
        std::stringstream inputLecturer_2;
        std::string errorStrLecturer_2;
        createLecturer(-1, "BadLecturer", inputLecturer_2);
        posApplicationFacade->appointLecturere(inputLecturer_2, errorStrLecturer_2);
        CHECK(errorStrLecturer_2 == "invalid IdPass value(>0)");
        CHECK(posApplicationFacade->getCntLecturers() == 1);
    }

    SECTION("not unique idPass for another lecturer") {
        std::stringstream inputLecturer_2;
        std::string errorStrLecturer_2;
        createLecturer(1, "EvgeniyDashkov", inputLecturer_2);
        posApplicationFacade->appointLecturere(inputLecturer_2, errorStrLecturer_2);
        CHECK(posApplicationFacade->getCntLecturers() == 1);
        CHECK(errorStrLecturer_2 == "not unique idPass");
    }

    SECTION("appoint second lecturer with unique idPass") {
        std::stringstream inputLecturer_2;
        std::string errorStrLecturer_2;
        createLecturer(2, "EvgeniyDashkov", inputLecturer_2);
        posApplicationFacade->appointLecturere(inputLecturer_2, errorStrLecturer_2);
        CHECK(posApplicationFacade->getCntLecturers() == 2);
    }

    SECTION("not unique idPass collision student with lecturer") {
        std::stringstream inputStudent_1;
        std::string errorStrStudent_1;
        createStudent(1, "Ivan", inputStudent_1);
        posApplicationFacade->enrollStudent(inputStudent_1, errorStrStudent_1);
        CHECK(errorStrStudent_1 == "not unique idPass");
    }

    SECTION("enroll student and duplicate idPass for student") {
        std::stringstream inputStudent_1;
        std::string errorStrStudent_1;
        createStudent(2, "Ivan", inputStudent_1);
        posApplicationFacade->enrollStudent(inputStudent_1, errorStrStudent_1);
        CHECK(errorStrStudent_1.empty());

        std::stringstream inputStudent_2;
        std::string errorStrStudent_2;
        createStudent(2, "Petr", inputStudent_2);
        posApplicationFacade->enrollStudent(inputStudent_2, errorStrStudent_2);
        CHECK(errorStrStudent_2 == "not unique idPass");
    }

    SECTION("not unique idPass collision lecturer with student") {
        std::stringstream inputStudent_1;
        std::string errorStrStudent_1;
        createStudent(5, "Anna", inputStudent_1);
        posApplicationFacade->enrollStudent(inputStudent_1, errorStrStudent_1);
        CHECK(errorStrStudent_1.empty());

        std::stringstream inputLecturer_2;
        std::string errorStrLecturer_2;
        createLecturer(5, "NewLecturer", inputLecturer_2);
        posApplicationFacade->appointLecturere(inputLecturer_2, errorStrLecturer_2);
        CHECK(errorStrLecturer_2 == "not unique idPass");
        CHECK(posApplicationFacade->getCntLecturers() == 1);
    }
}

TEST_CASE("Test logic with binding") {
    std::unique_ptr<POSApplicationFacade> posApplicationFacade = std::make_unique<POSApplicationFacade>();

    std::stringstream inputStudyProgram;
    std::string errorStrStudyProgram;
    createStudyProgram("se", std::nullopt, inputStudyProgram);
    posApplicationFacade->openStudyProgram(inputStudyProgram, errorStrStudyProgram);

    std::stringstream inputSubject_1;
    std::string errorStrSubject_1;
    createSubject("c++", "se", std::nullopt, inputSubject_1);
    posApplicationFacade->addSubject(inputSubject_1, errorStrSubject_1);

    std::stringstream inputSubject_2;
    std::string errorStrSubject_2;
    createSubject("algorithms", "se", std::nullopt, inputSubject_2);
    posApplicationFacade->addSubject(inputSubject_2, errorStrSubject_2);

    std::stringstream inputStudyProgram_2;
    std::string errorStrStudyProgram_2;
    createStudyProgram("ami", std::nullopt, inputStudyProgram_2);
    posApplicationFacade->openStudyProgram(inputStudyProgram_2, errorStrStudyProgram_2);

    std::stringstream inputLecturer;
    std::string errorStrLecturer;
    createLecturer(1, "Professor", inputLecturer);
    posApplicationFacade->appointLecturere(inputLecturer, errorStrLecturer);

    std::stringstream inputStudent;
    std::string errorStrStudent;
    createStudent(2, "Student", inputStudent);
    posApplicationFacade->enrollStudent(inputStudent, errorStrStudent);

    SECTION("successful add teach subject to lecturer") {
        std::stringstream inputTeachSubject;
        std::string errorStrTeachSubject;
        createTeachSubject(1, "se", "c++", inputTeachSubject);
        posApplicationFacade->addTeachSubject(inputTeachSubject, errorStrTeachSubject);
        CHECK(errorStrTeachSubject.empty());
    }

    SECTION("add multiple teach subjects to same lecturer") {
        std::stringstream inputTeachSubject_1;
        std::string errorStrTeachSubject_1;
        createTeachSubject(1, "se", "c++", inputTeachSubject_1);
        posApplicationFacade->addTeachSubject(inputTeachSubject_1, errorStrTeachSubject_1);
        CHECK(errorStrTeachSubject_1.empty());

        std::stringstream inputTeachSubject_2;
        std::string errorStrTeachSubject_2;
        createTeachSubject(1, "se", "algorithms", inputTeachSubject_2);
        posApplicationFacade->addTeachSubject(inputTeachSubject_2, errorStrTeachSubject_2);
        CHECK(errorStrTeachSubject_2.empty());
    }

    SECTION("lecturer does not exist error") {
        std::stringstream inputTeachSubject;
        std::string errorStrTeachSubject;
        createTeachSubject(999, "se", "c++", inputTeachSubject);
        posApplicationFacade->addTeachSubject(inputTeachSubject, errorStrTeachSubject);
        CHECK(errorStrTeachSubject == "lecturer does not exist");
    }

    SECTION("studyProgram does not exist for addTeachSubject") {
        std::stringstream inputTeachSubject;
        std::string errorStrTeachSubject;
        createTeachSubject(1, "unknown_program", "c++", inputTeachSubject);
        posApplicationFacade->addTeachSubject(inputTeachSubject, errorStrTeachSubject);
        CHECK(errorStrTeachSubject == "studyProgram does not exist");
    }

    SECTION("subject does not exist error") {
        std::stringstream inputTeachSubject;
        std::string errorStrTeachSubject;
        createTeachSubject(1, "se", "physics", inputTeachSubject);
        posApplicationFacade->addTeachSubject(inputTeachSubject, errorStrTeachSubject);
        CHECK(errorStrTeachSubject == "subject does not exist");
    }

    SECTION("successful add studyProgram to student") {
        std::stringstream inputStudyProgramStudent;
        std::string errorStrStudyProgramStudent;
        createStudyProgramStudent(2, "se", inputStudyProgramStudent);
        posApplicationFacade->addStudyProgramStudent(inputStudyProgramStudent, errorStrStudyProgramStudent);
        CHECK(errorStrStudyProgramStudent.empty());
    }

    SECTION("add multiple studyPrograms to same student") {
        std::stringstream inputStudyProgramStudent_1;
        std::string errorStrStudyProgramStudent_1;
        createStudyProgramStudent(2, "se", inputStudyProgramStudent_1);
        posApplicationFacade->addStudyProgramStudent(inputStudyProgramStudent_1, errorStrStudyProgramStudent_1);
        CHECK(errorStrStudyProgramStudent_1.empty());

        std::stringstream inputStudyProgramStudent_2;
        std::string errorStrStudyProgramStudent_2;
        createStudyProgramStudent(2, "ami", inputStudyProgramStudent_2);
        posApplicationFacade->addStudyProgramStudent(inputStudyProgramStudent_2, errorStrStudyProgramStudent_2);
        CHECK(errorStrStudyProgramStudent_2.empty());
    }

    SECTION("student does not exist error") {
        std::stringstream inputStudyProgramStudent;
        std::string errorStrStudyProgramStudent;
        createStudyProgramStudent(999, "se", inputStudyProgramStudent);
        posApplicationFacade->addStudyProgramStudent(inputStudyProgramStudent, errorStrStudyProgramStudent);
        CHECK(errorStrStudyProgramStudent == "student does not exist");
    }

    SECTION("studyProgram does not exist for addStudyProgramStudent") {
        std::stringstream inputStudyProgramStudent;
        std::string errorStrStudyProgramStudent;
        createStudyProgramStudent(2, "unknown_program", inputStudyProgramStudent);
        posApplicationFacade->addStudyProgramStudent(inputStudyProgramStudent, errorStrStudyProgramStudent);
        CHECK(errorStrStudyProgramStudent == "studyProgram does not exist");
    }
}

TEST_CASE("Test logic with invalid stream format") {
    std::unique_ptr<POSApplicationFacade> posApplicationFacade = std::make_unique<POSApplicationFacade>();

    SECTION("empty stream for openStudyProgram") {
        std::stringstream emptyInput;
        std::string errorStr;
        posApplicationFacade->openStudyProgram(emptyInput, errorStr);
        CHECK(errorStr == "invalid name value");
    }

    SECTION("empty stream for appointLecturere") {
        std::stringstream emptyInput;
        std::string errorStr;
        posApplicationFacade->appointLecturere(emptyInput, errorStr);
        CHECK(errorStr == "invalid idPass value");
    }

    SECTION("string instead of number for appointLecturere idPass") {
        std::stringstream invalidInput("not_a_number Name");
        std::string errorStr;
        posApplicationFacade->appointLecturere(invalidInput, errorStr);
        CHECK(errorStr == "invalid idPass value");
    }

    SECTION("empty stream for enrollStudent") {
        std::stringstream emptyInput;
        std::string errorStr;
        posApplicationFacade->enrollStudent(emptyInput, errorStr);
        CHECK(errorStr == "invalid idPass value");
    }

    SECTION("string instead of number for enrollStudent idPass") {
        std::stringstream invalidInput("string_id StudentName");
        std::string errorStr;
        posApplicationFacade->enrollStudent(invalidInput, errorStr);
        CHECK(errorStr == "invalid idPass value");
    }

    SECTION("empty stream for addSubject") {
        std::stringstream emptyInput;
        std::string errorStr;
        posApplicationFacade->addSubject(emptyInput, errorStr);
        CHECK(errorStr == "invalid name value");
    }

    SECTION("partial stream for addTeachSubject") {
        std::stringstream partialInput("1 only_one_program");
        std::string errorStr;
        posApplicationFacade->addTeachSubject(partialInput, errorStr);
        CHECK(errorStr == "invalid nameSubject value");
    }

    SECTION("empty stream for addStudyProgramStudent") {
        std::stringstream emptyInput;
        std::string errorStr;
        posApplicationFacade->addStudyProgramStudent(emptyInput, errorStr);
        CHECK(errorStr == "invalid name idPassStudent");
    }
}

TEST_CASE("Test logic with ScoreInt") {
    SECTION("valid range and default constructor") {
        REQUIRE_NOTHROW(ScoreInt(std::make_pair(0, 10)));
        REQUIRE_NOTHROW(ScoreInt());
    }

    SECTION("invalid range throw invalid_argument") {
        REQUIRE_THROWS_AS(ScoreInt(std::make_pair(-1, 10)), std::invalid_argument);
        REQUIRE_THROWS_AS(ScoreInt(std::make_pair(10, 5)), std::invalid_argument);
    }

    SECTION("AssessmentSubject constructor calls") {
        REQUIRE_NOTHROW(AssessmentSubject(1, std::nullopt));
        REQUIRE_NOTHROW(AssessmentSubject(1, std::make_pair(0, 100), "desc"));
    }

    SECTION("updateScore inside range and outside range") {
        ScoreInt score(std::make_pair(0, 10));
        REQUIRE_NOTHROW(score.updateScore(5));
        REQUIRE_NOTHROW(score.updateScore(15));
        REQUIRE_NOTHROW(score.updateScore(-1));
    }
}

TEST_CASE("Test logic with direct Domain classes") {
    SECTION("direct Subject creation and getName") {
        Subject subject("algebra", "se", "algebra_description");
        CHECK(subject.getName() == "algebra");
    }

    SECTION("direct StudyProgram addSubject and getIndSubject") {
        StudyProgram program("se", std::nullopt);
        CHECK(program.getNameStudyProgram() == "se");
        CHECK(program.getSubjects().empty());

        auto math = std::make_shared<Subject>("math", "se", std::nullopt);
        program.addSubject(math);
        CHECK(program.getSubjects().size() == 1);

        std::string queryFound = "math";
        auto indFound = program.getIndSubject(queryFound);
        CHECK(indFound.has_value());
        CHECK(indFound.value() == 0);

        std::string queryNotFound = "history";
        auto indNotFound = program.getIndSubject(queryNotFound);
        CHECK(!indNotFound.has_value());
    }

    SECTION("direct Student and Lecturer getIdPass") {
        Student student(10, "Ivan");
        CHECK(student.getIdPass() == 10);

        Lecturer lecturer(20, "Evgeniy");
        CHECK(lecturer.getIdPass() == 20);

        auto math = std::make_shared<Subject>("math", "se", std::nullopt);
        REQUIRE_NOTHROW(lecturer.addSubjectTeach(math));

        auto prog = std::make_shared<StudyProgram>("se", std::nullopt);
        REQUIRE_NOTHROW(student.addStudyProgram(prog));
    }
}

TEST_CASE("Assessment parameters survive construction and parsing") {
    auto repository = std::make_shared<InMemoryPOSRepository>();
    POSApplicationFacade app(repository);
    std::string error;
    REQUIRE(app.openStudyProgram("se", std::nullopt, error));
    REQUIRE(app.addSubject("math", "se", std::nullopt, error));
    auto subject = repository->findStudyProgram("se")->getSubjects().front();
    REQUIRE(subject->getAssessmentSubject() == nullptr);

    SECTION("custom range and multiword description") {
        std::stringstream input("math se 0.5 0 100 final exam");
        app.addAssessmentSubject(input, error);
        REQUIRE(error.empty());
        auto assessment = subject->getAssessmentSubject();
        REQUIRE(assessment != nullptr);
        CHECK(assessment->getWeight() == 0.5);
        CHECK(assessment->getRange() == std::make_pair(0, 100));
        CHECK(assessment->getDescription() == "final exam");
    }
    SECTION("default range without description") {
        std::stringstream input("math se 1   ");
        app.addAssessmentSubject(input, error);
        REQUIRE(error.empty());
        REQUIRE(subject->getAssessmentSubject() != nullptr);
        CHECK(subject->getAssessmentSubject()->getRange() == std::make_pair(0, 10));
        CHECK_FALSE(subject->getAssessmentSubject()->getDescription().has_value());
    }
    SECTION("invalid update preserves the previous assessment") {
        std::stringstream valid("math se 0.5 0 100 exam");
        app.addAssessmentSubject(valid, error);
        REQUIRE(error.empty());
        auto previous = subject->getAssessmentSubject();
        REQUIRE(previous != nullptr);
        for(const auto& command : {
                "math se 0", "math se -1", "math se 1 10 5",
                "math se 1 -1 10", "math se 1 0", "math se 1 0 abc",
                "math se 1 0 100abc", "math se 1 0 99999999999999999999",
                "math se 1e999", "math unknown 1", "unknown se 1"}) {
            error.clear();
            std::stringstream input(command);
            REQUIRE_NOTHROW(app.addAssessmentSubject(input, error));
            CHECK_FALSE(error.empty());
            CHECK(subject->getAssessmentSubject() == previous);
            CHECK(previous->getWeight() == 0.5);
            CHECK(previous->getRange() == std::make_pair(0, 100));
            CHECK(previous->getDescription() == "exam");
        }
    }
}

TEST_CASE("Assessment constructors protect their invariants") {
    std::optional<std::pair<int, int>> range = std::make_pair(0, 100);
    AssessmentSubject assessment(0.25, range, "exam");
    CHECK(assessment.getWeight() == 0.25);
    CHECK(assessment.getRange() == range.value());
    CHECK(assessment.getDescription() == "exam");
    AssessmentSubject defaults(1, std::nullopt, std::nullopt);
    CHECK(defaults.getRange() == std::make_pair(0, 10));
    CHECK(defaults.getWeight() == 1);
    CHECK_FALSE(defaults.getDescription().has_value());
    for(double weight : {0.0, -1.0, std::numeric_limits<double>::infinity(),
                          std::numeric_limits<double>::quiet_NaN()}) {
        REQUIRE_THROWS_AS(AssessmentSubject(weight, range, "exam"), std::invalid_argument);
        REQUIRE_THROWS_AS(AssessmentSubject(weight, std::make_pair(0, 10), "exam"), std::invalid_argument);
        REQUIRE_THROWS_AS(AssessmentSubject(weight, std::nullopt), std::invalid_argument);
    }
    range = std::make_pair(10, 5);
    REQUIRE_THROWS_AS(AssessmentSubject(1, range, "exam"), std::invalid_argument);
}

TEST_CASE("Console routes assessment creation and reports errors") {
    ConsoleApp app;
    app.init();
    for(const auto& command : {"studyProgram se", "subject math se",
                              "add_assessment math se 0.5 0 100 final exam"}) {
        std::stringstream input(command);
        CHECK(app.execute(input).empty());
    }
    for(const auto& command : {"add_assessment math se -1",
                              "add_assessment math se 1 0",
                              "add_assessment unknown se 1",
                              "add_assessment math se 1 10 5"}) {
        std::stringstream input(command);
        CHECK_FALSE(app.execute(input).empty());
    }
}


TEST_CASE("Rubric keeps independent criteria and individual evaluations") {
    Subject subject("math", "se", std::nullopt);
    subject.addCriterion("exam", 100, 0.7);
    subject.addCriterion("homework", 10, 0.3);
    CHECK(subject.getCriteria().size() == 2);
    CHECK(subject.getCriteria().at("exam").getWeight() == 0.7);
    CHECK_FALSE(subject.getEvaluation(1, "exam").has_value());
    subject.setEvaluation(1, "exam", 80);
    subject.setEvaluation(2, "exam", 0);
    subject.setEvaluation(1, "homework", 10);
    subject.setEvaluation(1, "exam", 100);
    CHECK(subject.getEvaluation(1, "exam") == 100);
    CHECK(subject.getEvaluation(2, "exam") == 0);
    CHECK(subject.getEvaluation(1, "homework") == 10);
    REQUIRE_THROWS_AS(subject.setEvaluation(1, "exam", 101), std::invalid_argument);
    REQUIRE_THROWS_AS(subject.setEvaluation(1, "exam", -1), std::invalid_argument);
    REQUIRE_THROWS_AS(subject.setEvaluation(1, "unknown", 1), std::invalid_argument);
    REQUIRE_THROWS_AS(subject.setEvaluation(-1, "exam", 1), std::invalid_argument);
    CHECK(subject.getEvaluation(1, "exam") == 100);
    REQUIRE_THROWS_AS(subject.addCriterion("exam", 10, 1), std::invalid_argument);
    REQUIRE_THROWS_AS(subject.addCriterion("", 10, 1), std::invalid_argument);
    REQUIRE_THROWS_AS(subject.addCriterion("zero", 0, 1), std::invalid_argument);
    REQUIRE_THROWS_AS(subject.addCriterion("bad_weight", 10, -1), std::invalid_argument);
    CHECK(subject.getCriteria().size() == 2);
}

TEST_CASE("Legacy assessment belongs to the rubric and protects recorded scores") {
    Subject subject("math", "se", std::nullopt);
    subject.addAssessmentSubject(std::make_unique<AssessmentSubject>(
        1, std::make_pair(0, 100), std::nullopt));
    subject.setEvaluation(1, "default", 80);
    REQUIRE_THROWS_AS(subject.addAssessmentSubject(std::make_unique<AssessmentSubject>(
        1, std::make_pair(0, 10), std::nullopt)), std::invalid_argument);
    REQUIRE_THROWS_AS(subject.addAssessmentSubject(nullptr), std::invalid_argument);
    CHECK(subject.getAssessmentSubject()->getRange() == std::make_pair(0, 100));
    CHECK(subject.getEvaluation(1, "default") == 80);
}

TEST_CASE("Evaluation use case rejects unknown students and isolates subjects") {
    auto repository = std::make_shared<InMemoryPOSRepository>();
    POSApplicationFacade app(repository);
    std::string error;
    REQUIRE(app.openStudyProgram("se", std::nullopt, error));
    REQUIRE(app.enrollStudent(1, "Ivan", error));
    for(const auto& name : {"math", "physics"}) {
        REQUIRE(app.addSubject(name, "se", std::nullopt, error));
        app.addCriterion("se", name, "exam", 10, 1);
    }
    app.setEvaluation("se", "math", 1, "exam", 7);
    const auto& subjects = repository->findStudyProgram("se")->getSubjects();
    CHECK(subjects[0]->getEvaluation(1, "exam") == 7);
    CHECK_FALSE(subjects[1]->getEvaluation(1, "exam").has_value());
    REQUIRE_THROWS_AS(app.setEvaluation("se", "math", 99, "exam", 5), std::invalid_argument);
    REQUIRE_THROWS_AS(app.setEvaluation("se", "missing", 1, "exam", 5), std::invalid_argument);
    REQUIRE_THROWS_AS(app.addCriterion("missing", "math", "exam", 10, 1), std::invalid_argument);
    CHECK_FALSE(subjects[0]->getEvaluation(99, "exam").has_value());
}

TEST_CASE("Console creates criteria and sets or corrects evaluations") {
    ConsoleApp app;
    app.init();
    for(const auto& command : {"studyProgram se", "subject math se", "student 1 Ivan",
                              "criterion se math exam 100 0.7", "criterion se math homework 10 0.3",
                              "evaluate se math 1 exam 80", "evaluate se math 1 exam 90"}) {
        std::stringstream input(command);
        CHECK(app.execute(input).empty());
    }
    for(const auto& command : {"evaluate se math 99 exam 80", "evaluate se math 1 exam 101",
                              "evaluate se math 1 missing 5", "evaluate se math 1 exam",
                              "evaluate se math 1 exam 5junk", "evaluate se math 1 exam 5 extra",
                              "criterion se math other 10 1junk", "criterion se math exam 10 1"}) {
        std::stringstream input(command);
        CHECK_FALSE(app.execute(input).empty());
    }
}


TEST_CASE("Weighted final normalizes maxima and recomputes after corrections") {
    Subject subject("math", "se", std::nullopt);
    RequireAllEvaluations strict;
    FinalScoreService service(strict);
    subject.addCriterion("exam", 100, 7);
    subject.addCriterion("homework", 10, 3);
    subject.setEvaluation(1, "exam", 80);
    subject.setEvaluation(1, "homework", 9);
    auto result = service.calculate(subject, 1);
    CHECK(result.value == Catch::Approx(8.3));
    CHECK(result.gradedCriteria == 2);
    CHECK(result.totalCriteria == 2);
    subject.setEvaluation(1, "exam", 100);
    CHECK(service.calculate(subject, 1).value == Catch::Approx(9.7));
    subject.addCriterion("project", 10, 10);
    REQUIRE_THROWS_AS(service.calculate(subject, 1), std::invalid_argument);
    subject.setEvaluation(1, "project", 10);
    CHECK(service.calculate(subject, 1).value == Catch::Approx(9.85));
}

TEST_CASE("Missing-score strategies distinguish absent evaluations from zero") {
    Subject subject("math", "se", std::nullopt);
    subject.addCriterion("exam", 100, 0.7);
    subject.addCriterion("homework", 10, 0.3);
    subject.setEvaluation(1, "exam", 80);
    RequireAllEvaluations strict;
    MissingAsZero zero;
    REQUIRE_THROWS_AS(FinalScoreService(strict).calculate(subject, 1), std::invalid_argument);
    auto result = FinalScoreService(zero).calculate(subject, 1);
    CHECK(result.value == Catch::Approx(5.6));
    CHECK(result.gradedCriteria == 1);
    CHECK(result.totalCriteria == 2);
    CHECK_FALSE(subject.getEvaluation(1, "homework").has_value());
    CHECK(FinalScoreService(zero).calculate(subject, 2).value == 0);
    subject.setEvaluation(1, "homework", 0);
    CHECK(FinalScoreService(strict).calculate(subject, 1).value == Catch::Approx(5.6));
    CHECK(FinalScoreService(strict).calculate(subject, 1).gradedCriteria == 2);
}

TEST_CASE("Final calculation rejects undefined rubrics and handles large weights") {
    Subject subject("math", "se", std::nullopt);
    MissingAsZero zero;
    FinalScoreService service(zero);
    REQUIRE_THROWS_AS(service.calculate(subject, 1), std::invalid_argument);
    subject.addAssessmentSubject(std::make_unique<AssessmentSubject>(
        1, std::make_pair(0, 0), std::nullopt));
    REQUIRE_THROWS_AS(service.calculate(subject, 1), std::invalid_argument);
    Subject large("physics", "se", std::nullopt);
    large.addCriterion("exam", 10, std::numeric_limits<double>::max());
    large.addCriterion("homework", 100, std::numeric_limits<double>::max());
    large.setEvaluation(1, "exam", 10);
    large.setEvaluation(1, "homework", 50);
    CHECK(service.calculate(large, 1).value == Catch::Approx(7.5));
    REQUIRE_THROWS_AS(service.calculate(large, -1), std::invalid_argument);
}

TEST_CASE("Final use case checks student and subject existence") {
    auto repository = std::make_shared<InMemoryPOSRepository>();
    POSApplicationFacade app(repository);
    MissingAsZero zero;
    std::string error;
    REQUIRE(app.openStudyProgram("se", std::nullopt, error));
    REQUIRE(app.addSubject("math", "se", std::nullopt, error));
    REQUIRE(app.enrollStudent(1, "Ivan", error));
    app.addCriterion("se", "math", "exam", 100, 1);
    app.setEvaluation("se", "math", 1, "exam", 80);
    CHECK(app.calculateFinal("se", "math", 1, zero).value == Catch::Approx(8));
    REQUIRE_THROWS_AS(app.calculateFinal("se", "math", 99, zero), std::invalid_argument);
    REQUIRE_THROWS_AS(app.calculateFinal("se", "missing", 1, zero), std::invalid_argument);
    REQUIRE_THROWS_AS(app.calculateFinal("missing", "math", 1, zero), std::invalid_argument);
}

TEST_CASE("Viewing, cancelling and exporting evaluations") {
    ApplicationContainer container;
    auto app = container.facade();
    std::string error;
    REQUIRE(app->openStudyProgram("se", std::nullopt, error));
    REQUIRE(app->addSubject("math", "se", std::nullopt, error));
    REQUIRE(app->enrollStudent(1, "Ivan, \"First\"", error));
    app->addCriterion("se", "math", "exam", 10, 1);
    app->setEvaluation("se", "math", 1, "exam", 8);

    SECTION("view and cancel through console") {
        auto console = container.console();
        console->init();
        std::stringstream input("cancel se math 1 exam");
        CHECK(console->execute(input).empty());
        CHECK(app->getCriteria("se", "math").size() == 1);
        CHECK_FALSE(app->getEvaluations("se", "math", 1).at("exam").has_value());
        CHECK(app->calculateFinal("se", "math", 1, MissingAsZero()).value == 0);
        REQUIRE_THROWS(app->calculateFinal("se", "math", 1, RequireAllEvaluations()));
        REQUIRE_THROWS(app->cancelEvaluation("se", "math", 99, "exam"));
        REQUIRE_THROWS(app->cancelEvaluation("se", "math", 1, "unknown"));
    }
    SECTION("CSV escaping and errors") {
        std::ostringstream output;
        CsvFinalExporter exporter(output);
        app->exportFinals("se", "math", RequireAllEvaluations(), exporter);
        CHECK(output.str() == "student_id,student_name,final_score,graded,total\n1,\"Ivan, \"\"First\"\"\",8.00,1,1\n");
        app->cancelEvaluation("se", "math", 1, "exam");
        const auto previous = output.str();
        REQUIRE_THROWS(app->exportFinals("se", "math", RequireAllEvaluations(), exporter));
        CHECK(output.str() == previous);
        output.setstate(std::ios::badbit);
        REQUIRE_THROWS(app->exportFinals("se", "math", MissingAsZero(), exporter));
    }
    SECTION("factory and dependency validation") {
        CHECK(EvaluationFactory::create(1, 10, {0, 10}).value() == 10);
        REQUIRE_THROWS(EvaluationFactory::create(1, 12, {0, 10}));
        REQUIRE_THROWS(Student(-1, "Ivan"));
        REQUIRE_THROWS(ApplicationContainer(nullptr));
        REQUIRE_THROWS(POSApplicationFacade(nullptr));
        REQUIRE_THROWS(ConsoleApp(nullptr));
    }
}
