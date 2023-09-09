// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "catch.hpp"

#include <string>
#include <memory>
#include "pkb/PKB.h"
#include "di/DI.h"
#include "sp/node/VariableNode.h"

TEST_CASE("IAffects") {
    DI di;
    PKB pkb(di);
    INextAdder* nextAdder = &di.getService<INextAdder>();
    IModifiesAdder* modifiesAdder = &di.getService<IModifiesAdder>();
    IUsesAdder* usesAdder = &di.getService<IUsesAdder>();
    IStmtAdder* stmtAdder = &di.getService<IStmtAdder>();
    IParentAdder* parentAdder = &di.getService<IParentAdder>();
    IAffectsClearer* pkbClearer = &di.getService<IAffectsClearer>();
    IAffectsGetter* pkbGetter = &di.getService<IAffectsGetter>();

    parentAdder->addRelation(3, 4);
    parentAdder->addRelation(3, 5);
    parentAdder->addRelation(3, 6);
    parentAdder->addRelation(7, 8);
    parentAdder->addRelation(7, 9);

    nextAdder->addNext(1, 2);
    nextAdder->addNext(2, 3);
    nextAdder->addNext(3, 4);
    nextAdder->addNext(3, 7);
    nextAdder->addNext(4, 5);
    nextAdder->addNext(5, 6);
    nextAdder->addNext(6, 3);
    nextAdder->addNext(7, 8);
    nextAdder->addNext(7, 9);
    nextAdder->addNext(8, 10);
    nextAdder->addNext(9, 10);
    nextAdder->addNext(10, 11);
    nextAdder->addNext(11, 12);
    nextAdder->addNext(12, 13);
    nextAdder->addNext(14, 15);
    nextAdder->addNext(15, 16);

    modifiesAdder->addVarS(1, "x");
    modifiesAdder->addVarS(2, "i");
    modifiesAdder->addVarS(3, "x");
    modifiesAdder->addVarS(3, "z");
    modifiesAdder->addVarS(3, "v");
    modifiesAdder->addVarS(3, "i");
    modifiesAdder->addVarS(4, "x");
    modifiesAdder->addVarS(5, "z");
    modifiesAdder->addVarS(5, "v");
    modifiesAdder->addVarS(6, "i");
    modifiesAdder->addVarS(7, "x");
    modifiesAdder->addVarS(7, "z");
    modifiesAdder->addVarS(8, "x");
    modifiesAdder->addVarS(9, "z");
    modifiesAdder->addVarS(10, "z");
    modifiesAdder->addVarS(11, "y");
    modifiesAdder->addVarS(12, "y");
    modifiesAdder->addVarS(13, "x");
    modifiesAdder->addVarS(14, "z");
    modifiesAdder->addVarS(15, "v");

    usesAdder->addVarS(3, "i");
    usesAdder->addVarS(3, "x");
    usesAdder->addVarS(3, "y");
    usesAdder->addVarS(3, "z");
    usesAdder->addVarS(3, "v");
    usesAdder->addVarS(4, "x");
    usesAdder->addVarS(4, "y");
    usesAdder->addVarS(5, "z");
    usesAdder->addVarS(5, "v");
    usesAdder->addVarS(6, "i");
    usesAdder->addVarS(7, "x");
    usesAdder->addVarS(8, "x");
    usesAdder->addVarS(6, "i");
    usesAdder->addVarS(7, "x");
    usesAdder->addVarS(10, "i");
    usesAdder->addVarS(10, "x");
    usesAdder->addVarS(10, "z");
    usesAdder->addVarS(11, "z");
    usesAdder->addVarS(13, "x");
    usesAdder->addVarS(13, "y");
    usesAdder->addVarS(13, "z");
    usesAdder->addVarS(15, "z");
    usesAdder->addVarS(16, "v");

    stmtAdder->addAssignStmt(1);
    stmtAdder->addAssignStmt(2);
    stmtAdder->addAssignStmt(4);
    stmtAdder->addAssignStmt(6);
    stmtAdder->addAssignStmt(8);
    stmtAdder->addAssignStmt(9);
    stmtAdder->addAssignStmt(10);
    stmtAdder->addAssignStmt(11);
    stmtAdder->addAssignStmt(13);
    stmtAdder->addAssignStmt(14);
    stmtAdder->addAssignStmt(15);

    SECTION("Affects Entries") {
        pkbClearer->clearAffectsAndT();
        std::unordered_map<int, std::unordered_set<int>> expected = { {1, {4, 8, 10, 13} },
                                                                      {2, {6, 10} },
                                                                      {4, {4, 8, 10, 13} },
                                                                      {6, {6, 10} },
                                                                      {8, {10, 13} },
                                                                      {9, {10} },
                                                                      {10, {11, 13} },
                                                                      {14, {15} } };

        REQUIRE(pkbGetter->getAffectsEntries() == expected);
    }

    SECTION("AffectsT Entries") {
        pkbClearer->clearAffectsAndT();
        std::unordered_map<int, std::unordered_set<int>> expected = { {1, {4, 8, 10, 11, 13} },
                                                                      {2, {6, 10, 11, 13} },
                                                                      {4, {4, 8, 10, 11, 13} },
                                                                      {6, {6, 10, 11, 13} },
                                                                      {8, {10, 11, 13} },
                                                                      {9, {10, 11, 13} },
                                                                      {10, {11, 13} },
                                                                      {14, {15} } };

        REQUIRE(pkbGetter->getAffectsTEntries() == expected);
    }
}

