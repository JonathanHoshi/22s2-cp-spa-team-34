#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "catch.hpp"
#include "common/ConversionUtils.h"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "../stub_entity/StubConstProcVarGetter.cpp"
#include "../stub_entity/StubStmtGetter.cpp"
#include "../stub_entity/StubClearer.cpp"
#include "../TestQPS.cpp"

namespace test_entity_eval {
    std::shared_ptr<StubStmtGetter> stmtInterface;
    std::shared_ptr<StubConstProcVarGetter> constProcVarInterface;
    std::shared_ptr<StubClearer> stubClearer;
    DI di;

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
        stmtInterface = std::make_shared<StubStmtGetter>();
        constProcVarInterface = std::make_shared<StubConstProcVarGetter>();
        stubClearer = std::make_shared<StubClearer>();

        constProcVarInterface->setVarEntries(varSet);
        constProcVarInterface->setProcEntries(procSet);
        constProcVarInterface->setConstEntries(constSet);
        stmtInterface->setReadStmtEntries(readMap);
        stmtInterface->setPrintStmtEntries(printMap);
        stmtInterface->setCallStmtEntries(callStmtMap);
        stmtInterface->setIfStmtEntries(ifStmtSet);
        stmtInterface->setWhileStmtEntries(whileStmtSet);
        stmtInterface->setAssignStmtEntries(assignStmtSet);
    }

    DI* getDI() {
        di.registerService<IAffectsClearer>(stubClearer);
        di.registerService<INextTClearer>(stubClearer);
        di.registerService<IStmtGetter>(stmtInterface);
        di.registerService<IConstGetter>(constProcVarInterface);
        di.registerService<IProcGetter>(constProcVarInterface);
        di.registerService<IVarGetter>(constProcVarInterface);

        return &di;
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
    DI* di = getDI();

    SECTION("Variable Select All") {
        std::unordered_set<std::string> expectedResult = varSet;
        std::vector<std::shared_ptr<Clause>> clauseList;

        SECTION("variable v; Select v") {
            std::string query = "variable v; Select v";

            TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
        }

        SECTION("variable k; Select k") {
            std::string query = "variable k; Select k";

            TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
        }
    }

    SECTION("Assign Select All") {
        std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(assignStmtSet);
        std::vector<std::shared_ptr<Clause>> clauseList;

        SECTION("assign a; Select a") {
            std::string query = "assign a; Select a";

            TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
        }

        SECTION("assign b; Select b") {
            std::string query = "assign b; Select b";

            TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
        }
    }

    SECTION("Procedure Select All") {
        std::unordered_set<std::string> expectedResult = procSet;
        std::vector<std::shared_ptr<Clause>> clauseList;

        SECTION("procedure p; Select p") {
            std::string query = "procedure p; Select p";

            TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
        }

        SECTION("procedure k; Select k") {
            std::string query = "procedure k; Select k";

            TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
        }
    }
}

TEST_CASE("Tuple Select All") {
    initializeInterfaces();
    DI* di = getDI();

    SECTION("Select <Assign, Proc>") {
        std::unordered_set<std::string> expectedResult = { "3 cx",
                                                           "3 fred",
                                                           "3 jon",
                                                           "3 nat",
                                                           "3 ryan",
                                                           "6 cx",
                                                           "6 fred",
                                                           "6 jon",
                                                           "6 nat",
                                                           "6 ryan",
                                                           "8 cx",
                                                           "8 fred",
                                                           "8 jon",
                                                           "8 nat",
                                                           "8 ryan",
                                                           "12 cx",
                                                           "12 fred",
                                                           "12 jon",
                                                           "12 nat",
                                                           "12 ryan" };

        std::string query = "assign a; procedure p; Select <a, p>";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Select <Const, Assign, While>") {
        std::unordered_set<std::string> expectedResult = { "1 3 14",
                                                           "1 6 14",
                                                           "1 8 14",
                                                           "1 12 14",
                                                           "2 3 14",
                                                           "2 6 14",
                                                           "2 8 14",
                                                           "2 12 14",
                                                           "7 3 14",
                                                           "7 6 14",
                                                           "7 8 14",
                                                           "7 12 14" };

        std::string query = "constant c; assign a; while w; Select <c, a, w>";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }
}

