#include "catch.hpp"
#include "pkb/tables/ParentTable.h"



TEST_CASE("PKB: ParentTable") {
    SECTION("Test getParentEntries") {
        ParentTable parentTable;
        parentTable.addRelation(1, 2);
        parentTable.addRelation(1, 3);
        parentTable.addRelation(2, 4);
        parentTable.addRelation(2, 5);

        auto expected = std::unordered_map<int, std::unordered_set<int>>{
                {1, {2, 3}},
                {2, {4, 5}}
        };
        REQUIRE(parentTable.getParentEntries() == expected);
    }

    SECTION("Test getParents") {
        ParentTable parentTable;
        parentTable.addRelation(1, 2);
        parentTable.addRelation(1, 3);
        parentTable.addRelation(2, 4);
        parentTable.addRelation(2, 5);
        parentTable.addRelation(4, 6);

        std::unordered_set<int> parents = parentTable.getParents();

        REQUIRE(parents.size() == 3);
        REQUIRE(parents.count(1));
        REQUIRE(parents.count(2));
        REQUIRE(parents.count(3) == 0);

        std::unordered_set<int> expectedParents{1, 2, 4};
        REQUIRE(parentTable.getParents() == expectedParents);
    }

    SECTION("Test getChildren") {
        ParentTable parentTable;
        parentTable.addRelation(1, 2);
        parentTable.addRelation(1, 3);
        parentTable.addRelation(2, 4);
        parentTable.addRelation(2, 5);
        parentTable.addRelation(4, 6);

        std::unordered_set<int> children = parentTable.getChildren();

        REQUIRE(children.size() == 5);
        REQUIRE(children.count(2));
        REQUIRE(children.count(3));
        REQUIRE(children.count(4));

        std::unordered_set<int> expectedChildren{2, 3, 4, 5, 6};
        REQUIRE(parentTable.getChildren() == expectedChildren);
    }

    SECTION("Test getChildrenOf") {
        ParentTable parentTable;
        parentTable.addRelation(1, 2);
        parentTable.addRelation(1, 3);
        parentTable.addRelation(2, 4);
        parentTable.addRelation(2, 5);
        parentTable.addRelation(4, 6);

        std::unordered_set<int> childrenOf1 = parentTable.getChildrenOf(1);
        REQUIRE(childrenOf1.size() == 2);
        REQUIRE(childrenOf1.count(2));
        REQUIRE(childrenOf1.count(3));

        std::unordered_set<int> childrenOf2 = parentTable.getChildrenOf(2);
        REQUIRE(childrenOf2.size() == 2);
        REQUIRE(childrenOf2.count(4));
        REQUIRE(childrenOf2.count(5));

        std::unordered_set<int> childrenOf3 = parentTable.getChildrenOf(3);
        REQUIRE(childrenOf3.empty());

        std::unordered_set<int> expectedChildrenOf2{4, 5};
        REQUIRE(parentTable.getChildrenOf(2) == expectedChildrenOf2);
    }

    SECTION("Test getParentOf") {
        ParentTable parentTable;
        parentTable.addRelation(1, 2);
        parentTable.addRelation(1, 3);
        parentTable.addRelation(2, 4);
        parentTable.addRelation(2, 5);

        REQUIRE(parentTable.getParentOf(2) == 1);
        REQUIRE(parentTable.getParentOf(3) == 1);
        REQUIRE(parentTable.getParentOf(4) == 2);
        REQUIRE(parentTable.getParentOf(5) == 2);
        REQUIRE(parentTable.getParentOf(1) == 0);
    }

    SECTION("Test isAssociated") {
        ParentTable parentTable;
        parentTable.addRelation(1, 2);
        parentTable.addRelation(1, 3);
        parentTable.addRelation(2, 4);
        parentTable.addRelation(2, 5);
        parentTable.addRelation(4, 6);

        REQUIRE(parentTable.isAssociated(1, 2));
        REQUIRE(parentTable.isAssociated(1, 3));
        REQUIRE(parentTable.isAssociated(2, 4));
        REQUIRE(parentTable.isAssociated(2, 5));
        REQUIRE(parentTable.isAssociated(4, 6));

        REQUIRE_FALSE(parentTable.isAssociated(1, 4));
        REQUIRE_FALSE(parentTable.isAssociated(2, 1));
        REQUIRE_FALSE(parentTable.isAssociated(4, 1));
        REQUIRE_FALSE(parentTable.isAssociated(1, 1));
        REQUIRE_FALSE(parentTable.isAssociated(7, 9));
    }

    SECTION("Test hasAssociated") {
        ParentTable parentTable;
        REQUIRE_FALSE(parentTable.hasAssociated());

        parentTable.addRelation(1, 2);
        REQUIRE(parentTable.hasAssociated());

        parentTable.addRelation(3, 4);
        REQUIRE(parentTable.hasAssociated());
    }

    SECTION("Test hasAssociatedByKey") {
        ParentTable parentTable;
        REQUIRE_FALSE(parentTable.hasAssociatedByKey(1));

        parentTable.addRelation(1, 2);
        REQUIRE(parentTable.hasAssociatedByKey(1));
        REQUIRE_FALSE(parentTable.hasAssociatedByKey(2));

        parentTable.addRelation(3, 4);
        REQUIRE(parentTable.hasAssociatedByKey(3));
        REQUIRE_FALSE(parentTable.hasAssociatedByKey(4));
        REQUIRE_FALSE(parentTable.hasAssociatedByKey(8));
        REQUIRE_FALSE(parentTable.hasAssociatedByKey(0));
    }

    SECTION("Test hasAssociatedByValue") {
        ParentTable parentTable;
        REQUIRE_FALSE(parentTable.hasAssociatedByValue(2));

        parentTable.addRelation(1, 2);
        REQUIRE(parentTable.hasAssociatedByValue(2));
        REQUIRE_FALSE(parentTable.hasAssociatedByValue(1));

        parentTable.addRelation(3, 4);
        REQUIRE(parentTable.hasAssociatedByValue(4));
        REQUIRE_FALSE(parentTable.hasAssociatedByValue(3));
        REQUIRE_FALSE(parentTable.hasAssociatedByValue(8));
        REQUIRE_FALSE(parentTable.hasAssociatedByValue(0));
    }

    SECTION("Test getTEntries") {
        ParentTable parentTable;
        parentTable.addRelationT(1, 2);
        parentTable.addRelationT(1, 3);
        parentTable.addRelationT(2, 4);
        parentTable.addRelationT(1, 4);
        parentTable.addRelationT(3, 5);
        parentTable.addRelationT(1, 5);
        parentTable.addRelationT(3, 6);
        parentTable.addRelationT(1, 6);

        auto expected = std::unordered_map<int, std::unordered_set<int>>{
                {1, {2, 3, 4, 5, 6}},
                {2, {4}},
                {3, {5, 6}}
        };
        REQUIRE(parentTable.getTEntries() == expected);
    }

    SECTION("Test getTStmtsByKey") {
        ParentTable parentTable;
        parentTable.addRelationT(1, 2);
        parentTable.addRelationT(1, 3);
        parentTable.addRelationT(2, 4);
        parentTable.addRelationT(1, 4);
        parentTable.addRelationT(3, 5);
        parentTable.addRelationT(1, 5);
        parentTable.addRelationT(3, 6);
        parentTable.addRelationT(1, 6);

        std::unordered_set<int> expected = {};
        REQUIRE(parentTable.getTStmtsByKey(6) == expected);

        expected = {5, 6};
        REQUIRE(parentTable.getTStmtsByKey(3) == expected);

        expected = {2, 3, 4, 5, 6};
        REQUIRE(parentTable.getTStmtsByKey(1) == expected);

        expected = {};
        REQUIRE(parentTable.getTStmtsByKey(8) == expected);
    }

    SECTION("Test getTStmtsByValue") {
        ParentTable parentTable;
        parentTable.addRelationT(1, 2);
        parentTable.addRelationT(1, 3);
        parentTable.addRelationT(2, 4);
        parentTable.addRelationT(1, 4);
        parentTable.addRelationT(3, 5);
        parentTable.addRelationT(1, 5);
        parentTable.addRelationT(3, 6);
        parentTable.addRelationT(1, 6);

        std::unordered_set<int> expected = {};
        REQUIRE(parentTable.getTStmtsByValue(1) == expected);

        expected = {1};
        REQUIRE(parentTable.getTStmtsByValue(2) == expected);

        expected = {1, 2};
        REQUIRE(parentTable.getTStmtsByValue(4) == expected);

        expected = {1, 3};
        REQUIRE(parentTable.getTStmtsByValue(6) == expected);

        expected = {};
        REQUIRE(parentTable.getTStmtsByValue(8) == expected);
    }

    SECTION("Test isAssociatedT") {
        ParentTable parentTable;
        parentTable.addRelationT(1, 2);
        parentTable.addRelationT(1, 3);
        parentTable.addRelationT(2, 4);
        parentTable.addRelationT(1, 4);
        parentTable.addRelationT(3, 5);
        parentTable.addRelationT(1, 5);
        parentTable.addRelationT(3, 6);
        parentTable.addRelationT(1, 6);

        REQUIRE(parentTable.isAssociatedT(1, 2));
        REQUIRE(parentTable.isAssociatedT(1, 6));
        REQUIRE_FALSE(parentTable.isAssociatedT(1, 7));
        REQUIRE_FALSE(parentTable.isAssociatedT(6, 1));
        REQUIRE_FALSE(parentTable.isAssociatedT(1, 1));
        REQUIRE_FALSE(parentTable.isAssociatedT(7, 9));
    }

    SECTION("Test hasAssociatedT") {
        ParentTable parentTable;
        REQUIRE_FALSE(parentTable.hasAssociatedT());

        parentTable.addRelationT(1, 2);
        REQUIRE(parentTable.hasAssociatedT());

        parentTable.addRelationT(3, 4);
        REQUIRE(parentTable.hasAssociatedT());
    }

    SECTION("Test hasAssociatedTByKey") {
        ParentTable parentTable;
        REQUIRE_FALSE(parentTable.hasAssociatedTByKey(1));

        parentTable.addRelationT(1, 2);
        REQUIRE(parentTable.hasAssociatedTByKey(1));
        REQUIRE_FALSE(parentTable.hasAssociatedTByKey(2));

        parentTable.addRelationT(2, 3);
        parentTable.addRelationT(1, 3);
        REQUIRE(parentTable.hasAssociatedTByKey(1));
        REQUIRE(parentTable.hasAssociatedTByKey(2));
        REQUIRE_FALSE(parentTable.hasAssociatedTByKey(3));
        REQUIRE_FALSE(parentTable.hasAssociatedTByKey(4));
        REQUIRE_FALSE(parentTable.hasAssociatedTByKey(8));
        REQUIRE_FALSE(parentTable.hasAssociatedTByKey(0));
    }

    SECTION("Test hasAssociatedTByValue") {
        ParentTable parentTable;
        REQUIRE_FALSE(parentTable.hasAssociatedTByValue(2));

        parentTable.addRelationT(1, 2);
        REQUIRE(parentTable.hasAssociatedTByValue(2));
        REQUIRE_FALSE(parentTable.hasAssociatedTByValue(1));

        parentTable.addRelationT(2, 3);
        parentTable.addRelationT(1, 3);
        REQUIRE(parentTable.hasAssociatedTByValue(2));
        REQUIRE(parentTable.hasAssociatedTByValue(3));
        REQUIRE_FALSE(parentTable.hasAssociatedTByValue(1));
        REQUIRE_FALSE(parentTable.hasAssociatedTByValue(8));
        REQUIRE_FALSE(parentTable.hasAssociatedTByValue(0));
    }
}
