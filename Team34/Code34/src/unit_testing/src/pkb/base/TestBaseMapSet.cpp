#include "catch.hpp"
#include "pkb/base/BaseMapSet.h"

TEST_CASE("PKB: BaseMapSet") {
    SECTION("Test adding duplicate entries") {
        BaseMapSet<std::string, int> testMap;
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key1", 2);
        testMap.addEntry("Key2", 3);
        testMap.addEntry("Key2", 3);

        REQUIRE(testMap.getValuesByKey("Key1") == std::unordered_set<int>({1, 2}));
        REQUIRE(testMap.getValuesByKey("Key2") == std::unordered_set<int>({3}));
        REQUIRE(testMap.getValuesByKey("Key3") == std::unordered_set<int>());
    }

    SECTION("Test getKeys") {
        BaseMapSet<std::string, int> testMap;
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key1", 2);
        testMap.addEntry("Key2", 3);

        REQUIRE(testMap.getKeys() == std::unordered_set<std::string>({"Key1", "Key2"}));
    }

    SECTION("Test hasKey") {
        BaseMapSet<std::string, int> testMap;
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key1", 2);

        REQUIRE(testMap.hasKey("Key1"));
        REQUIRE_FALSE(testMap.hasKey("Key2"));
    }

    SECTION("Test hasKeyValue") {
        BaseMapSet<std::string, int> testMap;
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key1", 2);

        REQUIRE(testMap.hasKeyValue("Key1", 1));
        REQUIRE(testMap.hasKeyValue("Key1", 2));
        REQUIRE_FALSE(testMap.hasKeyValue("Key1", 3));
        REQUIRE_FALSE(testMap.hasKeyValue("Key2", 1));
    }

    SECTION("Test getSize") {
        BaseMapSet<std::string, int> testMap;
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key1", 2);
        testMap.addEntry("Key2", 3);

        REQUIRE(testMap.getSize() == 2);
    }
}