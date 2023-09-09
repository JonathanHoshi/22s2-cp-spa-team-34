#include "catch.hpp"
#include "pkb/tables/ModifiesTable.h"



TEST_CASE("PKB: ModifiesTable statements positive test cases") {
    SECTION("Getting all stmt-modifies-var entries works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarS(1, "y");
        modifiesTable.addVarS(2, "z");
        modifiesTable.addVarS(3, "x");

        std::unordered_map<int, std::unordered_set<std::string>> expectedEntries = {
                {1, std::unordered_set<std::string>{"y"}},
                {2, std::unordered_set<std::string>{"z"}},
                {3, std::unordered_set<std::string>{"x"}}
        };
        REQUIRE(modifiesTable.getStmtVarEntries() == expectedEntries);
    }

    SECTION("Adding and getting stmt-modifies-var relations works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarS(1, "y");
        modifiesTable.addVarS(2, "y");
        modifiesTable.addVarS(3, "x");

        REQUIRE(modifiesTable.getVarsByStmt(1) == std::unordered_set<std::string>{"y"});
        REQUIRE(modifiesTable.getVarsByStmt(2) == std::unordered_set<std::string>{"y"});
        REQUIRE(modifiesTable.getVarsByStmt(3) == std::unordered_set<std::string>{"x"});
        REQUIRE(modifiesTable.getStmtsByVar("x") == std::unordered_set<int>{3});
        REQUIRE(modifiesTable.getStmtsByVar("y") == std::unordered_set<int>{1, 2});
        REQUIRE(modifiesTable.getStmtsByVar("z").empty());
        REQUIRE(modifiesTable.isAssociatedS(1, "y"));
        REQUIRE_FALSE(modifiesTable.isAssociatedS(1, "z"));
        REQUIRE_FALSE(modifiesTable.isAssociatedS(5, "a"));
    }

    SECTION("Getting vars modified by a statement works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarS(1, "y");
        modifiesTable.addVarS(2, "abc");

        std::unordered_set<std::string> expectedVarsModifiedBy1 = {"y"};
        std::unordered_set<std::string> expectedVarsModifiedBy2 = {"abc"};

        REQUIRE(modifiesTable.getVarsByStmt(1) == expectedVarsModifiedBy1);
        REQUIRE(modifiesTable.getVarsByStmt(2) == expectedVarsModifiedBy2);
    }

    SECTION("Getting statements modifies a var works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarS(1, "x");
        modifiesTable.addVarS(2, "x");
        modifiesTable.addVarS(3, "y");

        std::unordered_set<int> expectedStmtsModifyingX = {1, 2};
        std::unordered_set<int> expectedStmtsModifyingY = {3};

        REQUIRE(modifiesTable.getStmtsByVar("x") == expectedStmtsModifyingX);
        REQUIRE(modifiesTable.getStmtsByVar("y") == expectedStmtsModifyingY);
    }

    SECTION("Getting modified vars in statements works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarS(1, "y");
        modifiesTable.addVarS(2, "z");

        std::unordered_set<std::string> expectedModifiedVarsInStmts = {"y", "z"};

        REQUIRE(modifiesTable.getVarsInStmts() == expectedModifiedVarsInStmts);
    }

    SECTION("Getting statements that modify some var works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarS(1, "x");
        modifiesTable.addVarS(2, "x");
        modifiesTable.addVarS(3, "y");

        std::unordered_set<int> expectedStmtsModifyingSomeVar = {1, 2, 3};

        REQUIRE(modifiesTable.getStmts() == expectedStmtsModifyingSomeVar);
    }

    SECTION("Checking if stmt modifies var works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarS(1, "x");
        modifiesTable.addVarS(2, "x");
        modifiesTable.addVarS(3, "y");

        REQUIRE(modifiesTable.isAssociatedS(1, "x"));
        REQUIRE(modifiesTable.isAssociatedS(2, "x"));
        REQUIRE(modifiesTable.isAssociatedS(3, "y"));
        REQUIRE_FALSE(modifiesTable.isAssociatedS(1, "y"));
        REQUIRE_FALSE(modifiesTable.isAssociatedS(2, "y"));
        REQUIRE_FALSE(modifiesTable.isAssociatedS(3, "x"));
    }

    SECTION("Checking if there exists stmt modifies var works") {
        ModifiesTable modifiesTable;
        REQUIRE_FALSE(modifiesTable.hasAssociatedS());

        modifiesTable.addVarP("proc", "abc");
        REQUIRE_FALSE(modifiesTable.hasAssociatedS());

        modifiesTable.addVarS(1, "x");
        REQUIRE(modifiesTable.hasAssociatedS());
    }

    SECTION("Checking if there exists stmt modifies var by key works") {
        ModifiesTable modifiesTable;
        REQUIRE_FALSE(modifiesTable.hasAssociatedSByKey(1));

        modifiesTable.addVarS(1, "x");
        REQUIRE_FALSE(modifiesTable.hasAssociatedSByKey(2));
        REQUIRE(modifiesTable.hasAssociatedSByKey(1));
    }

    SECTION("Checking if there exists stmt modifies var by key works") {
        ModifiesTable modifiesTable;
        REQUIRE_FALSE(modifiesTable.hasAssociatedSByValue("x"));

        modifiesTable.addVarS(1, "x");
        REQUIRE_FALSE(modifiesTable.hasAssociatedSByValue("y"));
        REQUIRE(modifiesTable.hasAssociatedSByValue("x"));
    }

    SECTION("Adding stmt-modifies-var relation works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarS(1, "x");
        modifiesTable.addVarS(2, "x");

        REQUIRE(modifiesTable.getVarsByStmt(1) == std::unordered_set<std::string>{"x"});
        REQUIRE(modifiesTable.getVarsByStmt(2) == std::unordered_set<std::string>{"x"});
        REQUIRE(modifiesTable.getStmtsByVar("x") == std::unordered_set<int>{1, 2});
    }
}