TEST_CASE("Tuple Select w Attributes") {
    initializeInterfaces();
    DI* di = getDI();

    SECTION("Select <Read.stmt#, Print.stmt#>") {
        std::unordered_set<std::string> expectedResult = { "2 5",
                                                           "2 11",
                                                           "2 15",
                                                           "7 5",
                                                           "7 11",
                                                           "7 15",
                                                           "9 5",
                                                           "9 11",
                                                           "9 15" };

        std::string query = "read r; print p; Select <r.stmt#, p.stmt#>";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Select <Read.varName, Print.varName>") {
        std::unordered_set<std::string> expectedResult = { "sp sp",
                                                           "sp pkb",
                                                           "sp qps",
                                                           "qps sp",
                                                           "qps pkb",
                                                           "qps qps",
                                                           "pkb sp",
                                                           "pkb pkb",
                                                           "pkb qps" };

        std::string query = "read r; print p; Select <r.varName, p.varName>";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Select <Read.stmt#, Read.varName>") {
        std::unordered_set<std::string> expectedResult = { "2 sp",
                                                           "7 qps",
                                                           "9 pkb" };

        std::string query = "read r; print p; Select <r.stmt#, r.varName>";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }
}

TEST_CASE("BOOLEAN Select") {
    initializeInterfaces();
    DI* di = getDI();

    SECTION("Select BOOLEAN") {
        std::unordered_set<std::string> expectedResult = { "TRUE" };

        std::string query = "read r; print p; Select BOOLEAN";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Select BOOLEAN with 0 = 1") {
        std::unordered_set<std::string> expectedResult = { "FALSE" };

        std::string query = "read r; print p; Select BOOLEAN with 0 = 1";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }
}

TEST_CASE("Single Select w With Clause") {
    initializeInterfaces();
    DI* di = getDI();

    SECTION("Select Var with Read.varName = Var.varName") {
        std::unordered_set<std::string> expectedResult = { "sp", "pkb", "qps" };

        std::string query = "read r; variable v; Select v with r.varName = v.varName";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Select Stmt with Assign.stmt# = Stmt.stmt#") {
        std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(assignStmtSet);

        std::string query = "assign a; stmt s; Select s with s.stmt# = a.stmt#";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }
}

TEST_CASE("TUPLE Select w With Clause") {
    initializeInterfaces();
    DI* di = getDI();

    SECTION("Select <Read.stmt#, Print.stmt#> with Read.stmt# = Print.stmt#") {
        std::unordered_set<std::string> expectedResult;

        std::string query = "read r; print p; Select <r.stmt#, p.stmt#> with r.stmt# = p.stmt#";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Select <Read.stmt#, Print.stmt#> with Read.varName = Print.varName" ) {
        std::unordered_set<std::string> expectedResult = { "2 5",
                                                           "7 15",
                                                           "9 11" };

        std::string query = "read r; print p; Select <r.stmt#, p.stmt#> with r.varName = p.varName";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Select <Read.varName, Print.varName> with Read.varName = Print.varName") {
        std::unordered_set<std::string> expectedResult = { "sp sp",
                                                           "pkb pkb",
                                                           "qps qps" };

        std::string query = "read r; print p; Select <r.varName, p.varName> with r.varName = p.varName";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }
}

TEST_CASE("SyntaxError") {
    initializeInterfaces();
    DI* di = getDI();
    std::unordered_set<std::string> expectedResult = { "SyntaxError" };

    SECTION("Invalid Declaration Name") {
        std::string query = "const c; Select c";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Invalid Command Name") {
        std::string query = "read r; print p; Select r such that Follow(r, p)";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Invalid ending semi-colon") {
        std::string query = "read r; Select r;";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Invalid Digits - With clause") {
        std::string query = "read r; assign a; Select r with 1 = 01)";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Invalid Digits - Assign pattern") {
        std::string query = "read r; assign a; Select r pattern a(_, \"09\")";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }
}

TEST_CASE("SemanticError") {
    initializeInterfaces();
    DI* di = getDI();
    std::unordered_set<std::string> expectedResult = { "SemanticError" };

    SECTION("Undeclared synoynm") {
        std::string query = "constant c; Select a";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Different with comparison type") {
        std::string query = "read r; print p; assign a; Select r with 1 = \"a\"";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Invalid argument - Relation Clause Argument") {
        std::string query = "read r; procedure p; Select r such that Calls(r, p)";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }

    SECTION("Invalid argument - Pattern Clause Argument") {
        std::string query = "assign a; Select a pattern a(_, _, _)";

        TEST_SINGLESELECT_QUERY(*di, query, expectedResult);
    }
}