TEST_CASE("IAssignPattern") {
    DI di;
    PKB pkb(di);
    IAssignPatternAdder* pkbAdder = &di.getService<IAssignPatternAdder>();
    IAssignPatternGetter* pkbGetter = &di.getService<IAssignPatternGetter>();

    SECTION("Assign Entries") {
        std::shared_ptr<VariableNode> ptr1 = std::make_shared<VariableNode>("x");
        std::shared_ptr<VariableNode> ptr2 = std::make_shared<VariableNode>("y");
        std::shared_ptr<VariableNode> ptr3 = std::make_shared<VariableNode>("z");
        pkbAdder->addAssignPattern(1, "a", ptr1);
        pkbAdder->addAssignPattern(2, "b", ptr2);
        pkbAdder->addAssignPattern(3, "c", ptr3);

        std::unordered_map<int, std::pair<std::string, std::shared_ptr<ExpressionNode>>> expected = {
                {1, {"a", ptr1}},
                {2, {"b", ptr2}},
                {3, {"c", ptr3}},
        };

        REQUIRE(pkbGetter->getAssignPatterns() == expected);
    }
}

TEST_CASE("ICalls") {
    DI di;
    PKB pkb(di);
    ICallsAdder* pkbAdder = &di.getService<ICallsAdder>();
    ICallsGetter* pkbGetter = &di.getService<ICallsGetter>();

    SECTION("Calls Entries") {
        pkbAdder->addCalls("foo", "bar");
        pkbAdder->addCalls("bar", "main");
        pkbAdder->addCalls("zig", "zag");

        std::unordered_map<std::string, std::unordered_set<std::string>> expected = {
                {"foo", {"bar"}},
                {"bar", {"main"}},
                {"zig", {"zag"}},
        };

        REQUIRE(pkbGetter->getCallsEntries() == expected);
    }

    SECTION("CallsT Entries") {
        pkbAdder->addCallsT("foo", "bar");
        pkbAdder->addCallsT("bar", "main");
        pkbAdder->addCallsT("foo", "main");
        pkbAdder->addCallsT("zig", "zag");

        std::unordered_map<std::string, std::unordered_set<std::string>> expected = {
                {"foo", {"bar", "main"}},
                {"bar", {"main"}},
                {"zig", {"zag"}},
        };

        REQUIRE(pkbGetter->getCallsTEntries() == expected);
    }
}

TEST_CASE("IConst") {
    DI di;
    PKB pkb(di);
    IConstAdder* pkbAdder = &di.getService<IConstAdder>();
    IConstGetter* pkbGetter = &di.getService<IConstGetter>();

    SECTION("Const Entries") {
        pkbAdder->addConst(1);
        pkbAdder->addConst(321);
        pkbAdder->addConst(20);
        pkbAdder->addConsts({4, 6, 8});

        std::unordered_set<int> expected = {1, 4, 6, 8, 20, 321};

        REQUIRE(pkbGetter->getConsts() == expected);
    }
}

TEST_CASE("IFollows") {
    DI di;
    PKB pkb(di);
    IFollowsAdder* pkbAdder = &di.getService<IFollowsAdder>();
    IFollowsGetter* pkbGetter = &di.getService<IFollowsGetter>();

    SECTION("Follows Entries") {
        pkbAdder->addRelation(1, 2);
        pkbAdder->addRelation(2, 3);
        pkbAdder->addRelation(4, 6);

        std::unordered_map<int, int> expected = {
                {1, 2},
                {2, 3},
                {4, 6},
        };

        REQUIRE(pkbGetter->getFollowsEntries() == expected);
    }

    SECTION("FollowsT Entries") {
        pkbAdder->addRelationT(1, 2);
        pkbAdder->addRelationT(2, 3);
        pkbAdder->addRelationT(1, 3);
        pkbAdder->addRelationT(4, 6);

        std::unordered_map<int, std::unordered_set<int>> expected = {
                {1, {2, 3}},
                {2, {3}},
                {4, {6}},
        };

        REQUIRE(pkbGetter->getTEntries() == expected);
    }
}

