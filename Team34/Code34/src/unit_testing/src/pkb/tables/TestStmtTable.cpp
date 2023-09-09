#include "catch.hpp"
#include "pkb/tables/StmtTable.h"



TEST_CASE("PKB: StmtTable") {
    SECTION("Test empty getAllStmts") {
        StmtTable stmtTable;
        REQUIRE(stmtTable.getAllStmts().empty());
    }

    SECTION("Test empty getReadStmts") {
        StmtTable stmtTable;
        REQUIRE(stmtTable.getReadStmts().empty());
        REQUIRE_FALSE(stmtTable.isReadStmt(1));
    }

    SECTION("Test empty getPrintStmts") {
        StmtTable stmtTable;
        REQUIRE(stmtTable.getPrintStmts().empty());
        REQUIRE_FALSE(stmtTable.isPrintStmt(1));
    }

    SECTION("Test empty getAssignStmts") {
        StmtTable stmtTable;
        REQUIRE(stmtTable.getAssignStmts().empty());
        REQUIRE_FALSE(stmtTable.isAssignStmt(1));
    }

    SECTION("Test empty getCallStmts") {
        StmtTable stmtTable;
        REQUIRE(stmtTable.getCallStmts().empty());
        REQUIRE_FALSE(stmtTable.isCallStmt(1));
    }

    SECTION("Test empty getWhileStmts") {
        StmtTable stmtTable;
        REQUIRE(stmtTable.getWhileStmts().empty());
        REQUIRE_FALSE(stmtTable.isWhileStmt(1));
    }

    SECTION("Test empty getIfStmts") {
        StmtTable stmtTable;
        REQUIRE(stmtTable.getIfStmts().empty());
        REQUIRE_FALSE(stmtTable.isIfStmt(1));
    }

    SECTION("Test addReadStmt") {
        StmtTable stmtTable;
        stmtTable.addReadStmt(1, "x");
        REQUIRE(stmtTable.isReadStmt(1));
        REQUIRE_FALSE(stmtTable.isReadStmt(2));
    }

    SECTION("Test addPrintStmt") {
        StmtTable stmtTable;
        stmtTable.addPrintStmt(2, "y");
        REQUIRE(stmtTable.isPrintStmt(2));
        REQUIRE_FALSE(stmtTable.isPrintStmt(1));
    }

    SECTION("Test addAssignStmt") {
        StmtTable stmtTable;
        stmtTable.addAssignStmt(3);
        REQUIRE(stmtTable.isAssignStmt(3));
        REQUIRE_FALSE(stmtTable.isAssignStmt(4));
    }

    SECTION("Test addCallStmt") {
        StmtTable stmtTable;
        stmtTable.addCallStmt(4, "z");
        REQUIRE(stmtTable.isCallStmt(4));
        REQUIRE_FALSE(stmtTable.isCallStmt(5));
    }

    SECTION("Test addWhileStmt") {
        StmtTable stmtTable;
        stmtTable.addWhileStmt(5);
        REQUIRE(stmtTable.isWhileStmt(5));
        REQUIRE_FALSE(stmtTable.isWhileStmt(6));
    }

    SECTION("Test addIfStmt") {
        StmtTable stmtTable;
        stmtTable.addIfStmt(6);
        REQUIRE(stmtTable.isIfStmt(6));
        REQUIRE_FALSE(stmtTable.isIfStmt(7));
    }

    SECTION("Test getAllStmts") {
        StmtTable stmtTable;
        stmtTable.addReadStmt(1, "x");
        stmtTable.addPrintStmt(2, "y");
        stmtTable.addAssignStmt(3);
        stmtTable.addCallStmt(4, "z");
        stmtTable.addWhileStmt(5);
        stmtTable.addIfStmt(6);

        std::unordered_set<int> allStmts = stmtTable.getAllStmts();
        REQUIRE(allStmts.size() == 6);
        REQUIRE(allStmts.count(1) == 1);
        REQUIRE(allStmts.count(2) == 1);
        REQUIRE(allStmts.count(3) == 1);
        REQUIRE(allStmts.count(4) == 1);
        REQUIRE(allStmts.count(5) == 1);
        REQUIRE(allStmts.count(6) == 1);
        REQUIRE_FALSE(allStmts.count(7) == 1);
    }

    SECTION("Test isReadStmt") {
        StmtTable stmtTable;
        stmtTable.addReadStmt(1, "x");
        stmtTable.addPrintStmt(2, "y");
        stmtTable.addAssignStmt(3);
        stmtTable.addCallStmt(4, "z");
        stmtTable.addWhileStmt(5);
        stmtTable.addIfStmt(6);

        REQUIRE(stmtTable.isReadStmt(1));
        REQUIRE_FALSE(stmtTable.isReadStmt(2));
        REQUIRE_FALSE(stmtTable.isReadStmt(3));
        REQUIRE_FALSE(stmtTable.isReadStmt(4));
        REQUIRE_FALSE(stmtTable.isReadStmt(5));
        REQUIRE_FALSE(stmtTable.isReadStmt(6));
    }

    SECTION("Test isPrintStmt") {
        StmtTable stmtTable;
        stmtTable.addReadStmt(1, "x");
        stmtTable.addPrintStmt(2, "y");
        stmtTable.addAssignStmt(3);
        stmtTable.addCallStmt(4, "z");
        stmtTable.addWhileStmt(5);
        stmtTable.addIfStmt(6);

        REQUIRE_FALSE(stmtTable.isPrintStmt(1));
        REQUIRE(stmtTable.isPrintStmt(2));
        REQUIRE_FALSE(stmtTable.isPrintStmt(3));
        REQUIRE_FALSE(stmtTable.isPrintStmt(4));
        REQUIRE_FALSE(stmtTable.isPrintStmt(5));
        REQUIRE_FALSE(stmtTable.isPrintStmt(6));
    }

    SECTION("Test isAssignStmt") {
        StmtTable stmtTable;
        stmtTable.addReadStmt(1, "x");
        stmtTable.addPrintStmt(2, "y");
        stmtTable.addAssignStmt(3);
        stmtTable.addCallStmt(4, "z");
        stmtTable.addWhileStmt(5);
        stmtTable.addIfStmt(6);

        REQUIRE_FALSE(stmtTable.isAssignStmt(1));
        REQUIRE_FALSE(stmtTable.isAssignStmt(2));
        REQUIRE(stmtTable.isAssignStmt(3));
        REQUIRE_FALSE(stmtTable.isAssignStmt(4));
        REQUIRE_FALSE(stmtTable.isAssignStmt(5));
        REQUIRE_FALSE(stmtTable.isAssignStmt(6));
    }

    SECTION("Test isCallStmt") {
        StmtTable stmtTable;
        stmtTable.addReadStmt(1, "x");
        stmtTable.addPrintStmt(2, "y");
        stmtTable.addAssignStmt(3);
        stmtTable.addCallStmt(4, "z");
        stmtTable.addWhileStmt(5);
        stmtTable.addIfStmt(6);

        REQUIRE_FALSE(stmtTable.isCallStmt(1));
        REQUIRE_FALSE(stmtTable.isCallStmt(2));
        REQUIRE_FALSE(stmtTable.isCallStmt(3));
        REQUIRE(stmtTable.isCallStmt(4));
        REQUIRE_FALSE(stmtTable.isCallStmt(5));
        REQUIRE_FALSE(stmtTable.isCallStmt(6));
    }

    SECTION("Test isWhileStmt") {
        StmtTable stmtTable;
        stmtTable.addReadStmt(1, "x");
        stmtTable.addPrintStmt(2, "y");
        stmtTable.addAssignStmt(3);
        stmtTable.addCallStmt(4, "z");
        stmtTable.addWhileStmt(5);
        stmtTable.addIfStmt(6);

        REQUIRE_FALSE(stmtTable.isWhileStmt(1));
        REQUIRE_FALSE(stmtTable.isWhileStmt(2));
        REQUIRE_FALSE(stmtTable.isWhileStmt(3));
        REQUIRE_FALSE(stmtTable.isWhileStmt(4));
        REQUIRE(stmtTable.isWhileStmt(5));
        REQUIRE_FALSE(stmtTable.isWhileStmt(6));
    }

    SECTION("Test isIfStmt") {
        StmtTable stmtTable;
        stmtTable.addReadStmt(1, "x");
        stmtTable.addPrintStmt(2, "y");
        stmtTable.addAssignStmt(3);
        stmtTable.addCallStmt(4, "z");
        stmtTable.addWhileStmt(5);
        stmtTable.addIfStmt(6);

        REQUIRE_FALSE(stmtTable.isIfStmt(1));
        REQUIRE_FALSE(stmtTable.isIfStmt(2));
        REQUIRE_FALSE(stmtTable.isIfStmt(3));
        REQUIRE_FALSE(stmtTable.isIfStmt(4));
        REQUIRE_FALSE(stmtTable.isIfStmt(5));
        REQUIRE(stmtTable.isIfStmt(6));
    }
}