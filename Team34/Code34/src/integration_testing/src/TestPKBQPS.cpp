#include "catch.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

#include "sp/SourceProcessor.h"
#include "qps/QPS.h"
#include "pkb/PKB.h"
#include "di/DI.h"

inline void TEST_SOURCE_QUERY(std::string query, std::list<std::string>& expectedResult) {
    DI di;
    PKB pkb(di);
    di.getService<ICallsAdder>().addCalls("p1", "p2");
    di.getService<ICallsAdder>().addCalls("p2", "p3");
    di.getService<ICallsAdder>().addCallsT("p1", "p3");
    di.getService<IStmtAdder>().addReadStmt(1, "x");
    di.getService<IStmtAdder>().addAssignStmt(2);
    di.getService<IUsesAdder>().addVarS(3, "x");
    di.getService<IStmtAdder>().addPrintStmt(3, "x");
    di.getService<IStmtAdder>().addIfStmt(4);
    di.getService<IIfPatternAdder>().addIfPattern(4, std::unordered_set<std::string>({"p1","z"}));
    di.getService<IStmtAdder>().addWhileStmt(5);
    di.getService<IModifiesAdder>().addVarP("p1", "p1");
    di.getService<IFollowsAdder>().addRelation(2, 3);
    di.getService<IFollowsAdder>().addRelationT(1, 4);
    di.getService<IWhilePatternAdder>().addWhilePattern(5, std::unordered_set<std::string>({"x", "y"}));
    di.getService<IVarAdder>().addVars(std::unordered_set<std::string>({"x", "p1", "y", "z"}));
    di.getService<IAssignPatternAdder>().addAssignPattern(2, "x", ASTUtil::convertToAST("y + 3 * z"));
    di.getService<IProcAdder>().addProcs(std::unordered_set<std::string>({"p1", "p2", "p3"}));
    di.getService<IConstAdder>().addConsts(std::unordered_set<int>({1,2,3,4,5}));
    di.getService<INextAdder>().addNext(1, 3);
    di.getService<INextAdder>().addNext(3, 5);
    di.getService<IParentAdder>().addRelationT(2, 4);
    QPS qps;
    std::list<std::string> results = qps.process(query, di);
    REQUIRE(results == expectedResult);
}

TEST_CASE("Test Calls 1") {
    std::string query = "procedure p2, p1; Select p1 such that Calls(p1, p2) with p1.procName = \"p1\"";
    std::list<std::string> expectedResults = { "p1" };

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test Calls 2") {
    std::string query = "procedure p2, p1, p; Select p2 such that Calls*(p1, p2) and Calls(p, p2)";
    std::list<std::string> expectedResults = { "p3" };

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test Assign 1") {
    std::string query = "procedure p2, p1; assign a1; Select p1 pattern a1(\"x\", _\"3 * z\"_)";
    std::list<std::string> expectedResults = {"p1", "p2", "p3"};

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test Assign 2") {
    std::string query = "procedure p2, p1; assign a1; Select BOOLEAN pattern a1(\"x\", _\"y + 3\"_)";
    std::list<std::string> expectedResults = { "FALSE" };

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test with 1") {
    std::string query = "constant c1, c2; stmt s; Select <s, c1.value> with s.stmt# = c1.value "
                        "and c1.value = c2.value and c2.value = 3";
    std::list<std::string> expectedResults = { "3 3" };

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test Uses with 1") {
    std::string query = "constant c1, c2; stmt s; variable v; Select s such that Uses(s, v) with s.stmt# = c1.value";
    std::list<std::string> expectedResults = { "3" };

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test multi 1") {
    std::string query = "constant c1; stmt s; procedure p; variable v; Select <s, p, c1> such that Uses(s, v)"
                        " and Calls(p, \"p2\") with s.stmt# = c1.value and v.varName = \"x\"";
    std::list<std::string> expectedResults = { "3 p1 3" };

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test Next 1") {
    std::string query = "constant c; stmt s1, s2, s3; Select <s1, s2, s3, c> such that Next*(s1, s3) and Next(s1, s2)"
    "and Next(s2, s3) with s1.stmt# = c.value with s1.stmt# = c.value and s2.stmt# = 3 and s3.stmt# = 5 and c.value = 1";
    std::list<std::string> expectedResults = { "1 3 5 1" };

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test same proc var name") {
    std::string query = "procedure p; variable v; Select <p, v> such that Modifies(p, v) with p.procName = v.varName";
    std::list<std::string> expectedResults = { "p1 p1" };

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test multi 3") {
    std::string query = "if ifs; variable v; procedure p; Select <ifs.stmt#, v> pattern ifs(v, _, _)";
    std::list<std::string> expectedResults = { "4 p1", "4 z" };

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test follows 3") {
    std::string query = "assign a; print p; read r; if ifs; Select <r, a, p, ifs> such that Follows(a, p) and Follows*(r, ifs)";
    std::list<std::string> expectedResults = { "1 2 3 4" };

    TEST_SOURCE_QUERY(query, expectedResults);
}

TEST_CASE("Test parent with random constants 3") {
    std::string query = "stmt s; constant c; Select <s, c> such that Parent*(s, 4)";
    std::list<std::string> expectedResults = { "2 1", "2 2", "2 3", "2 4", "2 5" };

    TEST_SOURCE_QUERY(query, expectedResults);
}
