#include "catch.hpp"
#include "pkb/tables/FollowsTable.h"



TEST_CASE("PKB: FollowsTable") {
    SECTION("Test getFollowsEntries") {
        FollowsTable followsTable;
        followsTable.addRelation(1, 2);
        followsTable.addRelation(2, 3);
        followsTable.addRelation(2, 4);
        followsTable.addRelation(5, 6);
        followsTable.addRelation(7, 8);

        auto expected = std::unordered_map<int, int>{
                {1, 2},
                {2, 3},
                {2, 4},
                {5, 6},
                {7, 8}
        };
        REQUIRE(followsTable.getFollowsEntries() == expected);
    }

    SECTION("Test getStmtAfter") {
        FollowsTable followsTable;
        followsTable.addRelation(1, 2);
        followsTable.addRelation(2, 3);

        REQUIRE(followsTable.getStmtAfter(1) == 2);
        REQUIRE(followsTable.getStmtAfter(2) == 3);
        REQUIRE(followsTable.getStmtAfter(3) == 0);
    }

    SECTION("Test getStmtBefore") {
        FollowsTable followsTable;
        followsTable.addRelation(1, 2);
        followsTable.addRelation(2, 3);

        REQUIRE(followsTable.getStmtBefore(3) == 2);
        REQUIRE(followsTable.getStmtBefore(2) == 1);
        REQUIRE(followsTable.getStmtBefore(1) == 0);
    }

    SECTION("Test isAssociated") {
        FollowsTable followsTable;
        followsTable.addRelation(1, 2);
        followsTable.addRelation(2, 3);
        followsTable.addRelation(4, 5);

        REQUIRE(followsTable.isAssociated(1, 2));
        REQUIRE(followsTable.isAssociated(2, 3));
        REQUIRE(followsTable.isAssociated(4, 5));
        REQUIRE_FALSE(followsTable.isAssociated(2, 1));
        REQUIRE_FALSE(followsTable.isAssociated(3, 2));
        REQUIRE_FALSE(followsTable.isAssociated(1, 3));
        REQUIRE_FALSE(followsTable.isAssociated(1, 5));
        REQUIRE_FALSE(followsTable.isAssociated(1, 1));
        REQUIRE_FALSE(followsTable.isAssociated(7, 9));
    }

    SECTION("Test hasAssociated") {
        FollowsTable followsTable;
        REQUIRE_FALSE(followsTable.hasAssociated());

        followsTable.addRelation(1, 2);
        REQUIRE(followsTable.hasAssociated());
    }

    SECTION("Test hasAssociatedByKey") {
        FollowsTable followsTable;
        REQUIRE_FALSE(followsTable.hasAssociatedByKey(1));

        followsTable.addRelation(1, 2);
        REQUIRE(followsTable.hasAssociatedByKey(1));
        REQUIRE_FALSE(followsTable.hasAssociatedByKey(2));
    }

    SECTION("Test hasAssociatedByValue") {
        FollowsTable followsTable;
        REQUIRE_FALSE(followsTable.hasAssociatedByValue(2));

        followsTable.addRelation(1, 2);
        REQUIRE(followsTable.hasAssociatedByValue(2));
        REQUIRE_FALSE(followsTable.hasAssociatedByValue(1));
    }

    SECTION("Test getTEntries") {
        FollowsTable followsTable;
        followsTable.addRelationT(1, 2);
        followsTable.addRelationT(2, 3);
        followsTable.addRelationT(1, 3);
        followsTable.addRelationT(2, 4);
        followsTable.addRelationT(1, 4);
        followsTable.addRelationT(5, 6);
        followsTable.addRelationT(7, 8);

        auto expected = std::unordered_map<int, std::unordered_set<int>>{
                {1, {2, 3, 4}},
                {2, {3, 4}},
                {5, {6}},
                {7, {8}}
        };
        REQUIRE(followsTable.getTEntries() == expected);
    }

    SECTION("Test getTStmtsByKey") {
        FollowsTable followsTable;
        followsTable.addRelationT(1, 2);
        followsTable.addRelationT(2, 3);
        followsTable.addRelationT(1, 3);

        std::unordered_set<int> expected = {2, 3};
        REQUIRE(followsTable.getTStmtsByKey(1) == expected);

        expected = {3};
        REQUIRE(followsTable.getTStmtsByKey(2) == expected);

        expected = {};
        REQUIRE(followsTable.getTStmtsByKey(3) == expected);
    }

    SECTION("Test getTStmtsByValue") {
        FollowsTable followsTable;
        followsTable.addRelationT(1, 2);
        followsTable.addRelationT(2, 3);
        followsTable.addRelationT(1, 3);

        std::unordered_set<int> expected = {};
        REQUIRE(followsTable.getTStmtsByValue(1) == expected);

        expected = {1};
        REQUIRE(followsTable.getTStmtsByValue(2) == expected);

        expected = {1, 2};
        REQUIRE(followsTable.getTStmtsByValue(3) == expected);
    }

    SECTION("Test hasAssociatedT") {
        FollowsTable followsTable;
        followsTable.addRelationT(1, 2);

        REQUIRE(followsTable.hasAssociatedT());

        followsTable.addRelationT(2, 3);
        followsTable.addRelationT(3, 4);
        followsTable.addRelationT(4, 5);

        REQUIRE(followsTable.hasAssociatedT());

        followsTable.addRelationT(6, 7);

        REQUIRE(followsTable.hasAssociatedT());

        followsTable = FollowsTable();

        REQUIRE_FALSE(followsTable.hasAssociatedT());
    }

    SECTION("Test hasAssociatedTByKey") {
        FollowsTable followsTable;
        followsTable.addRelationT(1, 2);
        followsTable.addRelationT(2, 3);
        followsTable.addRelationT(1, 3);

        REQUIRE(followsTable.hasAssociatedTByKey(1));
        REQUIRE(followsTable.hasAssociatedTByKey(2));
        REQUIRE_FALSE(followsTable.hasAssociatedTByKey(3));
    }

    SECTION("Test hasAssociatedTByValue") {
        FollowsTable followsTable;
        followsTable.addRelationT(1, 2);
        followsTable.addRelationT(2, 3);
        followsTable.addRelationT(1, 3);
        followsTable.addRelationT(3, 4);
        followsTable.addRelationT(1, 4);
        followsTable.addRelationT(2, 4);

        REQUIRE(followsTable.hasAssociatedTByValue(2));
        REQUIRE(followsTable.hasAssociatedTByValue(3));
        REQUIRE(followsTable.hasAssociatedTByValue(4));
        REQUIRE_FALSE(followsTable.hasAssociatedTByValue(1));
    }

    SECTION("Test isAssociatedT") {
        FollowsTable followsTable;
        followsTable.addRelationT(1, 2);
        followsTable.addRelationT(2, 3);
        followsTable.addRelationT(1, 3);
        followsTable.addRelationT(3, 4);
        followsTable.addRelationT(1, 4);
        followsTable.addRelationT(2, 4);
        followsTable.addRelationT(4, 5);
        followsTable.addRelationT(1, 5);
        followsTable.addRelationT(2, 5);
        followsTable.addRelationT(3, 5);

        REQUIRE(followsTable.isAssociatedT(1, 2));
        REQUIRE(followsTable.isAssociatedT(1, 3));
        REQUIRE(followsTable.isAssociatedT(1, 5));
        REQUIRE(followsTable.isAssociatedT(2, 4));
        REQUIRE(followsTable.isAssociatedT(1, 5));
        REQUIRE_FALSE(followsTable.isAssociatedT(2, 1));
        REQUIRE_FALSE(followsTable.isAssociatedT(3, 2));
        REQUIRE_FALSE(followsTable.isAssociatedT(1, 1));
        REQUIRE_FALSE(followsTable.isAssociatedT(9, 7));
    }

    SECTION("Test addRelationT") {
        FollowsTable followsTable;

        followsTable.addRelationT(1, 2);
        std::unordered_set<int> expectedValues = {2};
        std::unordered_set<int> actualValues = followsTable.getTStmtsByKey(1);
        REQUIRE(actualValues == expectedValues);

        followsTable.addRelationT(2, 3);
        expectedValues = {3};
        actualValues = followsTable.getTStmtsByKey(2);
        REQUIRE(actualValues == expectedValues);

        followsTable.addRelationT(1, 3);
        expectedValues = {2, 3};
        actualValues = followsTable.getTStmtsByKey(1);
        REQUIRE(actualValues == expectedValues);
    }
}