TEST_CASE("IIfPattern") {
    DI di;
    PKB pkb(di);
    IIfPatternAdder* pkbAdder = &di.getService<IIfPatternAdder>();
    IIfPatternGetter* pkbGetter = &di.getService<IIfPatternGetter>();

    SECTION("IfPattern Entries") {
        pkbAdder->addIfPattern(1, {"x", "y"});
        pkbAdder->addIfPattern(2, {"a", "b"});
        pkbAdder->addIfPattern(3, {"y", "a"});

        std::unordered_map<int, std::unordered_set<std::string>> expected = {
                {1, {"x", "y"}},
                {2, {"a", "b"}},
                {3, {"y", "a"}},
        };

        REQUIRE(pkbGetter->getStmtVarEntries() == expected);
    }
}

TEST_CASE("IModifies") {
    DI di;
    PKB pkb(di);
    IModifiesAdder* pkbAdder = &di.getService<IModifiesAdder>();
    IModifiesGetter* pkbGetter = &di.getService<IModifiesGetter>();

    SECTION("ModifiesS Entries") {
        pkbAdder->addVarS(1, "x");
        pkbAdder->addVarS(1, "y");
        pkbAdder->addVarS(2, "y");
        pkbAdder->addVarS(4, "z");

        std::unordered_map<int, std::unordered_set<std::string>> expected = {
                {1, {"x", "y"}},
                {2, {"y"}},
                {4, {"z"}},
        };

        REQUIRE(pkbGetter->getStmtVarEntries() == expected);
    }

    SECTION("ModifiesP Entries") {
        pkbAdder->addVarP("foo", "x");
        pkbAdder->addVarP("bar", "x");
        pkbAdder->addVarP("foo", "y");
        pkbAdder->addVarP("main", "z");

        std::unordered_map<std::string, std::unordered_set<std::string>> expected = {
                {"foo", {"x", "y"}},
                {"bar", {"x"}},
                {"main", {"z"}},
        };

        REQUIRE(pkbGetter->getProcVarEntries() == expected);
    }
}

TEST_CASE("INext") {
    DI di;
    PKB pkb(di);
    INextAdder* pkbAdder = &di.getService<INextAdder>();
    INextGetter* pkbGetter = &di.getService<INextGetter>();
    INextTClearer* pkbClearer = &di.getService<INextTClearer>();

    SECTION("Next Entries") {
        pkbClearer->clearNextT();
        pkbAdder->addNext(1, 2);
        pkbAdder->addNext(1, 3);
        pkbAdder->addNext(1, 4);
        pkbAdder->addNext(2, 3);
        pkbAdder->addNext(2, 4);
        pkbAdder->addNext(2, 5);
        pkbAdder->addNext(3, 6);

        std::unordered_map<int, std::unordered_set<int>> expected = {
                {1, std::unordered_set<int>{2, 3, 4}},
                {2, std::unordered_set<int>{3, 4, 5}},
                {3, std::unordered_set<int>{6}}
        };

        REQUIRE(pkbGetter->getNextEntries() == expected);
    }

    SECTION("NextT Entries") {
        pkbClearer->clearNextT();
        pkbAdder->addNext(1, 2);
        pkbAdder->addNext(1, 3);
        pkbAdder->addNext(1, 4);
        pkbAdder->addNext(2, 3);
        pkbAdder->addNext(2, 4);
        pkbAdder->addNext(2, 5);
        pkbAdder->addNext(3, 6);

        std::unordered_map<int, std::unordered_set<int>> expected = {
                {1, std::unordered_set<int>{2, 3, 4, 5, 6}},
                {2, std::unordered_set<int>{3, 4, 5, 6}},
                {3, std::unordered_set<int>{6}}
        };

        REQUIRE(pkbGetter->getNextTEntries() == expected);
    }
}

