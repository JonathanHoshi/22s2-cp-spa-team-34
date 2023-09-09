#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "catch.hpp"
#include "common/ConversionUtils.h"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "qps/argument/entity/stmt/CallStmtEntity.h"
#include "qps/argument/entity/stmt/PrintStmtEntity.h"
#include "qps/argument/entity/stmt/ReadStmtEntity.h"
#include "qps/argument/input/StringInput.h"
#include "qps/argument/input/IntInput.h"
#include "qps/clause/strategy/WithStrategy.h"
#include "../stub_entity/StubConstProcVarGetter.cpp"
#include "../stub_entity/StubStmtGetter.cpp"
#include "../QueryFunction.h"

namespace test_with_eval {
    StubStmtGetter stmtInterface;
    StubConstProcVarGetter constProcVarInterface;

    std::unordered_map<int, std::string> readMap = {{2, "sp"},
        {7, "qps"},
        {9, "pkb"}};
    std::unordered_map<int, std::string> printMap = {{5, "sp"},
        {11, "pkb"},
        {15, "qps"}};
    std::unordered_map<int, std::string> callStmtMap = {{1, "cx"},
        {4, "jon"},
        {13, "jon"}};
    std::unordered_set<int> ifStmtSet = {10};
    std::unordered_set<int> whileStmtSet = {14};
    std::unordered_set<int> assignStmtSet = {3, 6, 8, 12};
    std::unordered_set<int> constSet = {1, 2, 7};
    std::unordered_set<std::string> varSet = {"pkb", "qps", "sp", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    std::unordered_set<std::string> procSet = {"cx", "fred", "jon", "nat", "ryan"};

    void initializeInterfaces() {
        constProcVarInterface.setVarEntries(varSet);
        constProcVarInterface.setProcEntries(procSet);
        constProcVarInterface.setConstEntries(constSet);
        stmtInterface.setReadStmtEntries(readMap);
        stmtInterface.setPrintStmtEntries(printMap);
        stmtInterface.setCallStmtEntries(callStmtMap);
        stmtInterface.setIfStmtEntries(ifStmtSet);
        stmtInterface.setWhileStmtEntries(whileStmtSet);
        stmtInterface.setAssignStmtEntries(assignStmtSet);
    }

    // for expected results
    std::unordered_set<int> stmtSet = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
}

using namespace test_with_eval;
using namespace query_func;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Evaluate Single Select - Single With") {
    initializeInterfaces();
    SECTION("Left Input") {
        SECTION("with 1 == s.stmt#) - Output") {
            std::unordered_set<std::string> expectedResult = {"1"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("1");
            std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "stmt#");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("with 'sp' == pn.varName) - Output") {
            std::unordered_set<std::string> expectedResult = {"5"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<PrintStmtEntity>(&stmtInterface, "pn", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("sp");
            std::shared_ptr<Argument> secondArg = std::make_shared<PrintStmtEntity>(&stmtInterface, "pn", "varName");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("with 'sp' == re.varName) - Output") {
            std::unordered_set<std::string> expectedResult = {"2"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ReadStmtEntity>(&stmtInterface, "re", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("sp");
            std::shared_ptr<Argument> secondArg = std::make_shared<ReadStmtEntity>(&stmtInterface, "re", "varName");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("with 'jon' == cl.procName) - Output") {
            std::unordered_set<std::string> expectedResult = {"4", "13"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<CallStmtEntity>(&stmtInterface, "cl", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("jon");
            std::shared_ptr<Argument> secondArg = std::make_shared<CallStmtEntity>(&stmtInterface, "cl", "procName");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Right Input") {
        SECTION("with s.stmt# == 1) - Output") {
            std::unordered_set<std::string> expectedResult = {"1"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "stmt#");
            std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("1");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("with pn.varName == 'sp') - Output") {
            std::unordered_set<std::string> expectedResult = {"5"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<PrintStmtEntity>(&stmtInterface, "pn", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<PrintStmtEntity>(&stmtInterface, "pn", "varName");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("sp");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("with re.varName == 'sp') - Output") {
            std::unordered_set<std::string> expectedResult = {"2"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ReadStmtEntity>(&stmtInterface, "re", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<ReadStmtEntity>(&stmtInterface, "re", "varName");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("sp");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("with cl.procName == 'jon') - Output") {
            std::unordered_set<std::string> expectedResult = {"4", "13"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<CallStmtEntity>(&stmtInterface, "cl", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<CallStmtEntity>(&stmtInterface, "cl", "procName");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("jon");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Both Input") {
        SECTION("with 1 == 1) - Output") {
            std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("1");
            std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("1");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("with 'j' == 'k') - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("j");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("k");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("No Input") {
        SECTION("with s.stmt# == re.stmt#) - Output") {
            std::unordered_set<std::string> expectedResult = {"2", "7", "9"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "stmt#");
            std::shared_ptr<Argument> secondArg = std::make_shared<ReadStmtEntity>(&stmtInterface, "re", "stmt#");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("with pn.stmt# == re.stmt#) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<PrintStmtEntity>(&stmtInterface, "pn", "stmt#");
            std::shared_ptr<Argument> secondArg = std::make_shared<ReadStmtEntity>(&stmtInterface, "re", "stmt#");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("with pn.varName == re.varName) - Output") {
            std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "stmt#");
            std::shared_ptr<Argument> firstArg = std::make_shared<PrintStmtEntity>(&stmtInterface, "pn", "varName");
            std::shared_ptr<Argument> secondArg = std::make_shared<ReadStmtEntity>(&stmtInterface, "re", "varName");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<WithStrategy>(), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }
}