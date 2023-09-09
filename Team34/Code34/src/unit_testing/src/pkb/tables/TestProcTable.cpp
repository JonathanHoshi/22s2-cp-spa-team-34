#include "catch.hpp"
#include "pkb/tables/ProcTable.h"

TEST_CASE("PKB: ProcTable") {

    SECTION("Test empty ProcTable") {
        ProcTable procTable;
        REQUIRE(procTable.getSize() == 0);
        REQUIRE(procTable.getProcs().empty());
    }

    SECTION("Test addProc") {
        ProcTable procTable;
        procTable.addProc("main");
        REQUIRE(procTable.getSize() == 1);
        REQUIRE(procTable.isProc("main"));
        REQUIRE_FALSE(procTable.isProc("proc1"));
    }

    SECTION("Test addProc duplicates") {
        ProcTable procTable;
        procTable.addProc("proc1");
        procTable.addProc("proc1");
        REQUIRE(procTable.getSize() == 1);
    }

    SECTION("Test addProc multiple procs and getProcs") {
        ProcTable procTable;
        procTable.addProc("main");
        procTable.addProc("proc1");
        procTable.addProc("proc2");

        std::unordered_set<std::string> expectedProcs = {"main", "proc1", "proc2"};
        std::unordered_set<std::string> actualProcs = procTable.getProcs();

        REQUIRE(actualProcs == expectedProcs);
        REQUIRE(procTable.getSize() == 3);
        REQUIRE(procTable.isProc("main"));
        REQUIRE(procTable.isProc("proc1"));
        REQUIRE(procTable.isProc("proc2"));
        REQUIRE_FALSE(procTable.isProc("not_a_proc"));
    }
}
