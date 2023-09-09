#include "catch.hpp"
#include "pkb/base/BaseSet.h"



TEST_CASE("PKB: BaseSet") {
    SECTION("Test adding duplicate entries") {
        BaseSet<std::string> stringSet;
        BaseSet<int> intSet;

        intSet.addEntry(1);
        intSet.addEntry(2);
        intSet.addEntry(3);
        intSet.addEntry(3);

        REQUIRE(intSet.getSize() == 3);

        stringSet.addEntry("hello");
        stringSet.addEntry("world");
        stringSet.addEntry("world");

        REQUIRE(stringSet.getSize() == 2);
    }

    SECTION("Test getEntries") {
        BaseSet<std::string> stringSet;
        BaseSet<int> intSet;

        intSet.addEntry(1);
        intSet.addEntry(2);
        intSet.addEntry(3);

        REQUIRE(intSet.getEntries() == std::unordered_set<int>({1, 2, 3}));

        stringSet.addEntry("hello");
        stringSet.addEntry("world");

        REQUIRE(stringSet.getEntries() == std::unordered_set<std::string>({"hello", "world"}));
    }

    SECTION("Test hasEntry") {
        BaseSet<std::string> stringSet;
        BaseSet<int> intSet;

        stringSet.addEntry("hello");
        stringSet.addEntry("world");

        REQUIRE(stringSet.containKey("hello"));
        REQUIRE_FALSE(stringSet.containKey("bla"));

        intSet.addEntry(1);
        intSet.addEntry(2);
        intSet.addEntry(3);

        REQUIRE(intSet.containKey(1));
        REQUIRE_FALSE(intSet.containKey(8));
    }

    SECTION("Test getSize") {
        BaseSet<std::string> stringSet;
        BaseSet<int> intSet;

        REQUIRE(stringSet.getSize() == 0);
        REQUIRE(intSet.getSize() == 0);

        stringSet.addEntry("hello");
        stringSet.addEntry("world");

        intSet.addEntry(1);
        intSet.addEntry(2);
        intSet.addEntry(3);

        REQUIRE(stringSet.getSize() == 2);
        REQUIRE(intSet.getSize() == 3);
    }
}