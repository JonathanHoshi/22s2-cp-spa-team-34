#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

#include "catch.hpp"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "qps/argument/entity/stmt/AssignStmtEntity.h"
#include "qps/argument/entity/stmt/IfStmtEntity.h"
#include "qps/argument/entity/stmt/WhileStmtEntity.h"
#include "qps/argument/input/StringInput.h"
#include "qps/clause/strategy/pattern/AssignStrategy.h"
#include "../stub_entity/StubConstProcVarGetter.cpp"
#include "../stub_entity/StubStmtGetter.cpp"
#include "../stub_clause/StubAssignPatternGetter.cpp"
#include "common/ASTUtil.h"
#include "common/ASTBuilder.h"
#include "../QueryFunction.h"

namespace test_assignpattern_eval {
    StubAssignPatternGetter assignPatternInterface;
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

    std::unordered_map<int, std::pair<std::string, std::shared_ptr<ExpressionNode>>> assignPatternEntries;
    
    // This unit test is not entirely a unit test as it utilize the ASTUtil functions
    void setupAssignStmt() {
        // 1: mood = random;
        std::shared_ptr<ExpressionNode> ast1 = ASTUtil::convertToAST("random");
        std::pair<std::string, std::shared_ptr<ExpressionNode>> pair1("mood", ast1);
        assignPatternEntries.emplace(1, pair1);

        // 7: chance = random;
        std::shared_ptr<ExpressionNode> ast2 = ASTUtil::convertToAST("random");
        std::pair<std::string, std::shared_ptr<ExpressionNode>> pair2("chance", ast2);
        assignPatternEntries.emplace(7, pair2);

        // 9: mood = lazy;
        std::shared_ptr<ExpressionNode> ast3 = ASTUtil::convertToAST("lazy");
        std::pair<std::string, std::shared_ptr<ExpressionNode>> pair3("mood", ast3);
        assignPatternEntries.emplace(9, pair3);

        // 10: mood = work;
        std::shared_ptr<ExpressionNode> ast4 = ASTUtil::convertToAST("work");
        std::pair<std::string, std::shared_ptr<ExpressionNode>> pair4("mood", ast4);
        assignPatternEntries.emplace(10, pair4);

        // 11: chance = random;
        std::shared_ptr<ExpressionNode> ast5 = ASTUtil::convertToAST("random");
        std::pair<std::string, std::shared_ptr<ExpressionNode>> pair5("chance", ast5);
        assignPatternEntries.emplace(11, pair5);

        // 13: mood = play;
        std::shared_ptr<ExpressionNode> ast6 = ASTUtil::convertToAST("play");
        std::pair<std::string, std::shared_ptr<ExpressionNode>> pair6("mood", ast6);
        assignPatternEntries.emplace(13, pair6);

        // 14: mood = lazy;
        std::shared_ptr<ExpressionNode> ast7 = ASTUtil::convertToAST("lazy");
        std::pair<std::string, std::shared_ptr<ExpressionNode>> pair7("mood", ast7);
        assignPatternEntries.emplace(14, pair7);

        // 16: energy = energy + recover;
        std::shared_ptr<ExpressionNode> ast8 = ASTUtil::convertToAST("energy + recover");
        std::pair<std::string, std::shared_ptr<ExpressionNode>> pair8("energy", ast8);
        assignPatternEntries.emplace(16, pair8);
    }

    void initializeInterfaces() {
        setupAssignStmt();
        constProcVarInterface.setVarEntries(varSet);
        constProcVarInterface.setProcEntries(procSet);
        stmtInterface.setCallStmtEntries(callStmtMap);
        stmtInterface.setAssignStmtEntries(assignStmtSet);
        stmtInterface.setIfStmtEntries(ifStmtSet);
        stmtInterface.setWhileStmtEntries(whileStmtSet);
        assignPatternInterface.setAssignPatternEntries(assignPatternEntries);
    }

}

using namespace test_assignpattern_eval;
using namespace query_func;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Evaluate Single Select - Single Assign Pattern") {
    initializeInterfaces();

    SECTION("Var Input") {
        SECTION("pattern a('chance', _) - Output") {
            std::unordered_set<std::string> expectedResult = {"7", "11"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("chance");
            std::shared_ptr<Argument> thirdArg = std::make_shared<WildcardEntity>();

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<AssignStrategy>(&assignPatternInterface), firstArg, secondArg, thirdArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("pattern a('tired', _, _) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("tired");
            std::shared_ptr<Argument> thirdArg = std::make_shared<WildcardEntity>();

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<AssignStrategy>(&assignPatternInterface), firstArg, secondArg, thirdArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Expression Input - Partial") {
        SECTION("pattern a(v, _'energy'_) - Output") {
            std::unordered_set<std::string> expectedResult = { "16" };
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            std::shared_ptr<ExpressionNode> exprAST = ASTUtil::convertToAST("energy");
            std::shared_ptr<Argument> thirdArg = std::make_shared<ExpressionInput>("energy", exprAST, true);

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<AssignStrategy>(&assignPatternInterface, true), firstArg, secondArg, thirdArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("pattern a(v, _'mood'_) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
            std::shared_ptr<ExpressionNode> exprAST = ASTUtil::convertToAST("mood");
            std::shared_ptr<Argument> thirdArg = std::make_shared<ExpressionInput>("mood", exprAST, true);

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<AssignStrategy>(&assignPatternInterface, true), firstArg, secondArg, thirdArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Expression Input - Full") {
        SECTION("pattern a(v, 'energy + recover') - Output") {
            std::unordered_set<std::string> expectedResult = { "16" };
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            std::shared_ptr<ExpressionNode> exprAST = ASTUtil::convertToAST("energy + recover");
            std::shared_ptr<Argument> thirdArg = std::make_shared<ExpressionInput>("energy + recover", exprAST, false);

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<AssignStrategy>(&assignPatternInterface), firstArg, secondArg, thirdArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("pattern a(v, 'energy') - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
            std::shared_ptr<ExpressionNode> exprAST = ASTUtil::convertToAST("energy");
            std::shared_ptr<Argument> thirdArg = std::make_shared<ExpressionInput>("energy", exprAST, false);

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<AssignStrategy>(&assignPatternInterface), firstArg, secondArg, thirdArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Both Input") {
        SECTION("pattern a('mood', _'lazy'_) - Output") {
            std::unordered_set<std::string> expectedResult = { "9", "14" };
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("mood");
            std::shared_ptr<ExpressionNode> exprAST = ASTUtil::convertToAST("lazy");
            std::shared_ptr<Argument> thirdArg = std::make_shared<ExpressionInput>("lazy", exprAST, true);

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<AssignStrategy>(&assignPatternInterface, true), firstArg, secondArg, thirdArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("pattern a('mood', _'energy'_) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("mood");
            std::shared_ptr<ExpressionNode> exprAST = ASTUtil::convertToAST("energy");
            std::shared_ptr<Argument> thirdArg = std::make_shared<ExpressionInput>("energy", exprAST, true);

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<AssignStrategy>(&assignPatternInterface, true), firstArg, secondArg, thirdArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("No Input") {
        SECTION("pattern a(v, _)") {
            SECTION("Select a - Output") {
                std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(assignStmtSet);
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> thirdArg = std::make_shared<WildcardEntity>();

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<AssignStrategy>(&assignPatternInterface), firstArg, secondArg, thirdArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select v - Output") {
                std::unordered_set<std::string> expectedResult = { "chance", "energy", "mood" };
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> thirdArg = std::make_shared<WildcardEntity>();

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<AssignStrategy>(&assignPatternInterface), firstArg, secondArg, thirdArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }
}
