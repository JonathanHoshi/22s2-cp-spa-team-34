#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "catch.hpp"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "qps/argument/entity/stmt/IfStmtEntity.h"
#include "qps/argument/entity/stmt/WhileStmtEntity.h"
#include "qps/argument/input/StringInput.h"
#include "qps/clause/strategy/pattern/IfStrategy.h"
#include "qps/clause/strategy/pattern/WhileStrategy.h"
#include "../stub_entity/StubConstProcVarGetter.cpp"
#include "../stub_entity/StubStmtGetter.cpp"
#include "../stub_clause/StubIfWhilePatternGetter.cpp"
#include "../QueryFunction.h"

namespace test_ifwhilepattern_eval {
    StubIfWhilePatternGetter ifPatternInterface;
    StubIfWhilePatternGetter whilePatternInterface;
    StubStmtGetter stmtInterface;
    StubConstProcVarGetter constProcVarInterface;

    std::unordered_map<int, std::string> callStmtMap = {{4, "contemplate"},
        {5, "play"},
        {6, "sleep"}};
    std::unordered_set<int> assignStmtSet = {1, 7, 9, 10, 11, 13, 14, 16};
    std::unordered_set<int> ifStmtSet = {3, 8, 12};
    std::unordered_set<int> whileStmtSet = {2, 15};
    std::unordered_set<std::string> varSet = {"body", "chance", "energy", "fifty", "lazy", "mood", "ninety",
        "play", "random", "recover", "threshold", "tired", "work"};
    std::unordered_set<std::string> procSet = {"contemplate", "jon", "play", "sleep"};
    std::unordered_map<int, std::unordered_set<std::string>> ifPatternEntries = {{3, {"mood", "work"}},
        {8, {"chance", "fifty"}},
        {12, {"chance", "ninety"}}};
    std::unordered_map<int, std::unordered_set<std::string>> whilePatternEntries = {{2, {"mood", "tired"}},
        {15, {"body", "energy", "threshold"}}};

    void initializeInterfaces() {
        ifPatternInterface.setPatternEntries(ifPatternEntries);
        whilePatternInterface.setPatternEntries(whilePatternEntries);
        constProcVarInterface.setVarEntries(varSet);
        constProcVarInterface.setProcEntries(procSet);
        stmtInterface.setCallStmtEntries(callStmtMap);
        stmtInterface.setAssignStmtEntries(assignStmtSet);
        stmtInterface.setIfStmtEntries(ifStmtSet);
        stmtInterface.setWhileStmtEntries(whileStmtSet);
    }
}

using namespace test_ifwhilepattern_eval;
using namespace query_func;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Evaluate Single Select - Single If Pattern") {
    initializeInterfaces();

    SECTION("Right Input") {
        SECTION("pattern ifs('chance', _, _) - Output") {
            std::unordered_set<std::string> expectedResult = {"8", "12"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<IfStmtEntity>(&stmtInterface, "ifs", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IfStmtEntity>(&stmtInterface, "ifs", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("chance");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<IfStrategy>(&ifPatternInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("pattern ifs('tired', _, _) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<IfStmtEntity>(&stmtInterface, "ifs", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IfStmtEntity>(&stmtInterface, "ifs", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("tired");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<IfStrategy>(&ifPatternInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("No Input") {
        SECTION("pattern ifs(v, _, _)") {
            SECTION("Select ifs - Output") {
                std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(ifStmtSet);
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<IfStmtEntity>(&stmtInterface, "ifs", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IfStmtEntity>(&stmtInterface, "ifs", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<IfStrategy>(&ifPatternInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select v - Output") {
                std::unordered_set<std::string> expectedResult = {"chance", "fifty", "mood", "ninety", "work"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IfStmtEntity>(&stmtInterface, "ifs", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<IfStrategy>(&ifPatternInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("pattern ifs(_, _, _) - Output") {
            std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(ifStmtSet);
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<IfStmtEntity>(&stmtInterface, "ifs", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IfStmtEntity>(&stmtInterface, "ifs", "");

            std::shared_ptr<WildcardEntity> wcEntity = std::make_shared<WildcardEntity>();
            wcEntity->assignEntityType(std::make_shared<VariableEntity>(&constProcVarInterface, "", ""));
            std::shared_ptr<Argument> secondArg = wcEntity;

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<IfStrategy>(&ifPatternInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }
}

TEST_CASE("Evaluate Single Select - Single While Pattern") {
    initializeInterfaces();

    SECTION("Right Input") {
        SECTION("pattern w('mood', _, _) - Output") {
            std::unordered_set<std::string> expectedResult = {"2"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<WhileStmtEntity>(&stmtInterface, "w", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<WhileStmtEntity>(&stmtInterface, "w", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("mood");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WhileStrategy>(&whilePatternInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("pattern w('fifty', _, _) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<WhileStmtEntity>(&stmtInterface, "w", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<WhileStmtEntity>(&stmtInterface, "w", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("fifty");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WhileStrategy>(&whilePatternInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("No Input") {
        SECTION("pattern w(v, _, _)") {
            SECTION("Select w - Output") {
                std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(whileStmtSet);
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<WhileStmtEntity>(&stmtInterface, "w", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<WhileStmtEntity>(&stmtInterface, "w", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<WhileStrategy>(&whilePatternInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select v - Output") {
                std::unordered_set<std::string> expectedResult = {"body", "energy", "mood", "threshold", "tired"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<WhileStmtEntity>(&stmtInterface, "w", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<WhileStrategy>(&whilePatternInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("pattern w(_, _, _) - Output") {
            std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(whileStmtSet);
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<WhileStmtEntity>(&stmtInterface, "w", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<WhileStmtEntity>(&stmtInterface, "w", "");

            std::shared_ptr<WildcardEntity> wcEntity = std::make_shared<WildcardEntity>();
            wcEntity->assignEntityType(std::make_shared<VariableEntity>(&constProcVarInterface, "", ""));
            std::shared_ptr<Argument> secondArg = wcEntity;

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WhileStrategy>(&whilePatternInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }
}
