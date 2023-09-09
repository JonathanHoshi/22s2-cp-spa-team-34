#include "catch.hpp"
#include "pkb/tables/UsesTable.h"



TEST_CASE("PKB: UsesTable statements positive test cases") {
    SECTION("Getting all stmt-uses-var entries works") {
        UsesTable usesTable;
        usesTable.addVarS(1, "x");
        usesTable.addVarS(1, "y");
        usesTable.addVarS(2, "z");
        usesTable.addVarS(3, "x");

        std::unordered_map<int, std::unordered_set<std::string>> expectedEntries = {
                {1, std::unordered_set<std::string>{"x", "y"}},
                {2, std::unordered_set<std::string>{"z"}},
                {3, std::unordered_set<std::string>{"x"}}
        };
        REQUIRE(usesTable.getStmtVarEntries() == expectedEntries);
    }

    SECTION("Adding and getting stmt-uses-var relations works") {
        UsesTable usesTable;
        usesTable.addVarS(1, "x");
        usesTable.addVarS(1, "y");
        usesTable.addVarS(2, "z");
        usesTable.addVarS(3, "x");

        REQUIRE(usesTable.getVarsByStmt(1) == std::unordered_set<std::string>{"x", "y"});
        REQUIRE(usesTable.getVarsByStmt(2) == std::unordered_set<std::string>{"z"});
        REQUIRE(usesTable.getVarsByStmt(3) == std::unordered_set<std::string>{"x"});
        REQUIRE(usesTable.getStmtsByVar("x") == std::unordered_set<int>{1, 3});
        REQUIRE(usesTable.getStmtsByVar("y") == std::unordered_set<int>{1});
        REQUIRE(usesTable.getStmtsByVar("z") == std::unordered_set<int>{2});
        REQUIRE(usesTable.isAssociatedS(1, "x"));
        REQUIRE_FALSE(usesTable.isAssociatedS(1, "z"));
        REQUIRE_FALSE(usesTable.isAssociatedS(5, "a"));
    }

    SECTION("Getting vars used by a statement works") {
        UsesTable usesTable;
        usesTable.addVarS(1, "x");
        usesTable.addVarS(1, "y");
        usesTable.addVarS(2, "z");
        usesTable.addVarS(2, "x");
        usesTable.addVarS(2, "abc");

        std::unordered_set<std::string> expectedVarsUsedBy1 = {"x", "y"};
        std::unordered_set<std::string> expectedVarsUsedBy2 = {"x", "z", "abc"};

        REQUIRE(usesTable.getVarsByStmt(1) == expectedVarsUsedBy1);
        REQUIRE(usesTable.getVarsByStmt(2) == expectedVarsUsedBy2);
    }

    SECTION("Getting statements using a var works") {
        UsesTable usesTable;
        usesTable.addVarS(1, "x");
        usesTable.addVarS(2, "x");
        usesTable.addVarS(3, "y");

        std::unordered_set<int> expectedStmtsUsingX = {1, 2};
        std::unordered_set<int> expectedStmtsUsingY = {3};

        REQUIRE(usesTable.getStmtsByVar("x") == expectedStmtsUsingX);
        REQUIRE(usesTable.getStmtsByVar("y") == expectedStmtsUsingY);
    }

    SECTION("Getting used vars in statements works") {
        UsesTable usesTable;
        usesTable.addVarS(1, "x");
        usesTable.addVarS(1, "y");
        usesTable.addVarS(2, "z");

        std::unordered_set<std::string> expectedUsedVarsInStmts = {"x", "y", "z"};

        REQUIRE(usesTable.getVarsInStmts() == expectedUsedVarsInStmts);
    }

    SECTION("Getting statements that use some var works") {
        UsesTable usesTable;
        usesTable.addVarS(1, "x");
        usesTable.addVarS(2, "x");
        usesTable.addVarS(3, "y");

        std::unordered_set<int> expectedStmtsUsingSomeVar = {1, 2, 3};

        REQUIRE(usesTable.getStmts() == expectedStmtsUsingSomeVar);
    }

    SECTION("Checking if stmt uses var works") {
        UsesTable usesTable;
        usesTable.addVarS(1, "x");
        usesTable.addVarS(2, "x");
        usesTable.addVarS(3, "y");

        REQUIRE(usesTable.isAssociatedS(1, "x"));
        REQUIRE(usesTable.isAssociatedS(2, "x"));
        REQUIRE(usesTable.isAssociatedS(3, "y"));
        REQUIRE_FALSE(usesTable.isAssociatedS(1, "y"));
        REQUIRE_FALSE(usesTable.isAssociatedS(2, "y"));
        REQUIRE_FALSE(usesTable.isAssociatedS(3, "x"));
    }

    SECTION("Checking if there exists stmt uses var works") {
        UsesTable usesTable;
        REQUIRE_FALSE(usesTable.hasAssociatedS());

        usesTable.addVarP("proc", "abc");
        REQUIRE_FALSE(usesTable.hasAssociatedS());

        usesTable.addVarS(1, "x");
        REQUIRE(usesTable.hasAssociatedS());
    }

    SECTION("Checking if there exists stmt uses var by key works") {
        UsesTable usesTable;
        REQUIRE_FALSE(usesTable.hasAssociatedSByKey(1));

        usesTable.addVarS(1, "x");
        REQUIRE_FALSE(usesTable.hasAssociatedSByKey(2));
        REQUIRE(usesTable.hasAssociatedSByKey(1));
    }

    SECTION("Checking if there exists stmt uses var by key works") {
        UsesTable usesTable;
        REQUIRE_FALSE(usesTable.hasAssociatedSByValue("x"));

        usesTable.addVarS(1, "x");
        REQUIRE_FALSE(usesTable.hasAssociatedSByValue("y"));
        REQUIRE(usesTable.hasAssociatedSByValue("x"));
    }

    SECTION("Adding stmt-uses-var relation works") {
        UsesTable usesTable;
        usesTable.addVarS(1, "x");
        usesTable.addVarS(2, "x");

        REQUIRE(usesTable.getVarsByStmt(1) == std::unordered_set<std::string>{"x"});
        REQUIRE(usesTable.getVarsByStmt(2) == std::unordered_set<std::string>{"x"});
        REQUIRE(usesTable.getStmtsByVar("x") == std::unordered_set<int>{1, 2});
    }
}

