#include "catch.hpp"
#include "pkb/tables/VarTable.h"

TEST_CASE("PKB: VarTable") {
    SECTION("Test empty VarTable") {
        VarTable varTable;
        REQUIRE(varTable.getSize() == 0);
        REQUIRE(varTable.getVars().empty());
    }

    SECTION("Test addVar") {
        VarTable varTable;
        varTable.addVar("x");
        REQUIRE(varTable.getSize() == 1);
        REQUIRE(varTable.isVar("x"));
        REQUIRE_FALSE(varTable.isVar("y"));
    }

    SECTION("Test addVar duplicates") {
        VarTable varTable;
        varTable.addVar("x");
        varTable.addVar("x");
        REQUIRE(varTable.getSize() == 1);
    }

    SECTION("Test addVar multiple vars and getVars") {
        VarTable varTable;
        varTable.addVar("x");
        varTable.addVar("y");
        varTable.addVar("z");

        std::unordered_set<std::string> expectedVars = {"x", "y", "z"};
        std::unordered_set<std::string> actualVars = varTable.getVars();

        REQUIRE(actualVars == expectedVars);
        REQUIRE(varTable.getSize() == 3);
        REQUIRE(varTable.isVar("x"));
        REQUIRE(varTable.isVar("y"));
        REQUIRE(varTable.isVar("z"));
        REQUIRE_FALSE(varTable.isVar("k"));
    }
}