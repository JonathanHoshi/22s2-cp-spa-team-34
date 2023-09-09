#include "catch.hpp"
#include "pkb/tables/NextTable.h"



TEST_CASE("PKB: Next Table") {
    SECTION("Test Next add and getEntries") {
        NextTable nextTable;
        nextTable.addNext(1, 2);
        nextTable.addNext(1, 3);
        nextTable.addNext(1, 4);
        nextTable.addNext(2, 3);
        nextTable.addNext(2, 4);
        nextTable.addNext(2, 5);
        nextTable.addNext(3, 6);
        std::unordered_map<int, std::unordered_set<int>> expectedKeyToVal = {
            {1, std::unordered_set<int>{2, 3, 4}},
            {2, std::unordered_set<int>{3, 4, 5}},
            {3, std::unordered_set<int>{6}}
        };

        std::unordered_map<int, std::unordered_set<int>> expectedKeyToValT = {
            {1, std::unordered_set<int>{2, 3, 4, 5, 6}},
            {2, std::unordered_set<int>{3, 4, 5, 6}},
            {3, std::unordered_set<int>{6}}
        };
        REQUIRE(nextTable.getNextEntries() == expectedKeyToVal);
        REQUIRE(nextTable.getNextTEntries() == expectedKeyToValT);
    };
    SECTION("Test isNext") {
        NextTable nextTable;
        nextTable.addNext(1, 2);
        nextTable.addNext(2, 3);
        nextTable.addNext(3, 4);
        REQUIRE(nextTable.isNext(1, 2));
        REQUIRE(nextTable.isNext(2, 3));
        REQUIRE(nextTable.isNext(3, 4));
        REQUIRE_FALSE(nextTable.isNext(1, 3));
        REQUIRE_FALSE(nextTable.isNext(2, 1));
        REQUIRE_FALSE(nextTable.isNext(2, 4));
    };
    SECTION("Test isNextT") {
        NextTable nextTable;
        nextTable.addNext(1, 2);
        nextTable.addNext(1, 3);
        nextTable.addNext(2, 3);
        nextTable.addNext(2, 4);
        nextTable.addNext(2, 5);
        nextTable.addNext(3, 6);
        nextTable.addNext(6, 7);
        REQUIRE(nextTable.isNextT(1, 2));
        REQUIRE(nextTable.isNextT(1, 3));
        REQUIRE(nextTable.isNextT(2, 3));
        REQUIRE(nextTable.isNextT(2, 4));
        REQUIRE(nextTable.isNextT(2, 5));
        REQUIRE(nextTable.isNextT(1, 4));
        REQUIRE(nextTable.isNextT(1, 6));
        REQUIRE(nextTable.isNextT(1, 7));
        REQUIRE(nextTable.isNextT(2, 7));
        REQUIRE_FALSE(nextTable.isNextT(4, 6));
        REQUIRE_FALSE(nextTable.isNextT(4, 7));
        REQUIRE_FALSE(nextTable.isNextT(4, 1));
        REQUIRE_FALSE(nextTable.isNextT(2, 1));
        REQUIRE_FALSE(nextTable.isNextT(3, 1));
    };
    SECTION("Test getKeysByVal") {
        NextTable nextTable;
        nextTable.addNext(1, 3);
        nextTable.addNext(2, 3);
        nextTable.addNext(1, 4);
        nextTable.addNext(3, 4);
        nextTable.addNext(4, 1);
        nextTable.addNext(4, 2);
        std::unordered_set<int> expected = {1, 2};
        REQUIRE(nextTable.getKeysByValue(3) == expected);
    };
    SECTION("Test getValuesByKey") {
        NextTable nextTable;
        nextTable.addNext(1, 3);
        nextTable.addNext(2, 3);
        nextTable.addNext(1, 4);
        nextTable.addNext(3, 5);
        nextTable.addNext(3, 6);
        nextTable.addNext(2, 1);
        std::unordered_set<int> expected = {3, 4};
        REQUIRE(nextTable.getValuesByKey(1) == expected);
    };
    SECTION("Test getTKeysByValue") {
        NextTable nextTable;
        nextTable.addNext(1, 3);
        nextTable.addNext(2, 3);
        nextTable.addNext(1, 4);
        nextTable.addNext(3, 4);
        nextTable.addNext(4, 1);
        nextTable.addNext(4, 2);
        std::unordered_set<int> expected = {1, 2, 3, 4};
        REQUIRE(nextTable.getTKeysByValue(3) == expected);
    };
    SECTION("Test getTValuesByKey") {
        NextTable nextTable;
        nextTable.addNext(1, 3);
        nextTable.addNext(2, 3);
        nextTable.addNext(1, 4);
        nextTable.addNext(3, 5);
        nextTable.addNext(3, 6);
        nextTable.addNext(2, 1);
        std::unordered_set<int> expected = {3, 4, 5, 6};
        REQUIRE(nextTable.getTValuesByKey(1) == expected);
    };
    SECTION("Test hasNext") {
        NextTable nextTable;
        REQUIRE_FALSE(nextTable.hasNext());
        nextTable.addNext(1, 2);
        REQUIRE(nextTable.hasNext());
    };
    SECTION("Test hasNextByKey") {
        NextTable nextTable;
        nextTable.addNext(1, 3);
        nextTable.addNext(2, 3);
        REQUIRE(nextTable.hasNextByKey(1));
        REQUIRE(nextTable.hasNextByKey(2));
        REQUIRE_FALSE(nextTable.hasNextByKey(3));
    };
    SECTION("Test hasNextByValue") {
        NextTable nextTable;
        nextTable.addNext(1, 3);
        nextTable.addNext(2, 3);
        REQUIRE_FALSE(nextTable.hasNextByValue(1));
        REQUIRE_FALSE(nextTable.hasNextByValue(2));
        REQUIRE(nextTable.hasNextByValue(3));
    }
}