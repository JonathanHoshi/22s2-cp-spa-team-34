#include <unordered_map>
#include <unordered_set>
#include "catch.hpp"
#include "pkb/tables/AffectsTable.h"
#include "pkb/tables/NextTable.h"
#include "pkb/tables/ModifiesTable.h"
#include "pkb/tables/UsesTable.h"
#include "pkb/tables/ParentTable.h"
#include "pkb/tables/StmtTable.h"

namespace affectsTest {
    std::shared_ptr<NextTable> nextTable;
    std::shared_ptr<ModifiesTable> modifiesTable;
    std::shared_ptr<UsesTable> usesTable;
    std::shared_ptr<ParentTable> parentTable;
    std::shared_ptr<StmtTable> stmtTable;

    void initializeParent() {
        parentTable = std::make_shared<ParentTable>();
        parentTable->addRelation(3, 4);
        parentTable->addRelation(3, 5);
        parentTable->addRelation(3, 6);
        parentTable->addRelation(7, 8);
        parentTable->addRelation(7, 9);
    }

    void initializeNext() {
        nextTable = std::make_shared<NextTable>();
        nextTable->addNext(1, 2);
        nextTable->addNext(2, 3);
        nextTable->addNext(3, 4);
        nextTable->addNext(3, 7);
        nextTable->addNext(4, 5);
        nextTable->addNext(5, 6);
        nextTable->addNext(6, 3);
        nextTable->addNext(7, 8);
        nextTable->addNext(7, 9);
        nextTable->addNext(8, 10);
        nextTable->addNext(9, 10);
        nextTable->addNext(10, 11);
        nextTable->addNext(11, 12);
        nextTable->addNext(12, 13);
        nextTable->addNext(14, 15);
        nextTable->addNext(15, 16);
    }

    void initializeModifies() {
        modifiesTable = std::make_shared<ModifiesTable>();
        modifiesTable->addVarS(1, "x");
        modifiesTable->addVarS(2, "i");
        modifiesTable->addVarS(3, "x");
        modifiesTable->addVarS(3, "z");
        modifiesTable->addVarS(3, "v");
        modifiesTable->addVarS(3, "i");
        modifiesTable->addVarS(4, "x");
        modifiesTable->addVarS(5, "z");
        modifiesTable->addVarS(5, "v");
        modifiesTable->addVarS(6, "i");
        modifiesTable->addVarS(7, "x");
        modifiesTable->addVarS(7, "z");
        modifiesTable->addVarS(8, "x");
        modifiesTable->addVarS(9, "z");
        modifiesTable->addVarS(10, "z");
        modifiesTable->addVarS(11, "y");
        modifiesTable->addVarS(12, "y");
        modifiesTable->addVarS(13, "x");
        modifiesTable->addVarS(14, "z");
        modifiesTable->addVarS(15, "v");
    }

    void initializeUses() {
        usesTable = std::make_shared<UsesTable>();
        usesTable->addVarS(3, "i");
        usesTable->addVarS(3, "x");
        usesTable->addVarS(3, "y");
        usesTable->addVarS(3, "z");
        usesTable->addVarS(3, "v");
        usesTable->addVarS(4, "x");
        usesTable->addVarS(4, "y");
        usesTable->addVarS(5, "z");
        usesTable->addVarS(5, "v");
        usesTable->addVarS(6, "i");
        usesTable->addVarS(7, "x");
        usesTable->addVarS(8, "x");
        usesTable->addVarS(6, "i");
        usesTable->addVarS(7, "x");
        usesTable->addVarS(10, "i");
        usesTable->addVarS(10, "x");
        usesTable->addVarS(10, "z");
        usesTable->addVarS(11, "z");
        usesTable->addVarS(13, "x");
        usesTable->addVarS(13, "y");
        usesTable->addVarS(13, "z");
        usesTable->addVarS(15, "z");
        usesTable->addVarS(16, "v");
    }

    void initializeStmts() {
        stmtTable = std::make_shared<StmtTable>();
        stmtTable->addAssignStmt(1);
        stmtTable->addAssignStmt(2);
        stmtTable->addAssignStmt(4);
        stmtTable->addAssignStmt(6);
        stmtTable->addAssignStmt(8);
        stmtTable->addAssignStmt(9);
        stmtTable->addAssignStmt(10);
        stmtTable->addAssignStmt(11);
        stmtTable->addAssignStmt(13);
        stmtTable->addAssignStmt(14);
        stmtTable->addAssignStmt(15);
    }

