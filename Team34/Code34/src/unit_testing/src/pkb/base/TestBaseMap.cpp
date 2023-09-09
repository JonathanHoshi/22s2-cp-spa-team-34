#include "catch.hpp"
#include "pkb/base/BaseMap.h"

TEST_CASE("PKB: BaseMap") {
    SECTION("Test adding duplicate entries") {
        BaseMap<std::string, int> testMap;
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key1", 2);
        testMap.addEntry("Key2", 3);
        testMap.addEntry("Key2", 3);

        REQUIRE(testMap.getValueByKey("Key1") == 1);
        REQUIRE(testMap.getValueByKey("Key2") == 3);
        REQUIRE(testMap.getValueByKey("Key3") == 0);
    }

    SECTION("Test getKeys") {
        BaseMap<std::string, int> testMap;
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key2", 2);
        testMap.addEntry("Key3", 3);

        REQUIRE(testMap.getKeys() == std::unordered_set<std::string>({"Key1", "Key2", "Key3"}));
    }

    SECTION("Test hasKey") {
        BaseMap<std::string, int> testMap;
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key2", 2);

        REQUIRE(testMap.hasKey("Key1"));
        REQUIRE_FALSE(testMap.hasKey("Key4"));
    }

    SECTION("Test hasKeyValue") {
        BaseMap<std::string, int> testMap;
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key2", 2);

        REQUIRE(testMap.hasKeyValue("Key1", 1));
        REQUIRE(testMap.hasKeyValue("Key2", 2));
        REQUIRE_FALSE(testMap.hasKeyValue("Key1", 3));
        REQUIRE_FALSE(testMap.hasKeyValue("Key2", 1));
    }

    SECTION("Test getSize") {
        BaseMap<std::string, int> testMap;
        testMap.addEntry("Key1", 1);
        testMap.addEntry("Key2", 2);
        testMap.addEntry("Key3", 3);

        REQUIRE(testMap.getSize() == 3);
    }
}