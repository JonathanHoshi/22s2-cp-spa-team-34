#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"

#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/extractor/ParentRelationVisitor.h"
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

#include "stub/StubParentAdder.cpp"
#include "common/ASTBuilder.h"

TEST_CASE("Evaluate basic parent functionalities - OK - Stub storage contains expected value") {
    StubParentAdder adder;
    ParentRelationVisitor extractor(adder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(2);
    readNode1->setVariable(variableNode1);
    stmtLstNode2->addStmt(readNode1);
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(variableNode3);
    operatorNode1->addRHS(variableNode4);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(3);
    assignNode1->setVariable(variableNode2);
    assignNode1->setExpression(operatorNode1); stmtLstNode2->addStmt(assignNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(4);
    readNode2->setVariable(variableNode5);
    stmtLstNode3->addStmt(readNode2);
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("y");
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("+");
    operatorNode2->addLHS(variableNode7);
    operatorNode2->addRHS(variableNode8);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(5);
    assignNode2->setVariable(variableNode6);
    assignNode2->setExpression(operatorNode2); stmtLstNode3->addStmt(assignNode2);
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("==");
    operatorNode3->addLHS(variableNode9);
    operatorNode3->addRHS(constantNode1);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(1);
    ifNode1->setCondition(operatorNode3);
    ifNode1->setThen(stmtLstNode2);
    ifNode1->setElse(stmtLstNode3);
    stmtLstNode1->addStmt(ifNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("y");
    std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(7);
    printNode1->setVariable(variableNode10);
    stmtLstNode4->addStmt(printNode1);
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("y");
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("c");
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("+");
    operatorNode4->addLHS(variableNode12);
    operatorNode4->addRHS(variableNode13);
    std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(8);
    assignNode3->setVariable(variableNode11);
    assignNode3->setExpression(operatorNode4); stmtLstNode4->addStmt(assignNode3);
    std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("==");
    operatorNode5->addLHS(variableNode14);
    operatorNode5->addRHS(constantNode2);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(6);
    whileNode1->setCondition(operatorNode5);
    whileNode1->setStmtLst(stmtLstNode4);
    stmtLstNode1->addStmt(whileNode1);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("main");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);

    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("if") {
        REQUIRE(adder.containsParent(1, 2));
        REQUIRE(adder.containsParent(1, 3));
        REQUIRE(adder.containsParent(1, 4));
        REQUIRE(adder.containsParent(1, 5));
        REQUIRE(!adder.containsParent(5, 1));
    }

    SECTION("Intercontainer") {
        REQUIRE(!adder.containsParent(3, 4));
        REQUIRE(!adder.containsParent(5, 6));
        REQUIRE(!adder.containsParent(1, 6));
    }

    SECTION("while") {
        REQUIRE(adder.containsParent(6, 7));
        REQUIRE(adder.containsParent(6, 8));
    }
}

TEST_CASE("Evaluate nest parent functionalities - OK - Stub storage contains expected value") {
    StubParentAdder adder;
    ParentRelationVisitor extractor(adder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(2);
    readNode1->setVariable(variableNode1);
    stmtLstNode2->addStmt(readNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
    std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(5);
    printNode1->setVariable(variableNode2);
    stmtLstNode4->addStmt(printNode1);
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("y");
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(variableNode4);
    operatorNode1->addRHS(constantNode1);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(6);
    assignNode1->setVariable(variableNode3);
    assignNode1->setExpression(operatorNode1); stmtLstNode4->addStmt(assignNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("+");
    operatorNode2->addLHS(variableNode6);
    operatorNode2->addRHS(constantNode2);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(7);
    assignNode2->setVariable(variableNode5);
    assignNode2->setExpression(operatorNode2); stmtLstNode5->addStmt(assignNode2);
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("==");
    operatorNode3->addLHS(variableNode7);
    operatorNode3->addRHS(constantNode3);
    std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(4);
    ifNode2->setCondition(operatorNode3);
    ifNode2->setThen(stmtLstNode4);
    ifNode2->setElse(stmtLstNode5);
    stmtLstNode3->addStmt(ifNode2);
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("==");
    operatorNode4->addLHS(variableNode8);
    operatorNode4->addRHS(constantNode4);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(3);
    whileNode1->setCondition(operatorNode4);
    whileNode1->setStmtLst(stmtLstNode3);
    stmtLstNode2->addStmt(whileNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(9);
    readNode2->setVariable(variableNode9);
    stmtLstNode7->addStmt(readNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode8 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("+");
    operatorNode5->addLHS(variableNode11);
    operatorNode5->addRHS(constantNode5);
    std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(11);
    assignNode3->setVariable(variableNode10);
    assignNode3->setExpression(operatorNode5); stmtLstNode8->addStmt(assignNode3);
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("==");
    operatorNode6->addLHS(variableNode12);
    operatorNode6->addRHS(constantNode6);
    std::shared_ptr<WhileNode> whileNode3 = std::make_shared<WhileNode>(10);
    whileNode3->setCondition(operatorNode6);
    whileNode3->setStmtLst(stmtLstNode8);
    stmtLstNode7->addStmt(whileNode3);
    std::shared_ptr<StmtLstNode> stmtLstNode9 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode7 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>("+");
    operatorNode7->addLHS(variableNode14);
    operatorNode7->addRHS(constantNode7);
    std::shared_ptr<AssignNode> assignNode4 = std::make_shared<AssignNode>(13);
    assignNode4->setVariable(variableNode13);
    assignNode4->setExpression(operatorNode7); stmtLstNode9->addStmt(assignNode4);
    std::shared_ptr<VariableNode> variableNode15 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode8 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("==");
    operatorNode8->addLHS(variableNode15);
    operatorNode8->addRHS(constantNode8);
    std::shared_ptr<WhileNode> whileNode4 = std::make_shared<WhileNode>(12);
    whileNode4->setCondition(operatorNode8);
    whileNode4->setStmtLst(stmtLstNode9);
    stmtLstNode7->addStmt(whileNode4);
    std::shared_ptr<VariableNode> variableNode16 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode9 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>("==");
    operatorNode9->addLHS(variableNode16);
    operatorNode9->addRHS(constantNode9);
    std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(8);
    whileNode2->setCondition(operatorNode9);
    whileNode2->setStmtLst(stmtLstNode7);
    stmtLstNode6->addStmt(whileNode2);
    std::shared_ptr<VariableNode> variableNode17 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode10 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode10 = std::make_shared<OperatorNode>("==");
    operatorNode10->addLHS(variableNode17);
    operatorNode10->addRHS(constantNode10);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(1);
    ifNode1->setCondition(operatorNode10);
    ifNode1->setThen(stmtLstNode2);
    ifNode1->setElse(stmtLstNode6);
    stmtLstNode1->addStmt(ifNode1);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("main");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);

    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("Intercontainer") {
        REQUIRE(adder.containsParent(1, 2));
        REQUIRE(adder.containsParent(1, 3));
        REQUIRE(adder.containsParent(1, 8));
    }

    SECTION("Multi nest") {
        REQUIRE(!adder.containsParent(1, 4));
        REQUIRE(adder.containsParent(3, 4));
        REQUIRE(adder.containsParent(4, 5));
        REQUIRE(adder.containsParent(4, 6));
        REQUIRE(adder.containsParent(4, 7));
    }

    SECTION("Containers within container") {
        REQUIRE(adder.containsParent(8, 9));
        REQUIRE(adder.containsParent(8, 10));
        REQUIRE(adder.containsParent(8, 12));
    }

}