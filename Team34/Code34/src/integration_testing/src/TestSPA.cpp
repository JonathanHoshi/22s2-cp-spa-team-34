#include "catch.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

#include "FileReader.h"
#include "sp/SourceProcessor.h"
#include "qps/QPS.h"
#include "pkb/PKB.h"
#include "di/DI.h"

inline void TEST_SOURCE_QUERY(std::string filePath, std::string query, std::list<std::string>& expectedResult) {
    DI di;
    PKB pkb(di);
    SPParserManager parserManager;
    Tokenizer tokenizer;

    std::string fileContents = FileReader::readFile(filePath);
    SourceProcessor sp;
    sp.parse(fileContents, di);

    QPS qps;
    std::list<std::string> results = qps.process(query, di);

    REQUIRE(results == expectedResult);
}

TEST_CASE("Multiclause aspa source") {
    SECTION("Select Single: Call Stmt w Attribute") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        filePath /= "integration_testing/tests/Multiclause_aspa_source.txt";

        std::string query = "call cl; procedure p, p1; Select cl.procName such that Calls(p, p1) with p.procName = cl.procName";
        std::list<std::string> expectedResults = { "find" };

        TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
    }
}

TEST_CASE("With source") {
    SECTION("Select Single: Call Stmt w Attribute") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        filePath /= "integration_testing/tests/With_spa_source.txt";

        std::string query = "call cl; procedure p; variable v; Select cl with cl.procName = v.varName and v.varName = cl.procName";
        std::list<std::string> expectedResults = { "2" };

        TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
    }
}


TEST_CASE("Select source") {
    SECTION("Select Single: Call Stmt w Attribute") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        filePath /= "integration_testing/tests/Select_spa_source.txt";

        std::string query = "call c;	Select c.procName";
        std::list<std::string> expectedResults = { "p4" };

        TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
    }
}

TEST_CASE("Follows source") {
    SECTION("Single pattern - Same Synonym") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        filePath /= "integration_testing/tests/Follows_spa_source.txt";

        std::string query = "stmt s; Select s such that Follows(s, s)";
        std::list<std::string> expectedResults;

        TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
    }
}

TEST_CASE("Calls source") {
    SECTION("Single pattern - Left Wildcard Right Synonym") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        filePath /= "integration_testing/tests/Calls_spa_source.txt";

        std::string query = "procedure p; Select p such that Calls(_, p)";
        std::list<std::string> expectedResults = { "p2", "p3", "p4", "p5", "p6" };

        TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
    }

    SECTION("Single pattern - 2 Synonym") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        filePath /= "integration_testing/tests/Calls_spa_source.txt";

        std::string query = "procedure p, p1; Select p such that Calls(p, p1)";
        std::list<std::string> expectedResults = { "p1", "p2", "p3" };

        TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
    }
}

TEST_CASE("Assign source") {
    SECTION("Single pattern - Synonym - Full Match") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        filePath /= "integration_testing/tests/Assign_spa_source.txt";

        std::string query = "assign a; variable v; Select a pattern a (v, \"ryan\")";
        std::list<std::string> expectedResults = { "10", "11" };

        TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
    }

    SECTION("Single pattern - IDENT - Partial Match") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        filePath /= "integration_testing/tests/Assign_spa_source.txt";

        std::string query = "assign a; Select a pattern a(\"nat\", _\"nat + 1\"_)";
        std::list<std::string> expectedResults = { "14", "5" };

        TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
    }

    SECTION("MultiClause") {
        SECTION("Single Pattern Single Relation") {
            SECTION("pattern a(_,_) such that Modifies(a,v2)") {
                std::filesystem::path filePath = std::filesystem::current_path().parent_path();
                filePath /= "integration_testing/tests/Assign_spa_source.txt";

                std::string query = "variable v1, v2; assign a; Select v1 pattern a(_, _) such that Modifies(a, v2)";
                std::list<std::string> expectedResults = { "cx", "fred", "jon", "nat", "outong", "ryan" };

                TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
            }

            SECTION("pattern a(v, _\"nat\"_) such that Parent(_, a)") {
                std::filesystem::path filePath = std::filesystem::current_path().parent_path();
                filePath /= "integration_testing/tests/Assign_spa_source.txt";

                std::string query = "assign a, a1; variable v; Select a pattern a(v, _\"nat\"_) such that Parent(_, a)";
                std::list<std::string> expectedResults = { "13", "5", "8" };

                TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
            }

            SECTION("pattern a(v1, _) such that Uses(a, v) ") {
                std::filesystem::path filePath = std::filesystem::current_path().parent_path();
                filePath /= "integration_testing/tests/Assign_spa_source.txt";

                std::string query = "assign a; variable v, v1; Select a pattern a(v1, _) such that Uses(a, v)";
                std::list<std::string> expectedResults = { "10", "11", "13", "14", "15", "5", "8" };

                TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
            }

            SECTION("pattern a(v, _) such that Uses(a, v) ") {
                std::filesystem::path filePath = std::filesystem::current_path().parent_path();
                filePath /= "integration_testing/tests/Assign_spa_source.txt";

                std::string query = "assign a; variable v; Select a pattern a(v, _) such that Uses(a, v)";
                std::list<std::string> expectedResults = { "14", "5" };

                TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
            }
        }
    }
}

TEST_CASE("Next Source") {
    SECTION("Next* search") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        filePath /= "integration_testing/tests/Next_spa_source.txt";
        std::string query = "stmt s; Select s such that Next* (s, 12)";
        std::list<std::string> expectedResults = { "1", "10", "11", "12", "13", "2", "3", "4", "5", "6", "7", "8", "9" };

        TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
    };
    SECTION("Next search") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        filePath /= "integration_testing/tests/Next_spa_source.txt";
        std::string query = "stmt s; Select s such that Next (s, 12)";
        std::list<std::string> expectedResults = { "11", "13" };

        TEST_SOURCE_QUERY(filePath.string(), query, expectedResults);
    }
}
