#include "catch.hpp"
#include "pkb/tables/WhilePatternTable.h"

using namespace std;

TEST_CASE("PKB: WhilePatternTable") {
    SECTION("Test getStmtVarEntries") {
        WhilePatternTable table;

        unordered_set<string> entries1 = {"x", "y"};
        table.addWhilePattern(1, entries1);
        unordered_set<string> entries2 = {"y", "z"};
        table.addWhilePattern(2, entries2);

        unordered_map<int, unordered_set<string>> expectedEntries = {
                {1, {"x", "y"}},
                {2, {"y", "z"}}
        };
        REQUIRE(table.getStmtVarEntries() == expectedEntries);
    }

    SECTION("Test getVarsByStmt") {
        WhilePatternTable table;

        unordered_set<string> entries1 = {"x", "y"};
        table.addWhilePattern(1, entries1);
        unordered_set<string> entries2 = {"y", "z"};
        table.addWhilePattern(2, entries2);

        unordered_set<string> expectedVars = {"x", "y"};
        REQUIRE(table.getVarsByStmt(1) == expectedVars);
    }

    SECTION("Test getStmtsByVar") {
        WhilePatternTable table;

        unordered_set<string> entries1 = {"x", "y"};
        table.addWhilePattern(1, entries1);
        unordered_set<string> entries2 = {"y", "z"};
        table.addWhilePattern(2, entries2);

        unordered_set<int> expectedStmts = {1, 2};
        REQUIRE(table.getStmtsByVar("y") == expectedStmts);
    }

    SECTION("Test isValidPattern") {
        WhilePatternTable table;

        unordered_set<string> entries1 = {"x", "y"};
        table.addWhilePattern(1, entries1);
        unordered_set<string> entries2 = {"y", "z"};
        table.addWhilePattern(2, entries2);

        REQUIRE(table.isValidPattern(1, "x"));
        REQUIRE(table.isValidPattern(1, "y"));
        REQUIRE_FALSE(table.isValidPattern(1, "z"));
        REQUIRE(table.isValidPattern(2, "y"));
        REQUIRE(table.isValidPattern(2, "z"));
        REQUIRE_FALSE(table.isValidPattern(2, "x"));
        REQUIRE_FALSE(table.isValidPattern(3, "x"));
    }

    SECTION("Test hasValidPattern") {
        WhilePatternTable table;

        REQUIRE_FALSE(table.hasValidPattern());

        unordered_set<string> entries = {"x", "y"};
        table.addWhilePattern(1, entries);

        REQUIRE(table.hasValidPattern());

        REQUIRE(table.hasValidPattern(1));
        REQUIRE_FALSE(table.hasValidPattern(2));

        REQUIRE(table.hasValidPattern("x"));
        REQUIRE(table.hasValidPattern("y"));
        REQUIRE_FALSE(table.hasValidPattern("z"));
    }

    SECTION("Test addWhilePattern") {
        WhilePatternTable table;

        unordered_set<string> entries1 = {"x", "y"};
        table.addWhilePattern(1, entries1);
        unordered_set<string> entries2 = {"y", "z"};
        table.addWhilePattern(2, entries2);

        unordered_map<int, unordered_set<string>> expectedEntries = {
                {1, {"x", "y"}},
                {2, {"y", "z"}}
        };
        REQUIRE(table.getStmtVarEntries() == expectedEntries);

        // Test adding duplicate does not affect the table
        table.addWhilePattern(1, entries1);
        REQUIRE(table.getStmtVarEntries() == expectedEntries);

        // Test adding existing statement number but new variable name updates the table correctly
        entries1.insert("z");
        table.addWhilePattern(1, entries1);

        unordered_map<int, unordered_set<string>> expectedEntries2 = {
                {1, {"x", "y", "z"}},
                {2, {"y", "z"}}
        };
        REQUIRE(table.getStmtVarEntries() == expectedEntries2);

        // Test adding new statement number and new variable names updates the table correctly
        unordered_set<string> entries3 = {"x", "w"};
        table.addWhilePattern(3, entries3);

        unordered_map<int, unordered_set<string>> expectedEntries3 = {
                {1, {"x", "y", "z"}},
                {2, {"y", "z"}},
                {3, {"x", "w"}}
        };
        REQUIRE(table.getStmtVarEntries() == expectedEntries3);

        // Test that adding a pattern with new statement number and existing variable names updates the table correctly
        table.addWhilePattern(4, entries1);

        unordered_map<int, unordered_set<string>> expectedEntries4 = {
                {1, {"x", "y", "z"}},
                {2, {"y", "z"}},
                {3, {"x", "w"}},
                {4, {"x", "y", "z"}}
        };
        REQUIRE(table.getStmtVarEntries() == expectedEntries4);
    }
}