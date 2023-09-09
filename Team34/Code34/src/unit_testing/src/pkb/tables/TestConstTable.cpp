#include "catch.hpp"
#include "pkb/tables/ConstTable.h"



TEST_CASE("PKB: ConstTable") {
    SECTION("Test empty ConstTable") {
        ConstTable constTable;
        REQUIRE(constTable.getSize() == 0);
        REQUIRE(constTable.getConsts().empty());
    }

    SECTION("Test addConst") {
        ConstTable constTable;
        constTable.addConst(10);
        REQUIRE(constTable.getSize() == 1);
        REQUIRE(constTable.isConst(10));
        REQUIRE_FALSE(constTable.isConst(20));
    }

    SECTION("Test addConst duplicates") {
        ConstTable constTable;
        constTable.addConst(5);
        constTable.addConst(5);
        REQUIRE(constTable.getSize() == 1);
    }

    SECTION("Test addConst multiple consts and getConsts") {
        ConstTable constTable;
        constTable.addConst(10);
        constTable.addConst(20);
        constTable.addConst(30);

        std::unordered_set<int> expectedConsts = {10, 20, 30};
        std::unordered_set<int> actualConsts = constTable.getConsts();

        REQUIRE(actualConsts == expectedConsts);
        REQUIRE(constTable.getSize() == 3);
        REQUIRE(constTable.isConst(10));
        REQUIRE(constTable.isConst(20));
        REQUIRE(constTable.isConst(30));
        REQUIRE_FALSE(constTable.isConst(40));
    }
}