TEST_CASE("IParent") {
    DI di;
    PKB pkb(di);
    IParentAdder* pkbAdder = &di.getService<IParentAdder>();
    IParentGetter* pkbGetter = &di.getService<IParentGetter>();

    SECTION("Parent Entries") {
        pkbAdder->addRelation(1, 2);
        pkbAdder->addRelation(2, 3);
        pkbAdder->addRelation(4, 6);

        std::unordered_map<int, std::unordered_set<int>> expected = {
                {1, {2}},
                {2, {3}},
                {4, {6}},
        };

        REQUIRE(pkbGetter->getParentEntries() == expected);
    }

    SECTION("ParentT Entries") {
        pkbAdder->addRelationT(1, 2);
        pkbAdder->addRelationT(2, 3);
        pkbAdder->addRelationT(1, 3);
        pkbAdder->addRelationT(4, 6);

        std::unordered_map<int, std::unordered_set<int>> expected = {
                {1, {2, 3}},
                {2, {3}},
                {4, {6}},
        };

        REQUIRE(pkbGetter->getTEntries() == expected);
    }
}

TEST_CASE("IProc") {
    DI di;
    PKB pkb(di);
    IProcAdder* pkbAdder = &di.getService<IProcAdder>();
    IProcGetter* pkbGetter = &di.getService<IProcGetter>();

    SECTION("Proc Entries") {
        pkbAdder->addProc("main");
        pkbAdder->addProc("foo");
        pkbAdder->addProc("bar");
        pkbAdder->addProcs({"zig", "zag"});

        std::unordered_set<std::string> expected = {
                "main", "foo", "bar", "zig", "zag"
        };

        REQUIRE(pkbGetter->getProcs() == expected);
    }
}

TEST_CASE("IStmt") {
    DI di;
    PKB pkb(di);
    IStmtAdder* pkbAdder = &di.getService<IStmtAdder>();
    IStmtGetter* pkbGetter = &di.getService<IStmtGetter>();

    SECTION("Stmt Entries") {
        pkbAdder->addReadStmt(1, "x");
        pkbAdder->addPrintStmt(2, "y");
        pkbAdder->addAssignStmt(3);
        pkbAdder->addCallStmt(4, "z");
        pkbAdder->addWhileStmt(5);
        pkbAdder->addIfStmt(6);

        std::unordered_set<int> expected = {
                1, 2, 3, 4, 5, 6
        };

        REQUIRE(pkbGetter->getAllStmts() == expected);
    }
}

TEST_CASE("IUses") {
    DI di;
    PKB pkb(di);
    IUsesAdder* pkbAdder = &di.getService<IUsesAdder>();
    IUsesGetter* pkbGetter = &di.getService<IUsesGetter>();

    SECTION("UsesS Entries") {
        pkbAdder->addVarS(1, "x");
        pkbAdder->addVarS(1, "y");
        pkbAdder->addVarS(2, "y");
        pkbAdder->addVarS(4, "z");

        std::unordered_map<int, std::unordered_set<std::string>> expected = {
                {1, {"x", "y"}},
                {2, {"y"}},
                {4, {"z"}},
        };

        REQUIRE(pkbGetter->getStmtVarEntries() == expected);
    }

    SECTION("UsesP Entries") {
        pkbAdder->addVarP("foo", "x");
        pkbAdder->addVarP("bar", "x");
        pkbAdder->addVarP("foo", "y");
        pkbAdder->addVarP("main", "z");

        std::unordered_map<std::string, std::unordered_set<std::string>> expected = {
                {"foo", {"x", "y"}},
                {"bar", {"x"}},
                {"main", {"z"}},
        };

        REQUIRE(pkbGetter->getProcVarEntries() == expected);
    }
}

TEST_CASE("IVar") {
    DI di;
    PKB pkb(di);
    IVarAdder* pkbAdder = &di.getService<IVarAdder>();
    IVarGetter* pkbGetter = &di.getService<IVarGetter>();

    SECTION("Var Entries") {
        pkbAdder->addVar("x");
        pkbAdder->addVar("y");
        pkbAdder->addVar("z");
        pkbAdder->addVars({"a", "b"});

        std::unordered_set<std::string> expected = {
                "x", "y", "z", "a", "b"
        };

        REQUIRE(pkbGetter->getVars() == expected);
    }
}

TEST_CASE("IWhilePattern") {
    DI di;
    PKB pkb(di);
    IWhilePatternAdder* pkbAdder = &di.getService<IWhilePatternAdder>();
    IWhilePatternGetter* pkbGetter = &di.getService<IWhilePatternGetter>();

    SECTION("WhilePattern Entries") {
        pkbAdder->addWhilePattern(1, {"x", "y"});
        pkbAdder->addWhilePattern(2, {"a", "b"});
        pkbAdder->addWhilePattern(3, {"y", "a"});

        std::unordered_map<int, std::unordered_set<std::string>> expected = {
                {1, {"x", "y"}},
                {2, {"a", "b"}},
                {3, {"y", "a"}},
        };

        REQUIRE(pkbGetter->getStmtVarEntries() == expected);
    }
}
