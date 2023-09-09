#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"
#include "sp/extractor/CallsExtractorVisitor.h"
#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/node/AssignNode.h"
#include "sp/node/CallNode.h"
#include "sp/node/ConstantNode.h"
#include "sp/node/IfNode.h"
#include "sp/node/OperatorNode.h"
#include "sp/node/PrintNode.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/ReadNode.h"
#include "sp/node/RootNode.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/StmtNode.h"
#include "sp/node/VariableNode.h"
#include "sp/node/WhileNode.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include "stub/StubCallAdder.cpp"
#include "common/ASTBuilder.h"

TEST_CASE("Test Calls toposorted exception - OK/Exception - Non topo sorted throws error and vice versa") {
    SECTION("Non toposort") {
        StubCallAdder adder;
        CallsExtractorVisitor extractor(adder);

        std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(1, "a2");
        stmtLstNode1->addStmt(callNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(3, "a2");
        stmtLstNode2->addStmt(callNode2);
        std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode3 = std::make_shared<CallNode>(4, "a3");
        stmtLstNode3->addStmt(callNode3);
        std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(3);
        std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("==");
        operatorNode1->addLHS(variableNode1);
        operatorNode1->addRHS(constantNode1);
        std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(2);
        ifNode1->setCondition(operatorNode1);
        ifNode1->setThen(stmtLstNode2);
        ifNode1->setElse(stmtLstNode3);
        stmtLstNode1->addStmt(ifNode1);
        std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("a1");
        procedureNode1->setStmtList(stmtLstNode1);
        rootNode1->addProcedure(procedureNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode4 = std::make_shared<CallNode>(6, "a3");
        stmtLstNode5->addStmt(callNode4);
        std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(3);
        std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("==");
        operatorNode2->addLHS(variableNode2);
        operatorNode2->addRHS(constantNode2);
        std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(5);
        whileNode1->setCondition(operatorNode2);
        whileNode1->setStmtLst(stmtLstNode5);
        stmtLstNode4->addStmt(whileNode1);
        std::shared_ptr<ProcedureNode> procedureNode2 = std::make_shared<ProcedureNode>("a2");
        procedureNode2->setStmtList(stmtLstNode4);
        rootNode1->addProcedure(procedureNode2);
        std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode5 = std::make_shared<CallNode>(7, "a4");
        stmtLstNode6->addStmt(callNode5);
        std::shared_ptr<CallNode> callNode6 = std::make_shared<CallNode>(8, "a6");
        stmtLstNode6->addStmt(callNode6);
        std::shared_ptr<ProcedureNode> procedureNode3 = std::make_shared<ProcedureNode>("a3");
        procedureNode3->setStmtList(stmtLstNode6);
        rootNode1->addProcedure(procedureNode3);
        std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode7 = std::make_shared<CallNode>(9, "a5");
        stmtLstNode7->addStmt(callNode7);
        std::shared_ptr<ProcedureNode> procedureNode4 = std::make_shared<ProcedureNode>("a4");
        procedureNode4->setStmtList(stmtLstNode7);
        rootNode1->addProcedure(procedureNode4);
        std::shared_ptr<StmtLstNode> stmtLstNode8 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode8 = std::make_shared<CallNode>(10, "a7");
        stmtLstNode8->addStmt(callNode8);
        std::shared_ptr<ProcedureNode> procedureNode5 = std::make_shared<ProcedureNode>("a5");
        procedureNode5->setStmtList(stmtLstNode8);
        rootNode1->addProcedure(procedureNode5);
        std::shared_ptr<StmtLstNode> stmtLstNode9 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode9 = std::make_shared<CallNode>(11, "a5");
        stmtLstNode9->addStmt(callNode9);
        std::shared_ptr<ProcedureNode> procedureNode6 = std::make_shared<ProcedureNode>("a6");
        procedureNode6->setStmtList(stmtLstNode9);
        rootNode1->addProcedure(procedureNode6);
        std::shared_ptr<StmtLstNode> stmtLstNode10 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("a");
        std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("a");
        std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(1);
        std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("+");
        operatorNode3->addLHS(variableNode4);
        operatorNode3->addRHS(constantNode3);
        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(12);
        assignNode1->setVariable(variableNode3);
        assignNode1->setExpression(operatorNode3); stmtLstNode10->addStmt(assignNode1);
        std::shared_ptr<ProcedureNode> procedureNode7 = std::make_shared<ProcedureNode>("a7");
        procedureNode7->setStmtList(stmtLstNode10);
        rootNode1->addProcedure(procedureNode7);


        REQUIRE_THROWS(extractor.begin(*rootNode1));
    }

    SECTION("Non toposort") {
        StubCallAdder adder;
        CallsExtractorVisitor extractor(adder);

        std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("a");
        std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("a");
        std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
        std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
        operatorNode1->addLHS(variableNode2);
        operatorNode1->addRHS(constantNode1);
        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
        assignNode1->setVariable(variableNode1);
        assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
        std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("a7");
        procedureNode1->setStmtList(stmtLstNode1);
        rootNode1->addProcedure(procedureNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(2, "a7");
        stmtLstNode2->addStmt(callNode1);
        std::shared_ptr<ProcedureNode> procedureNode2 = std::make_shared<ProcedureNode>("a5");
        procedureNode2->setStmtList(stmtLstNode2);
        rootNode1->addProcedure(procedureNode2);
        std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(3, "a5");
        stmtLstNode3->addStmt(callNode2);
        std::shared_ptr<ProcedureNode> procedureNode3 = std::make_shared<ProcedureNode>("a4");
        procedureNode3->setStmtList(stmtLstNode3);
        rootNode1->addProcedure(procedureNode3);
        std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode3 = std::make_shared<CallNode>(4, "a5");
        stmtLstNode4->addStmt(callNode3);
        std::shared_ptr<ProcedureNode> procedureNode4 = std::make_shared<ProcedureNode>("a6");
        procedureNode4->setStmtList(stmtLstNode4);
        rootNode1->addProcedure(procedureNode4);
        std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode4 = std::make_shared<CallNode>(5, "a4");
        stmtLstNode5->addStmt(callNode4);
        std::shared_ptr<CallNode> callNode5 = std::make_shared<CallNode>(6, "a6");
        stmtLstNode5->addStmt(callNode5);
        std::shared_ptr<ProcedureNode> procedureNode5 = std::make_shared<ProcedureNode>("a3");
        procedureNode5->setStmtList(stmtLstNode5);
        rootNode1->addProcedure(procedureNode5);
        std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode6 = std::make_shared<CallNode>(8, "a3");
        stmtLstNode7->addStmt(callNode6);
        std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(3);
        std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("==");
        operatorNode2->addLHS(variableNode3);
        operatorNode2->addRHS(constantNode2);
        std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(7);
        whileNode1->setCondition(operatorNode2);
        whileNode1->setStmtLst(stmtLstNode7);
        stmtLstNode6->addStmt(whileNode1);
        std::shared_ptr<ProcedureNode> procedureNode6 = std::make_shared<ProcedureNode>("a2");
        procedureNode6->setStmtList(stmtLstNode6);
        rootNode1->addProcedure(procedureNode6);
        std::shared_ptr<StmtLstNode> stmtLstNode8 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode7 = std::make_shared<CallNode>(9, "a2");
        stmtLstNode8->addStmt(callNode7);
        std::shared_ptr<StmtLstNode> stmtLstNode9 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode8 = std::make_shared<CallNode>(11, "a2");
        stmtLstNode9->addStmt(callNode8);
        std::shared_ptr<StmtLstNode> stmtLstNode10 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode9 = std::make_shared<CallNode>(12, "a3");
        stmtLstNode10->addStmt(callNode9);
        std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(3);
        std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("==");
        operatorNode3->addLHS(variableNode4);
        operatorNode3->addRHS(constantNode3);
        std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(10);
        ifNode1->setCondition(operatorNode3);
        ifNode1->setThen(stmtLstNode9);
        ifNode1->setElse(stmtLstNode10);
        stmtLstNode8->addStmt(ifNode1);
        std::shared_ptr<ProcedureNode> procedureNode7 = std::make_shared<ProcedureNode>("a1");
        procedureNode7->setStmtList(stmtLstNode8);
        rootNode1->addProcedure(procedureNode7);


        REQUIRE_NOTHROW(extractor.begin(*rootNode1));
    }
}

TEST_CASE("Test Calls extraction - OK - Stub contains expected value") {
    StubCallAdder adder;
    CallsExtractorVisitor extractor(adder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(variableNode2);
    operatorNode1->addRHS(constantNode1);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
    assignNode1->setVariable(variableNode1);
    assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("a7");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(2, "a7");
    stmtLstNode2->addStmt(callNode1);
    std::shared_ptr<ProcedureNode> procedureNode2 = std::make_shared<ProcedureNode>("a5");
    procedureNode2->setStmtList(stmtLstNode2);
    rootNode1->addProcedure(procedureNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(3, "a5");
    stmtLstNode3->addStmt(callNode2);
    std::shared_ptr<ProcedureNode> procedureNode3 = std::make_shared<ProcedureNode>("a4");
    procedureNode3->setStmtList(stmtLstNode3);
    rootNode1->addProcedure(procedureNode3);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode3 = std::make_shared<CallNode>(4, "a5");
    stmtLstNode4->addStmt(callNode3);
    std::shared_ptr<ProcedureNode> procedureNode4 = std::make_shared<ProcedureNode>("a6");
    procedureNode4->setStmtList(stmtLstNode4);
    rootNode1->addProcedure(procedureNode4);
    std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode4 = std::make_shared<CallNode>(5, "a4");
    stmtLstNode5->addStmt(callNode4);
    std::shared_ptr<CallNode> callNode5 = std::make_shared<CallNode>(6, "a6");
    stmtLstNode5->addStmt(callNode5);
    std::shared_ptr<ProcedureNode> procedureNode5 = std::make_shared<ProcedureNode>("a3");
    procedureNode5->setStmtList(stmtLstNode5);
    rootNode1->addProcedure(procedureNode5);
    std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode6 = std::make_shared<CallNode>(8, "a3");
    stmtLstNode7->addStmt(callNode6);
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("==");
    operatorNode2->addLHS(variableNode3);
    operatorNode2->addRHS(constantNode2);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(7);
    whileNode1->setCondition(operatorNode2);
    whileNode1->setStmtLst(stmtLstNode7);
    stmtLstNode6->addStmt(whileNode1);
    std::shared_ptr<ProcedureNode> procedureNode6 = std::make_shared<ProcedureNode>("a2");
    procedureNode6->setStmtList(stmtLstNode6);
    rootNode1->addProcedure(procedureNode6);
    std::shared_ptr<StmtLstNode> stmtLstNode8 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode7 = std::make_shared<CallNode>(9, "a2");
    stmtLstNode8->addStmt(callNode7);
    std::shared_ptr<StmtLstNode> stmtLstNode9 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode8 = std::make_shared<CallNode>(11, "a2");
    stmtLstNode9->addStmt(callNode8);
    std::shared_ptr<StmtLstNode> stmtLstNode10 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode9 = std::make_shared<CallNode>(12, "a3");
    stmtLstNode10->addStmt(callNode9);
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("==");
    operatorNode3->addLHS(variableNode4);
    operatorNode3->addRHS(constantNode3);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(10);
    ifNode1->setCondition(operatorNode3);
    ifNode1->setThen(stmtLstNode9);
    ifNode1->setElse(stmtLstNode10);
    stmtLstNode8->addStmt(ifNode1);
    std::shared_ptr<ProcedureNode> procedureNode7 = std::make_shared<ProcedureNode>("a1");
    procedureNode7->setStmtList(stmtLstNode8);
    rootNode1->addProcedure(procedureNode7);


    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("Direct calls") {
        REQUIRE(adder.containsCall("a1", "a2"));
        REQUIRE(adder.containsCall("a1", "a3"));
        REQUIRE(adder.containsCall("a2", "a3"));
        REQUIRE(adder.containsCall("a3", "a4"));
        REQUIRE(adder.containsCall("a3", "a6"));
        REQUIRE(adder.containsCall("a4", "a5"));
        REQUIRE(adder.containsCall("a6", "a5"));
        REQUIRE(adder.containsCall("a5", "a7"));
    }

    SECTION("Direct calls Negative") {
        REQUIRE_FALSE(adder.containsCall("a2", "a1"));
        REQUIRE_FALSE(adder.containsCall("a3", "a1"));
        REQUIRE_FALSE(adder.containsCall("a3", "a2"));
        REQUIRE_FALSE(adder.containsCall("a4", "a3"));
        REQUIRE_FALSE(adder.containsCall("a6", "a3"));
        REQUIRE_FALSE(adder.containsCall("a5", "a4"));
        REQUIRE_FALSE(adder.containsCall("a5", "a6"));
        REQUIRE_FALSE(adder.containsCall("a7", "a5"));
    }

    SECTION("Calls != CallsT") {
        REQUIRE_FALSE(adder.containsCall("a1", "a7"));
        REQUIRE_FALSE(adder.containsCall("a1", "a6"));
        REQUIRE_FALSE(adder.containsCall("a1", "a4"));

        REQUIRE_FALSE(adder.containsCall("a2", "a7"));
        REQUIRE_FALSE(adder.containsCall("a3", "a7"));
        REQUIRE_FALSE(adder.containsCall("a4", "a7"));
        REQUIRE_FALSE(adder.containsCall("a6", "a7"));
    }

    SECTION("CallsT") {
        REQUIRE(adder.containsCallT("a1", "a2"));
        REQUIRE(adder.containsCallT("a1", "a3"));
        REQUIRE(adder.containsCallT("a1", "a4"));
        REQUIRE(adder.containsCallT("a1", "a5"));
        REQUIRE(adder.containsCallT("a1", "a6"));
        REQUIRE(adder.containsCallT("a1", "a7"));

        REQUIRE(adder.containsCallT("a2", "a3"));
        REQUIRE(adder.containsCallT("a2", "a4"));
        REQUIRE(adder.containsCallT("a2", "a6"));
        REQUIRE(adder.containsCallT("a2", "a5"));
        REQUIRE(adder.containsCallT("a2", "a7"));

        REQUIRE(adder.containsCallT("a3", "a4"));
        REQUIRE(adder.containsCallT("a3", "a6"));
        REQUIRE(adder.containsCallT("a3", "a5"));
        REQUIRE(adder.containsCallT("a3", "a7"));

        REQUIRE(adder.containsCallT("a4", "a5"));
        REQUIRE(adder.containsCallT("a4", "a7"));

        REQUIRE(adder.containsCallT("a6", "a5"));
        REQUIRE(adder.containsCallT("a6", "a7"));

        REQUIRE(adder.containsCallT("a5", "a7"));
    }

    SECTION("CallsT Negative") {
        REQUIRE_FALSE(adder.containsCallT("a2", "a1"));
        REQUIRE_FALSE(adder.containsCallT("a3", "a1"));
        REQUIRE_FALSE(adder.containsCallT("a4", "a1"));
        REQUIRE_FALSE(adder.containsCallT("a5", "a1"));
        REQUIRE_FALSE(adder.containsCallT("a6", "a1"));
        REQUIRE_FALSE(adder.containsCallT("a7", "a1"));

        REQUIRE_FALSE(adder.containsCallT("a3", "a2"));
        REQUIRE_FALSE(adder.containsCallT("a4", "a2"));
        REQUIRE_FALSE(adder.containsCallT("a6", "a2"));
        REQUIRE_FALSE(adder.containsCallT("a5", "a2"));
        REQUIRE_FALSE(adder.containsCallT("a7", "a2"));

        REQUIRE_FALSE(adder.containsCallT("a4", "a3"));
        REQUIRE_FALSE(adder.containsCallT("a6", "a3"));
        REQUIRE_FALSE(adder.containsCallT("a5", "a3"));
        REQUIRE_FALSE(adder.containsCallT("a7", "a3"));

        REQUIRE_FALSE(adder.containsCallT("a5", "a4"));
        REQUIRE_FALSE(adder.containsCallT("a7", "a4"));

        REQUIRE_FALSE(adder.containsCallT("a5", "a6"));
        REQUIRE_FALSE(adder.containsCallT("a7", "a6"));

        REQUIRE_FALSE(adder.containsCallT("a7", "a5"));
    }
}

TEST_CASE("Test Multipath calls extraction - OK - Stub contains expected value") {
    StubCallAdder adder;
    CallsExtractorVisitor extractor(adder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(variableNode2);
    operatorNode1->addRHS(constantNode1);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
    assignNode1->setVariable(variableNode1);
    assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("a8");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(2, "a8");
    stmtLstNode2->addStmt(callNode1);
    std::shared_ptr<ProcedureNode> procedureNode2 = std::make_shared<ProcedureNode>("a7");
    procedureNode2->setStmtList(stmtLstNode2);
    rootNode1->addProcedure(procedureNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(3, "a7");
    stmtLstNode3->addStmt(callNode2);
    std::shared_ptr<ProcedureNode> procedureNode3 = std::make_shared<ProcedureNode>("a6");
    procedureNode3->setStmtList(stmtLstNode3);
    rootNode1->addProcedure(procedureNode3);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode3 = std::make_shared<CallNode>(4, "a6");
    stmtLstNode4->addStmt(callNode3);
    std::shared_ptr<ProcedureNode> procedureNode4 = std::make_shared<ProcedureNode>("a5");
    procedureNode4->setStmtList(stmtLstNode4);
    rootNode1->addProcedure(procedureNode4);
    std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode4 = std::make_shared<CallNode>(5, "a8");
    stmtLstNode5->addStmt(callNode4);
    std::shared_ptr<ProcedureNode> procedureNode5 = std::make_shared<ProcedureNode>("a4");
    procedureNode5->setStmtList(stmtLstNode5);
    rootNode1->addProcedure(procedureNode5);
    std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode5 = std::make_shared<CallNode>(6, "a4");
    stmtLstNode6->addStmt(callNode5);
    std::shared_ptr<ProcedureNode> procedureNode6 = std::make_shared<ProcedureNode>("a3");
    procedureNode6->setStmtList(stmtLstNode6);
    rootNode1->addProcedure(procedureNode6);
    std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode8 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode9 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode6 = std::make_shared<CallNode>(9, "a3");
    stmtLstNode9->addStmt(callNode6);
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("==");
    operatorNode2->addLHS(variableNode3);
    operatorNode2->addRHS(constantNode2);
    std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(8);
    whileNode2->setCondition(operatorNode2);
    whileNode2->setStmtLst(stmtLstNode9);
    stmtLstNode8->addStmt(whileNode2);
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("==");
    operatorNode3->addLHS(variableNode4);
    operatorNode3->addRHS(constantNode3);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(7);
    whileNode1->setCondition(operatorNode3);
    whileNode1->setStmtLst(stmtLstNode8);
    stmtLstNode7->addStmt(whileNode1);
    std::shared_ptr<ProcedureNode> procedureNode7 = std::make_shared<ProcedureNode>("a2");
    procedureNode7->setStmtList(stmtLstNode7);
    rootNode1->addProcedure(procedureNode7);
    std::shared_ptr<StmtLstNode> stmtLstNode10 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode11 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode7 = std::make_shared<CallNode>(11, "a2");
    stmtLstNode11->addStmt(callNode7);
    std::shared_ptr<StmtLstNode> stmtLstNode12 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode8 = std::make_shared<CallNode>(12, "a5");
    stmtLstNode12->addStmt(callNode8);
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("==");
    operatorNode4->addLHS(variableNode5);
    operatorNode4->addRHS(constantNode4);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(10);
    ifNode1->setCondition(operatorNode4);
    ifNode1->setThen(stmtLstNode11);
    ifNode1->setElse(stmtLstNode12);
    stmtLstNode10->addStmt(ifNode1);
    std::shared_ptr<ProcedureNode> procedureNode8 = std::make_shared<ProcedureNode>("a1");
    procedureNode8->setStmtList(stmtLstNode10);
    rootNode1->addProcedure(procedureNode8);


    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("Basic test") {
        REQUIRE(adder.containsCall("a1", "a2"));
        REQUIRE(adder.containsCall("a2", "a3"));
        REQUIRE(adder.containsCall("a3", "a4"));
        REQUIRE(adder.containsCall("a4", "a8"));

        REQUIRE(adder.containsCall("a1", "a5"));
        REQUIRE(adder.containsCall("a5", "a6"));
        REQUIRE(adder.containsCall("a6", "a7"));
        REQUIRE(adder.containsCall("a7", "a8"));

        REQUIRE(adder.containsCallT("a1", "a8"));
        REQUIRE(adder.containsCallT("a2", "a8"));
        REQUIRE(adder.containsCallT("a5", "a8"));
    }

    SECTION("Multipaths do not cross") {
        REQUIRE_FALSE(adder.containsCallT("a2", "a5"));
        REQUIRE_FALSE(adder.containsCallT("a2", "a6"));
        REQUIRE_FALSE(adder.containsCallT("a2", "a7"));

        REQUIRE_FALSE(adder.containsCallT("a5", "a2"));
        REQUIRE_FALSE(adder.containsCallT("a5", "a3"));
        REQUIRE_FALSE(adder.containsCallT("a5", "a4"));

        REQUIRE(adder.containsCallT("a2", "a8"));
        REQUIRE(adder.containsCallT("a5", "a8"));
    }
}