TEST_CASE("PKB: UsesTable procedures positive test cases") {
    SECTION("Getting all proc-uses-var entries works") {
        UsesTable usesTable;
        usesTable.addVarP("main", "x");
        usesTable.addVarP("main", "y");
        usesTable.addVarP("foo", "z");
        usesTable.addVarP("bar", "x");

        std::unordered_map<std::string, std::unordered_set<std::string>> expectedEntries = {
                {"main", std::unordered_set<std::string>{"x", "y"}},
                {"foo", std::unordered_set<std::string>{"z"}},
                {"bar", std::unordered_set<std::string>{"x"}}
        };
        REQUIRE(usesTable.getProcVarEntries() == expectedEntries);
    }

    SECTION("Adding and getting proc-uses-var relations works") {
        UsesTable usesTable;
        usesTable.addVarP("main", "x");
        usesTable.addVarP("main", "y");
        usesTable.addVarP("foo", "z");
        usesTable.addVarP("bar", "x");

        REQUIRE(usesTable.getVarsByProc("main") == std::unordered_set<std::string>{"x", "y"});
        REQUIRE(usesTable.getVarsByProc("foo") == std::unordered_set<std::string>{"z"});
        REQUIRE(usesTable.getVarsByProc("bar") == std::unordered_set<std::string>{"x"});
        REQUIRE(usesTable.getProcsByVar("x") == std::unordered_set<std::string>{"main", "bar"});
        REQUIRE(usesTable.getProcsByVar("y") == std::unordered_set<std::string>{"main"});
        REQUIRE(usesTable.getProcsByVar("z") == std::unordered_set<std::string>{"foo"});
        REQUIRE(usesTable.isAssociatedP("main", "x"));
        REQUIRE_FALSE(usesTable.isAssociatedP("foo", "y"));
        REQUIRE_FALSE(usesTable.isAssociatedP("proc1", "a"));
    }

    SECTION("Getting vars used by a procedure works") {
        UsesTable usesTable;
        usesTable.addVarP("main", "x");
        usesTable.addVarP("main", "y");
        usesTable.addVarP("foo", "z");
        usesTable.addVarP("foo", "x");
        usesTable.addVarP("foo", "abc");

        std::unordered_set<std::string> expectedVarsUsedByMain = {"x", "y"};
        std::unordered_set<std::string> expectedVarsUsedByFoo = {"x", "z", "abc"};

        REQUIRE(usesTable.getVarsByProc("main") == expectedVarsUsedByMain);
        REQUIRE(usesTable.getVarsByProc("foo") == expectedVarsUsedByFoo);
    }

    SECTION("Getting procedures using a var works") {
        UsesTable usesTable;
        usesTable.addVarP("main", "x");
        usesTable.addVarP("foo", "x");
        usesTable.addVarP("bar", "y");

        std::unordered_set<std::string> expectedProcsUsingX = {"main", "foo"};
        std::unordered_set<std::string> expectedProcsUsingY = {"bar"};

        REQUIRE(usesTable.getProcsByVar("x") == expectedProcsUsingX);
        REQUIRE(usesTable.getProcsByVar("y") == expectedProcsUsingY);
    }

    SECTION("Getting used vars in procedures works") {
        UsesTable usesTable;
        usesTable.addVarP("main", "x");
        usesTable.addVarP("main", "y");
        usesTable.addVarP("foo", "z");

        std::unordered_set<std::string> expectedUsedVarsInProcs = {"x", "y", "z"};

        REQUIRE(usesTable.getVarsInProcs() == expectedUsedVarsInProcs);
    }

    SECTION("Getting procedures that use some var works") {
        UsesTable usesTable;
        usesTable.addVarP("main", "x");
        usesTable.addVarP("foo", "x");
        usesTable.addVarP("bar", "y");

        std::unordered_set<std::string> expectedProcsUsingSomeVar = {"main", "foo", "bar"};

        REQUIRE(usesTable.getProcs() == expectedProcsUsingSomeVar);
    }

    SECTION("Checking if proc uses var works") {
        UsesTable usesTable;
        usesTable.addVarP("main", "x");
        usesTable.addVarP("foo", "x");
        usesTable.addVarP("bar", "y");

        REQUIRE(usesTable.isAssociatedP("main", "x"));
        REQUIRE(usesTable.isAssociatedP("foo", "x"));
        REQUIRE(usesTable.isAssociatedP("bar", "y"));
        REQUIRE_FALSE(usesTable.isAssociatedP("main", "y"));
        REQUIRE_FALSE(usesTable.isAssociatedP("foo", "y"));
        REQUIRE_FALSE(usesTable.isAssociatedP("bar", "x"));
    }

    SECTION("Checking if there exists proc uses var works") {
        UsesTable usesTable;
        REQUIRE_FALSE(usesTable.hasAssociatedP());

        usesTable.addVarS(1, "x");
        REQUIRE_FALSE(usesTable.hasAssociatedP());

        usesTable.addVarP("proc", "abc");
        REQUIRE(usesTable.hasAssociatedP());
    }

    SECTION("Checking if there exists proc uses var by key works") {
        UsesTable usesTable;
        REQUIRE_FALSE(usesTable.hasAssociatedPByKey("proc"));

        usesTable.addVarP("proc", "x");
        REQUIRE_FALSE(usesTable.hasAssociatedPByKey("bla"));
        REQUIRE(usesTable.hasAssociatedPByKey("proc"));
    }

    SECTION("Checking if there exists proc uses var by key works") {
        UsesTable usesTable;
        REQUIRE_FALSE(usesTable.hasAssociatedPByValue("x"));

        usesTable.addVarP("proc", "x");
        REQUIRE_FALSE(usesTable.hasAssociatedPByValue("y"));
        REQUIRE(usesTable.hasAssociatedPByValue("x"));
    }

    SECTION("Adding proc-uses-var relation works") {
        UsesTable usesTable;
        usesTable.addVarP("main", "x");
        usesTable.addVarP("foo", "x");

        REQUIRE(usesTable.getVarsByProc("main") == std::unordered_set<std::string>{"x"});
        REQUIRE(usesTable.getVarsByProc("foo") == std::unordered_set<std::string>{"x"});
        REQUIRE(usesTable.getProcsByVar("x") == std::unordered_set<std::string>{"main", "foo"});
    }
}