TEST_CASE("PKB: ModifiesTable procedures positive test cases") {
    SECTION("Getting all proc-modifies-var entries works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarP("main", "x");
        modifiesTable.addVarP("main", "y");
        modifiesTable.addVarP("foo", "z");
        modifiesTable.addVarP("bar", "x");

        std::unordered_map<std::string, std::unordered_set<std::string>> expectedEntries = {
                {"main", std::unordered_set<std::string>{"x", "y"}},
                {"foo", std::unordered_set<std::string>{"z"}},
                {"bar", std::unordered_set<std::string>{"x"}}
        };
        REQUIRE(modifiesTable.getProcVarEntries() == expectedEntries);
    }

    SECTION("Adding and getting proc-modifies-var relations works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarP("main", "x");
        modifiesTable.addVarP("main", "y");
        modifiesTable.addVarP("foo", "z");
        modifiesTable.addVarP("bar", "x");

        REQUIRE(modifiesTable.getVarsByProc("main") == std::unordered_set<std::string>{"x", "y"});
        REQUIRE(modifiesTable.getVarsByProc("foo") == std::unordered_set<std::string>{"z"});
        REQUIRE(modifiesTable.getVarsByProc("bar") == std::unordered_set<std::string>{"x"});
        REQUIRE(modifiesTable.getProcsByVar("x") == std::unordered_set<std::string>{"main", "bar"});
        REQUIRE(modifiesTable.getProcsByVar("y") == std::unordered_set<std::string>{"main"});
        REQUIRE(modifiesTable.getProcsByVar("z") == std::unordered_set<std::string>{"foo"});
        REQUIRE(modifiesTable.isAssociatedP("main", "x"));
        REQUIRE_FALSE(modifiesTable.isAssociatedP("foo", "y"));
        REQUIRE_FALSE(modifiesTable.isAssociatedP("proc1", "a"));
    }

    SECTION("Getting vars modified by a procedure works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarP("main", "x");
        modifiesTable.addVarP("main", "y");
        modifiesTable.addVarP("foo", "z");
        modifiesTable.addVarP("foo", "x");
        modifiesTable.addVarP("foo", "abc");

        std::unordered_set<std::string> expectedVarsModifiedByMain = {"x", "y"};
        std::unordered_set<std::string> expectedVarsModifiedByFoo = {"x", "z", "abc"};

        REQUIRE(modifiesTable.getVarsByProc("main") == expectedVarsModifiedByMain);
        REQUIRE(modifiesTable.getVarsByProc("foo") == expectedVarsModifiedByFoo);
    }

    SECTION("Getting procedures modifies a var works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarP("main", "x");
        modifiesTable.addVarP("foo", "x");
        modifiesTable.addVarP("bar", "y");

        std::unordered_set<std::string> expectedProcsModifyingX = {"main", "foo"};
        std::unordered_set<std::string> expectedProcsModifyingY = {"bar"};

        REQUIRE(modifiesTable.getProcsByVar("x") == expectedProcsModifyingX);
        REQUIRE(modifiesTable.getProcsByVar("y") == expectedProcsModifyingY);
    }

    SECTION("Getting modified vars in procedures works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarP("main", "x");
        modifiesTable.addVarP("main", "y");
        modifiesTable.addVarP("foo", "z");

        std::unordered_set<std::string> expectedModifiedVarsInProcs = {"x", "y", "z"};

        REQUIRE(modifiesTable.getVarsInProcs() == expectedModifiedVarsInProcs);
    }

    SECTION("Getting procedures that modify some var works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarP("main", "x");
        modifiesTable.addVarP("foo", "x");
        modifiesTable.addVarP("bar", "y");

        std::unordered_set<std::string> expectedProcsModifyingSomeVar = {"main", "foo", "bar"};

        REQUIRE(modifiesTable.getProcs() == expectedProcsModifyingSomeVar);
    }

    SECTION("Checking if proc modifies var works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarP("main", "x");
        modifiesTable.addVarP("foo", "x");
        modifiesTable.addVarP("bar", "y");

        REQUIRE(modifiesTable.isAssociatedP("main", "x"));
        REQUIRE(modifiesTable.isAssociatedP("foo", "x"));
        REQUIRE(modifiesTable.isAssociatedP("bar", "y"));
        REQUIRE_FALSE(modifiesTable.isAssociatedP("main", "y"));
        REQUIRE_FALSE(modifiesTable.isAssociatedP("foo", "y"));
        REQUIRE_FALSE(modifiesTable.isAssociatedP("bar", "x"));
    }

    SECTION("Checking if there exists proc modifies var works") {
        ModifiesTable modifiesTable;
        REQUIRE_FALSE(modifiesTable.hasAssociatedP());

        modifiesTable.addVarS(1, "x");
        REQUIRE_FALSE(modifiesTable.hasAssociatedP());

        modifiesTable.addVarP("proc", "abc");
        REQUIRE(modifiesTable.hasAssociatedP());
    }

    SECTION("Checking if there exists proc modifies var by key works") {
        ModifiesTable modifiesTable;
        REQUIRE_FALSE(modifiesTable.hasAssociatedPByKey("proc"));

        modifiesTable.addVarP("proc", "x");
        REQUIRE_FALSE(modifiesTable.hasAssociatedPByKey("bla"));
        REQUIRE(modifiesTable.hasAssociatedPByKey("proc"));
    }

    SECTION("Checking if there exists proc modifies var by key works") {
        ModifiesTable modifiesTable;
        REQUIRE_FALSE(modifiesTable.hasAssociatedPByValue("x"));

        modifiesTable.addVarP("proc", "x");
        REQUIRE_FALSE(modifiesTable.hasAssociatedPByValue("y"));
        REQUIRE(modifiesTable.hasAssociatedPByValue("x"));
    }

    SECTION("Adding proc-modifies-var relation works") {
        ModifiesTable modifiesTable;
        modifiesTable.addVarP("main", "x");
        modifiesTable.addVarP("foo", "x");

        REQUIRE(modifiesTable.getVarsByProc("main") == std::unordered_set<std::string>{"x"});
        REQUIRE(modifiesTable.getVarsByProc("foo") == std::unordered_set<std::string>{"x"});
        REQUIRE(modifiesTable.getProcsByVar("x") == std::unordered_set<std::string>{"main", "foo"});
    }
}

