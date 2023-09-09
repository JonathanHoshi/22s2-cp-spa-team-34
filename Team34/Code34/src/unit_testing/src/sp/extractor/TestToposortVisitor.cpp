#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"
#include "sp/extractor/TopologicalSortVisitor.h"
#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"

#include "sp/node/CallNode.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/RootNode.h"
#include "common/exceptions/ParserError.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>


TEST_CASE("Test Recursive calls - Exception - Extractor throws exception") {

    TopologicalSortVisitor visitor;

    SECTION("Recurcive Procedure") {
        std::shared_ptr<RootNode> root = std::make_shared<RootNode>();
        std::shared_ptr<ProcedureNode> prod = std::make_shared<ProcedureNode>("prod1");
        std::shared_ptr<StmtLstNode> stmtList = std::make_shared <StmtLstNode>();
        std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(1, "prod1");

        stmtList->addStmt(move(callNode));
        prod->setStmtList(move(stmtList));
        root->addProcedure(move(prod));

        REQUIRE_THROWS(visitor.begin(*root));
    }
}

TEST_CASE("Test same procedure name - Exception - Extractor throws exception") {

    TopologicalSortVisitor visitor;

    SECTION("Recurcive Procedure") {
        std::shared_ptr<RootNode> root = std::make_shared<RootNode>();
        std::shared_ptr<ProcedureNode> prod1 = std::make_shared<ProcedureNode>("prod1");
        std::shared_ptr<ProcedureNode> prod2 = std::make_shared<ProcedureNode>("prod1");
        std::shared_ptr<StmtLstNode> stmtList1 = std::make_shared <StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtList2 = std::make_shared <StmtLstNode>();

        prod1->setStmtList(move(stmtList1));
        prod2->setStmtList(move(stmtList2));
        root->addProcedure(move(prod1));
        root->addProcedure(move(prod2));

        REQUIRE_THROWS(visitor.begin(*root));
    }
}

TEST_CASE("Test Cyclic calls - Exception - Extractor throws exception") {

    TopologicalSortVisitor visitor;

    SECTION("Cyclic Procedure") {
        std::shared_ptr<RootNode> root = std::make_shared<RootNode>();
        std::shared_ptr<ProcedureNode> prod1 = std::make_shared<ProcedureNode>("prod1");
        std::shared_ptr<ProcedureNode> prod2 = std::make_shared<ProcedureNode>("prod2");
        std::shared_ptr<ProcedureNode> prod3 = std::make_shared<ProcedureNode>("prod3");

        std::shared_ptr<StmtLstNode> stmtList1 = std::make_shared <StmtLstNode>();
        std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(1, "prod2");
        std::shared_ptr<StmtLstNode> stmtList2 = std::make_shared <StmtLstNode>();
        std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(2, "prod3");
        std::shared_ptr<StmtLstNode> stmtList3 = std::make_shared <StmtLstNode>();
        std::shared_ptr<CallNode> callNode3 = std::make_shared<CallNode>(3, "prod1");

        stmtList1->addStmt(move(callNode1));
        stmtList2->addStmt(move(callNode2));
        stmtList3->addStmt(move(callNode3));

        prod1->setStmtList(move(stmtList1));
        prod2->setStmtList(move(stmtList2));
        prod3->setStmtList(move(stmtList3));

        root->addProcedure(move(prod1));
        root->addProcedure(move(prod2));
        root->addProcedure(move(prod3));

        REQUIRE_THROWS(visitor.begin(*root));
    }
}

TEST_CASE("Nested non Cyclic/Recursive calls - OK - No exception thrown") {

    TopologicalSortVisitor visitor;

    SECTION("Cyclic Procedure") {
        std::shared_ptr<RootNode> root = std::make_shared<RootNode>();
        std::shared_ptr<ProcedureNode> prod1 = std::make_shared<ProcedureNode>("prod1");
        std::shared_ptr<ProcedureNode> prod2 = std::make_shared<ProcedureNode>("prod2");
        std::shared_ptr<ProcedureNode> prod3 = std::make_shared<ProcedureNode>("prod3");

        std::shared_ptr<StmtLstNode> stmtList1 = std::make_shared <StmtLstNode>();
        std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(1, "prod2");
        std::shared_ptr<StmtLstNode> stmtList2 = std::make_shared <StmtLstNode>();
        std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(2, "prod3");
        std::shared_ptr<StmtLstNode> stmtList3 = std::make_shared <StmtLstNode>();
        std::shared_ptr<CallNode> callNode3 = std::make_shared<CallNode>(3, "prod3");

        stmtList1->addStmt(move(callNode1));
        stmtList1->addStmt(move(callNode2));
        stmtList2->addStmt(move(callNode3));

        prod1->setStmtList(move(stmtList1));
        prod2->setStmtList(move(stmtList2));
        prod3->setStmtList(move(stmtList3));

        root->addProcedure(move(prod1));
        root->addProcedure(move(prod2));
        root->addProcedure(move(prod3));

        REQUIRE_NOTHROW(visitor.begin(*root));
    }
}