TEST_CASE("PKB: UsesTable statements negative test cases") {
    SECTION("Getting vars used by stmt with invalid stmt number returns empty set") {
        UsesTable usesTable;
        REQUIRE(usesTable.getVarsByStmt(1).empty());
        REQUIRE(usesTable.getVarsByStmt(-1).empty());
    }

    SECTION("Getting stmts using var with invalid var name returns empty set") {
        UsesTable usesTable;
        REQUIRE(usesTable.getStmtsByVar("x").empty());
        REQUIRE(usesTable.getStmtsByVar("").empty());
    }

    SECTION("Checking if stmt uses var with non-existent input returns false") {
        UsesTable usesTable;
        REQUIRE_FALSE(usesTable.isAssociatedS(1, "x"));
        REQUIRE_FALSE(usesTable.isAssociatedS(-1, "x"));
        REQUIRE_FALSE(usesTable.isAssociatedS(1, ""));
        REQUIRE_FALSE(usesTable.isAssociatedS(-1, ""));
    }
}

TEST_CASE("PKB: UsesTable procedures negative test cases") {
    SECTION("Getting vars used by proc with non-existent proc name returns empty set") {
        UsesTable usesTable;
        REQUIRE(usesTable.getVarsByProc("1").empty());
        REQUIRE(usesTable.getVarsByProc("").empty());
    }

    SECTION("Getting procs using var with non-existent var name returns empty set") {
        UsesTable usesTable;
        REQUIRE(usesTable.getProcsByVar("x").empty());
        REQUIRE(usesTable.getProcsByVar("").empty());
    }

    SECTION("Checking if proc uses var with non-existent input returns false") {
        UsesTable usesTable;
        REQUIRE_FALSE(usesTable.isAssociatedP("foo", "x"));
        REQUIRE_FALSE(usesTable.isAssociatedP("", "x"));
        REQUIRE_FALSE(usesTable.isAssociatedP("foo", ""));
        REQUIRE_FALSE(usesTable.isAssociatedP("", ""));
    }
}