    void initialize() {
        initializeNext();
        initializeModifies();
        initializeUses();
        initializeStmts();
        initializeParent();
    }
}

using namespace affectsTest;

TEST_CASE("Affects methods call functionality test - ok - expected value") {
    initialize();
    AffectsTable table(*modifiesTable, *usesTable, *nextTable, *parentTable, *stmtTable);

    SECTION("Direct affects") {
        std::unordered_set<int> affectedSet = { 4, 8, 10, 13 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(1) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 6, 10 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(2) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(3) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 4, 8, 10, 13 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(4) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(5) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 6, 10 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(6) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(7) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 10, 13 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(8) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 10 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(9) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 11, 13 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(10) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(11) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(12) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(13) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 15 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(14) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(15) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(16) == affectedSet);
        table.clearAffectsAndT();
    }

    SECTION("Direct affects without clear") {
        std::unordered_set<int> affectedSet = { 4, 8, 10, 13 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(1) == affectedSet);
        affectedSet = { 6, 10 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(2) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(3) == affectedSet);
        affectedSet = { 4, 8, 10, 13 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(4) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(5) == affectedSet);
        affectedSet = { 6, 10 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(6) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(7) == affectedSet);
        affectedSet = { 10, 13 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(8) == affectedSet);
        affectedSet = { 10 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(9) == affectedSet);
        affectedSet = { 11, 13 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(10) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(11) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(12) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(13) == affectedSet);
        affectedSet = { 15 };
        REQUIRE(table.getAffectedStmtsByKeyStmt(14) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(15) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getAffectedStmtsByKeyStmt(16) == affectedSet);
    }

    table.clearAffectsAndT();

    SECTION("Direct affected") {
        std::unordered_set<int> affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(1) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(2) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(3) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 1, 4 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(4) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(5) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 2, 6 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(6) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(7) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 4, 1 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(8) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(9) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 8, 4, 1, 9, 6, 2 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(10) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 10 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(11) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(12) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 10, 8, 4, 1 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(13) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(14) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 14 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(15) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(16) == affectedSet);
        table.clearAffectsAndT();
    }

    SECTION("Direct affected without clear") {
        std::unordered_set<int> affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(1) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(2) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(3) == affectedSet);
        affectedSet = { 1, 4 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(4) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(5) == affectedSet);
        affectedSet = { 2, 6 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(6) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(7) == affectedSet);
        affectedSet = { 4, 1 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(8) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(9) == affectedSet);
        affectedSet = { 8, 4, 1, 9, 6, 2 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(10) == affectedSet);
        affectedSet = { 10 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(11) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(12) == affectedSet);
        affectedSet = { 10, 8, 4, 1 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(13) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(14) == affectedSet);
        affectedSet = { 14 };
        REQUIRE(table.getKeyStmtsByAffectedStmt(15) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getKeyStmtsByAffectedStmt(16) == affectedSet);
    }

    table.clearAffectsAndT();

    SECTION("Direct affectsT") {
        std::unordered_set<int> affectedSet = { 4, 8, 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(1) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 6, 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(2) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(3) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 4, 8, 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(4) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(5) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 6, 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(6) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(7) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(8) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(9) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(10) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(11) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(12) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(13) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 15 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(14) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(15) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(16) == affectedSet);
        table.clearAffectsAndT();
    }

    SECTION("Direct affectsT without clear") {
        std::unordered_set<int> affectedSet = { 4, 8, 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(1) == affectedSet);
        affectedSet = { 6, 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(2) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(3) == affectedSet);
        affectedSet = { 4, 8, 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(4) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(5) == affectedSet);
        affectedSet = { 6, 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(6) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(7) == affectedSet);
        affectedSet = { 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(8) == affectedSet);
        affectedSet = { 10, 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(9) == affectedSet);
        affectedSet = { 11, 13 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(10) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(11) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(12) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(13) == affectedSet);
        affectedSet = { 15 };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(14) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(15) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(16) == affectedSet);
    }

    table.clearAffectsAndT();

    SECTION("Direct affectedT") {
        std::unordered_set<int> affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(1) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(2) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(3) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 1, 4 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(4) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(5) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 2, 6 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(6) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(7) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 1, 4 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(8) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(9) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 1, 2, 4, 6, 8, 9 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(10) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 1, 2, 4, 6, 8, 9, 10 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(11) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(12) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 1, 2, 4, 6, 8, 9, 10 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(13) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(14) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { 14 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(15) == affectedSet);
        table.clearAffectsAndT();
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(16) == affectedSet);
        table.clearAffectsAndT();
    }

    SECTION("Direct affectedT") {
        std::unordered_set<int> affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(1) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(2) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(3) == affectedSet);
        affectedSet = { 1, 4 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(4) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(5) == affectedSet);
        affectedSet = { 2, 6 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(6) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(7) == affectedSet);
        affectedSet = { 1, 4 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(8) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(9) == affectedSet);
        affectedSet = { 1, 2, 4, 6, 8, 9 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(10) == affectedSet);
        affectedSet = { 1, 2, 4, 6, 8, 9, 10 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(11) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTAffectedStmtsByKeyStmt(12) == affectedSet);
        affectedSet = { 1, 2, 4, 6, 8, 9, 10 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(13) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(14) == affectedSet);
        affectedSet = { 14 };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(15) == affectedSet);
        affectedSet = { };
        REQUIRE(table.getTKeyStmtsByAffectedStmt(16) == affectedSet);
    }

    table.clearAffectsAndT();

    SECTION("Has affects positive") {
        REQUIRE(table.hasAffects());
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByKeyStmt(1));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByKeyStmt(2));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByKeyStmt(4));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByKeyStmt(6));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByKeyStmt(8));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByKeyStmt(9));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByKeyStmt(10));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByKeyStmt(14));
        table.clearAffectsAndT();
    }

    SECTION("Has affects positive without clear") {
        REQUIRE(table.hasAffects());
        REQUIRE(table.hasAffectsByKeyStmt(1));
        REQUIRE(table.hasAffectsByKeyStmt(2));
        REQUIRE(table.hasAffectsByKeyStmt(4));
        REQUIRE(table.hasAffectsByKeyStmt(6));
        REQUIRE(table.hasAffectsByKeyStmt(8));
        REQUIRE(table.hasAffectsByKeyStmt(9));
        REQUIRE(table.hasAffectsByKeyStmt(10));
        REQUIRE(table.hasAffectsByKeyStmt(14));
    }

    table.clearAffectsAndT();

    SECTION("Has affects negative") {
        std::shared_ptr<ParentTable> emptyParentTable = std::make_shared<ParentTable>();
        std::shared_ptr<ModifiesTable> emptyModifiesTable = std::make_shared<ModifiesTable>();
        std::shared_ptr<UsesTable> emptyUsesTable = std::make_shared<UsesTable>();
        std::shared_ptr<StmtTable> emptyStmtTable = std::make_shared<StmtTable>();
        std::shared_ptr<NextTable> emptyNextTable = std::make_shared<NextTable>();
        AffectsTable emptyTable(*emptyModifiesTable, *emptyUsesTable, *emptyNextTable, *emptyParentTable, *emptyStmtTable);
        REQUIRE_FALSE(emptyTable.hasAffects());
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(3));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(5));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(7));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(11));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(12));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(13));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(15));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(16));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(17));
        table.clearAffectsAndT();
    }

    SECTION("Has affects negative without clear") {
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(3));
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(5));
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(7));
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(11));
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(12));
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(13));
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(15));
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(16));
        REQUIRE_FALSE(table.hasAffectsByKeyStmt(17));
    }

    table.clearAffectsAndT();

    SECTION("Has affected positive") {
        REQUIRE(table.hasAffectsByAffectedStmt(4));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByAffectedStmt(6));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByAffectedStmt(8));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByAffectedStmt(10));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByAffectedStmt(11));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByAffectedStmt(13));
        table.clearAffectsAndT();
        REQUIRE(table.hasAffectsByAffectedStmt(15));
        table.clearAffectsAndT();
    }

    SECTION("Has affected positive without clear") {
        REQUIRE(table.hasAffectsByAffectedStmt(4));
        REQUIRE(table.hasAffectsByAffectedStmt(6));
        REQUIRE(table.hasAffectsByAffectedStmt(8));
        REQUIRE(table.hasAffectsByAffectedStmt(10));
        REQUIRE(table.hasAffectsByAffectedStmt(11));
        REQUIRE(table.hasAffectsByAffectedStmt(13));
        REQUIRE(table.hasAffectsByAffectedStmt(15));
    }

    table.clearAffectsAndT();

    SECTION("Has affected negative") {
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(1));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(2));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(3));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(5));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(7));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(9));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(12));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(14));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(16));
        table.clearAffectsAndT();
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(17));
        table.clearAffectsAndT();
    }

    SECTION("Has affected negative without clear") {
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(1));
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(2));
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(3));
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(5));
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(7));
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(9));
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(12));
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(14));
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(16));
        REQUIRE_FALSE(table.hasAffectsByAffectedStmt(17));
    }

    table.clearAffectsAndT();
    
    SECTION("Is affects positive") {
        REQUIRE(table.isAffects(1, 4));
        REQUIRE(table.isAffects(1, 8));
        REQUIRE(table.isAffects(2, 6));
        REQUIRE(table.isAffects(2, 10));
        REQUIRE(table.isAffects(4, 4));
    }

    table.clearAffectsAndT();

    SECTION("Is affects negative") {
        REQUIRE_FALSE(table.isAffects(1, 11));
        REQUIRE_FALSE(table.isAffects(8, 8));
    }

    table.clearAffectsAndT();

    SECTION("Is affects positive after precomputation") {
        table.getAffectsEntries();
        REQUIRE(table.isAffects(1, 4));
        REQUIRE(table.isAffects(1, 8));
        REQUIRE(table.isAffects(2, 6));
        REQUIRE(table.isAffects(2, 10));
        REQUIRE(table.isAffects(4, 4));
    }

    table.clearAffectsAndT();

    SECTION("Is affects negative after precomputation") {
        table.getAffectsEntries();
        REQUIRE_FALSE(table.isAffects(1, 11));
        REQUIRE_FALSE(table.isAffects(8, 8));
    }

    table.clearAffectsAndT();

    SECTION("Is affectsT positive") {
        REQUIRE(table.isAffectsT(1, 4));
        REQUIRE(table.isAffectsT(1, 8));
        REQUIRE(table.isAffectsT(1, 11));
        REQUIRE(table.isAffectsT(2, 6));
        REQUIRE(table.isAffectsT(2, 10));
        REQUIRE(table.isAffectsT(4, 4));
    }

    table.clearAffectsAndT();

    SECTION("Is affectsT negative") {
        REQUIRE_FALSE(table.isAffectsT(8, 8));
    }

    table.clearAffectsAndT();

    SECTION("Is affectsT positive after precomputation") {
        table.getAffectsEntries();
        REQUIRE(table.isAffectsT(1, 4));
        REQUIRE(table.isAffectsT(1, 8));
        REQUIRE(table.isAffectsT(1, 11));
        REQUIRE(table.isAffectsT(2, 6));
        REQUIRE(table.isAffectsT(2, 10));
        REQUIRE(table.isAffectsT(4, 4));
    }

    table.clearAffectsAndT();

    SECTION("Is affectsT negative after precomputation") {
        table.getAffectsEntries();
        REQUIRE_FALSE(table.isAffectsT(8, 8));
    }

    table.clearAffectsAndT();

    SECTION("Get all affects/T entries") {
        table.clearAffectsAndT();
        std::unordered_map<int, std::unordered_set<int>> affectsCompTable = { {1, {4, 8, 10, 13} },
                     {2, {6, 10} },
                     {4, {4, 8, 10, 13} },
                     {6, {6, 10} },
                     {8, {10, 13} },
                     {9, {10} },
                     {10, {11, 13} },
                     {14, {15} } };
        REQUIRE(affectsCompTable == table.getAffectsEntries());
        table.clearAffectsAndT();
        std::unordered_map<int, std::unordered_set<int>> affectsTCompTable = { {1, {4, 8, 10, 11, 13} },
                     {2, {6, 10, 11, 13} },
                     {4, {4, 8, 10, 11, 13} },
                     {6, {6, 10, 11, 13} },
                     {8, {10, 11, 13} },
                     {9, {10, 11, 13} },
                     {10, {11, 13} },
                     {14, {15} } };
        std::unordered_map<int, std::unordered_set<int>> affectsTCompTable2 = table.getAffectsTEntries();
        REQUIRE(affectsTCompTable == table.getAffectsTEntries());
    }
}