#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "catch.hpp"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "../stub_entity/StubConstProcVarGetter.cpp"
#include "../stub_entity/StubStmtGetter.cpp"
#include "../QueryFunction.h"

namespace test_entity_eval {
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

using namespace test_entity_eval;
using namespace query_func;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Single Entity Select All") {
    initializeInterfaces();
    SECTION("Variable Select All") {
        std::unordered_set<std::string> expectedResult = varSet;
        std::vector<std::shared_ptr<Clause>> clauseList;

        SECTION("variable v; Select v") {
            std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("variable k; Select k") {
            std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "k", "");

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Procedure Select All") {
        std::unordered_set<std::string> expectedResult = procSet;
        std::vector<std::shared_ptr<Clause>> clauseList;

        SECTION("procedure p; Select p") {
            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("procedure k; Select k") {
            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "k", "");

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }
}