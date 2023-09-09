#include "catch.hpp"
#include "pkb/tables/CallsTable.h"



TEST_CASE("PKB: CallsTable") {
    SECTION("Test getCallsEntries") {
        CallsTable callsTable;
        callsTable.addCalls("P1", "P2");
        callsTable.addCalls("P1", "P3");
        callsTable.addCalls("P2", "P4");
        callsTable.addCalls("P4", "P5");

        std::unordered_map<std::string, std::unordered_set<std::string>> expected = {
                {"P1", {"P2", "P3"}},
                {"P2", {"P4"}},
                {"P4", {"P5"}}
        };
        REQUIRE(callsTable.getCallsEntries() == expected);
    }

    SECTION("Test getProcsCalledBy") {
        CallsTable callsTable;
        callsTable.addCalls("P1", "P2");
        callsTable.addCalls("P1", "P3");
        callsTable.addCalls("P2", "P4");
        callsTable.addCalls("P4", "P5");

        std::unordered_set<std::string> expected = {"P2", "P3"};
        REQUIRE(callsTable.getProcsCalledBy("P1") == expected);

        expected = {"P4"};
        REQUIRE(callsTable.getProcsCalledBy("P2") == expected);

        expected = {"P5"};
        REQUIRE(callsTable.getProcsCalledBy("P4") == expected);
    }

    SECTION("Test getProcsCalling") {
        CallsTable callsTable;
        callsTable.addCalls("P1", "P2");
        callsTable.addCalls("P1", "P3");
        callsTable.addCalls("P2", "P4");
        callsTable.addCalls("P4", "P5");

        std::unordered_set<std::string> expected = {"P1"};
        REQUIRE(callsTable.getProcsCalling("P2") == expected);

        expected = {"P1"};
        REQUIRE(callsTable.getProcsCalling("P3") == expected);

        expected = {"P2"};
        REQUIRE(callsTable.getProcsCalling("P4") == expected);

        expected = {"P4"};
        REQUIRE(callsTable.getProcsCalling("P5") == expected);
    }

    SECTION("Test isCalls") {
        CallsTable callsTable;
        callsTable.addCalls("P1", "P2");
        callsTable.addCalls("P1", "P3");
        callsTable.addCalls("P2", "P4");
        callsTable.addCalls("P4", "P5");

        REQUIRE(callsTable.isCalls("P1", "P2"));
        REQUIRE(callsTable.isCalls("P1", "P3"));
        REQUIRE(callsTable.isCalls("P2", "P4"));
        REQUIRE(callsTable.isCalls("P4", "P5"));

        REQUIRE_FALSE(callsTable.isCalls("P2", "P2"));
        REQUIRE_FALSE(callsTable.isCalls("P3", "P2"));
        REQUIRE_FALSE(callsTable.isCalls("P5", "P1"));
        REQUIRE_FALSE(callsTable.isCalls("foo", "bar"));
        REQUIRE_FALSE(callsTable.isCalls("", "P2"));
        REQUIRE_FALSE(callsTable.isCalls("P2", ""));
    }

    SECTION("Test hasCalls") {
        CallsTable callsTable;
        REQUIRE_FALSE(callsTable.hasCalls());

        callsTable.addCalls("P1", "P2");

        REQUIRE(callsTable.hasCalls());
    }

    SECTION("Test hasCallsByKey") {
        CallsTable callsTable;
        REQUIRE_FALSE(callsTable.hasCallsByKey("P1"));

        callsTable.addCalls("P1", "P2");
        REQUIRE(callsTable.hasCallsByKey("P1"));
        REQUIRE_FALSE(callsTable.hasCallsByKey("P2"));
    }

    SECTION("Test hasCallsByValue") {
        CallsTable callsTable;
        REQUIRE_FALSE(callsTable.hasCallsByValue("P2"));

        callsTable.addCalls("P1", "P2");
        REQUIRE(callsTable.hasCallsByValue("P2"));
        REQUIRE_FALSE(callsTable.hasCallsByValue("P1"));
    }

    SECTION("Test getCallerProcs") {
        CallsTable callsTable;
        callsTable.addCalls("P1", "P2");
        callsTable.addCalls("P1", "P3");
        callsTable.addCalls("P2", "P4");
        callsTable.addCalls("P4", "P5");

        std::unordered_set<std::string> expected = {"P1",
                                          "P2",
                                          "P4"};
        REQUIRE(callsTable.getCallerProcs() == expected);
    }

    SECTION("Test getCalleeProcs") {
        CallsTable callsTable;
        callsTable.addCalls("P1", "P2");
        callsTable.addCalls("P1", "P3");
        callsTable.addCalls("P2", "P4");
        callsTable.addCalls("P4", "P5");

        std::unordered_set<std::string> expected = {"P2", "P3", "P4", "P5"};
        REQUIRE(callsTable.getCalleeProcs() == expected);
    }

    SECTION("Test getCallsTEntries") {
        CallsTable callsTable;
        callsTable.addCallsT("P1", "P2");
        callsTable.addCallsT("P1", "P3");
        callsTable.addCallsT("P2", "P4");
        callsTable.addCallsT("P4", "P5");
        callsTable.addCallsT("P4", "P6");
        callsTable.addCallsT("P2", "P5");
        callsTable.addCallsT("P2", "P6");

        std::unordered_map<std::string, std::unordered_set<std::string>> expected = {
                {"P1", {"P2", "P3"}},
                {"P2", {"P4", "P5", "P6"}},
                {"P4", {"P5", "P6"}}
        };
        REQUIRE(callsTable.getCallsTEntries() == expected);
    }

    SECTION("Test getProcsCalledTBy") {
        CallsTable callsTable;
        callsTable.addCallsT("P1", "P2");
        callsTable.addCallsT("P1", "P3");
        callsTable.addCallsT("P2", "P4");
        callsTable.addCallsT("P4", "P5");
        callsTable.addCallsT("P4", "P6");
        callsTable.addCallsT("P2", "P5");
        callsTable.addCallsT("P2", "P6");

        std::unordered_set<std::string> expected = {"P2", "P3"};
        REQUIRE(callsTable.getProcsCalledTBy("P1") == expected);

        expected = {"P4", "P5", "P6"};
        REQUIRE(callsTable.getProcsCalledTBy("P2") == expected);

        expected = {"P5", "P6"};
        REQUIRE(callsTable.getProcsCalledTBy("P4") == expected);
    }

    SECTION("Test getProcsCallingT") {
        CallsTable callsTable;
        callsTable.addCallsT("P1", "P2");
        callsTable.addCallsT("P1", "P3");
        callsTable.addCallsT("P2", "P4");
        callsTable.addCallsT("P4", "P5");
        callsTable.addCallsT("P4", "P6");
        callsTable.addCallsT("P2", "P5");
        callsTable.addCallsT("P2", "P6");

        std::unordered_set<std::string> expected = {"P1"};
        REQUIRE(callsTable.getProcsCallingT("P2") == expected);

        expected = {"P1"};
        REQUIRE(callsTable.getProcsCallingT("P3") == expected);

        expected = {"P2"};
        REQUIRE(callsTable.getProcsCallingT("P4") == expected);

        expected = {"P2", "P4"};
        REQUIRE(callsTable.getProcsCallingT("P5") == expected);

        expected = {"P2", "P4"};
        REQUIRE(callsTable.getProcsCallingT("P6") == expected);
    }

    SECTION("Test isCallsT") {
        CallsTable callsTable;
        callsTable.addCallsT("P1", "P2");
        callsTable.addCallsT("P1", "P3");
        callsTable.addCallsT("P2", "P4");
        callsTable.addCallsT("P4", "P5");
        callsTable.addCallsT("P4", "P6");
        callsTable.addCallsT("P2", "P5");
        callsTable.addCallsT("P2", "P6");

        REQUIRE(callsTable.isCallsT("P1", "P2"));
        REQUIRE(callsTable.isCallsT("P1", "P3"));
        REQUIRE(callsTable.isCallsT("P2", "P4"));
        REQUIRE(callsTable.isCallsT("P4", "P5"));
        REQUIRE(callsTable.isCallsT("P4", "P6"));
        REQUIRE(callsTable.isCallsT("P2", "P5"));
        REQUIRE(callsTable.isCallsT("P2", "P6"));

        REQUIRE_FALSE(callsTable.isCallsT("P2", "P2"));
        REQUIRE_FALSE(callsTable.isCallsT("P3", "P2"));
        REQUIRE_FALSE(callsTable.isCallsT("P5", "P1"));
        REQUIRE_FALSE(callsTable.isCallsT("P5", "P2"));
        REQUIRE_FALSE(callsTable.isCallsT("P1", "P4"));
        REQUIRE_FALSE(callsTable.isCallsT("P3", "P5"));
        REQUIRE_FALSE(callsTable.isCallsT("P6", "P2"));
        REQUIRE_FALSE(callsTable.isCallsT("foo", "bar"));
        REQUIRE_FALSE(callsTable.isCallsT("", "P2"));
        REQUIRE_FALSE(callsTable.isCallsT("P2", ""));
    }

    SECTION("Test hasCallsT") {
        CallsTable callsTable;
        REQUIRE_FALSE(callsTable.hasCallsT());

        callsTable.addCallsT("P1", "P2");

        REQUIRE(callsTable.hasCallsT());
    }

    SECTION("Test hasCallsTByKey") {
        CallsTable callsTable;
        REQUIRE_FALSE(callsTable.hasCallsTByKey("P1"));

        callsTable.addCallsT("P1", "P2");
        REQUIRE(callsTable.hasCallsTByKey("P1"));
        REQUIRE_FALSE(callsTable.hasCallsTByKey("P2"));
    }

    SECTION("Test hasCallsTByValue") {
        CallsTable callsTable;
        REQUIRE_FALSE(callsTable.hasCallsTByValue("P2"));

        callsTable.addCallsT("P1", "P2");
        REQUIRE(callsTable.hasCallsTByValue("P2"));
        REQUIRE_FALSE(callsTable.hasCallsTByValue("P1"));
    }

}