TEST_CASE("Test Toposort - OK - Tree toposorted in correct order") {

    TopologicalSortVisitor visitor;

    std::shared_ptr<RootNode> root = std::make_shared<RootNode>();
    std::shared_ptr<ProcedureNode> prod1 = std::make_shared<ProcedureNode>("prod1");
    std::shared_ptr<ProcedureNode> prod2 = std::make_shared<ProcedureNode>("prod2");
    std::shared_ptr<ProcedureNode> prod3 = std::make_shared<ProcedureNode>("prod3");
    std::shared_ptr<ProcedureNode> prod4 = std::make_shared<ProcedureNode>("prod4");
    std::shared_ptr<ProcedureNode> prod5 = std::make_shared<ProcedureNode>("prod5");
    std::shared_ptr<ProcedureNode> prod6 = std::make_shared<ProcedureNode>("prod6");
    std::shared_ptr<ProcedureNode> prod7 = std::make_shared<ProcedureNode>("prod7");

    std::shared_ptr<StmtLstNode> stmtList1 = std::make_shared <StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtList2 = std::make_shared <StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtList3 = std::make_shared <StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtList4 = std::make_shared <StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtList5 = std::make_shared <StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtList6 = std::make_shared <StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtList7 = std::make_shared <StmtLstNode>();

    std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(1, "prod2");
    std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(2, "prod3");
    std::shared_ptr<CallNode> callNode3 = std::make_shared<CallNode>(3, "prod3");
    std::shared_ptr<CallNode> callNode4 = std::make_shared<CallNode>(4, "prod4");
    std::shared_ptr<CallNode> callNode5 = std::make_shared<CallNode>(5, "prod6");
    std::shared_ptr<CallNode> callNode6 = std::make_shared<CallNode>(6, "prod5");
    std::shared_ptr<CallNode> callNode7 = std::make_shared<CallNode>(7, "prod7");
    std::shared_ptr<CallNode> callNode8 = std::make_shared<CallNode>(8, "prod5");

    stmtList1->addStmt(move(callNode1));
    stmtList1->addStmt(move(callNode2));
    stmtList2->addStmt(move(callNode3));
    stmtList3->addStmt(move(callNode4));
    stmtList3->addStmt(move(callNode5));
    stmtList4->addStmt(move(callNode6));
    stmtList5->addStmt(move(callNode7));
    stmtList6->addStmt(move(callNode8));

    prod1->setStmtList(move(stmtList1));
    prod2->setStmtList(move(stmtList2));
    prod3->setStmtList(move(stmtList3));
    prod4->setStmtList(move(stmtList4));
    prod5->setStmtList(move(stmtList5));
    prod6->setStmtList(move(stmtList6));
    prod7->setStmtList(move(stmtList7));

    root->addProcedure(move(prod1));
    root->addProcedure(move(prod2));
    root->addProcedure(move(prod3));
    root->addProcedure(move(prod4));
    root->addProcedure(move(prod5));
    root->addProcedure(move(prod6));
    root->addProcedure(move(prod7));

    std::unordered_map<std::string, std::unordered_set<std::string>> callsMap = {{"prod1", {"prod2", "prod3"}},
        {"prod2", {"prod3"}},
        {"prod3", {"prod4", "prod6"}},
        {"prod4", {"prod5"}},
        {"prod5", {"prod7"}},
        {"prod6", {"prod5"}},
        {"prod7", {}}};



    SECTION("Non toposorted expects error") {
        bool error = false;
        std::unordered_set<std::string> added;
        for (int i = 0; i < root->getProcedureCount(); i++) {
            std::string prodName = root->getProcedure(i)->getProcedureName();
            added.insert(prodName);
            std::unordered_set<std::string> next = callsMap.at(prodName);
            for (auto& nextProc : next) {
                if (added.find(nextProc) == added.end()) {
                    error = true;
                    break;
                }
            }
            if (error)
                break;
        }
        REQUIRE(error);
    }

    SECTION("Non toposorted expects error") {
        visitor.begin(*root);
        bool error = false;
        std::unordered_set<std::string> added;
        for (int i = 0; i < root->getProcedureCount(); i++) {
            std::string prodName = root->getProcedure(i)->getProcedureName();
            added.insert(prodName);
            std::unordered_set<std::string> next = callsMap.at(prodName);
            for (auto& nextProc : next) {
                if (added.find(nextProc) == added.end()) {
                    error = true;
                    break;
                }
            }
        }
        REQUIRE_FALSE(error);
    }
}