TEST_CASE("PKB: ModifiesTable statements negative test cases") {
    SECTION("Getting vars modified by stmt with invalid stmt number returns empty set") {
        ModifiesTable modifiesTable;
        REQUIRE(modifiesTable.getVarsByStmt(1).empty());
        REQUIRE(modifiesTable.getVarsByStmt(-1).empty());
    }

    SECTION("Getting stmts modifies var with invalid var name returns empty set") {
        ModifiesTable modifiesTable;
        REQUIRE(modifiesTable.getStmtsByVar("x").empty());
        REQUIRE(modifiesTable.getStmtsByVar("").empty());
    }

    SECTION("Checking if stmt modifies var with non-existent input returns false") {
        ModifiesTable modifiesTable;
        REQUIRE_FALSE(modifiesTable.isAssociatedS(1, "x"));
        REQUIRE_FALSE(modifiesTable.isAssociatedS(-1, "x"));
        REQUIRE_FALSE(modifiesTable.isAssociatedS(1, ""));
        REQUIRE_FALSE(modifiesTable.isAssociatedS(-1, ""));
    }
}

TEST_CASE("PKB: ModifiesTable procedures negative test cases") {
    SECTION("Getting vars modified by proc with non-existent proc name returns empty set") {
        ModifiesTable modifiesTable;
        REQUIRE(modifiesTable.getVarsByProc("1").empty());
        REQUIRE(modifiesTable.getVarsByProc("").empty());
    }

    SECTION("Getting procs modifies var with non-existent var name returns empty set") {
        ModifiesTable modifiesTable;
        REQUIRE(modifiesTable.getProcsByVar("x").empty());
        REQUIRE(modifiesTable.getProcsByVar("").empty());
    }

    SECTION("Checking if proc modifies var with non-existent input returns false") {
        ModifiesTable modifiesTable;
        REQUIRE_FALSE(modifiesTable.isAssociatedP("foo", "x"));
        REQUIRE_FALSE(modifiesTable.isAssociatedP("", "x"));
        REQUIRE_FALSE(modifiesTable.isAssociatedP("foo", ""));
        REQUIRE_FALSE(modifiesTable.isAssociatedP("", ""));
    }
}
