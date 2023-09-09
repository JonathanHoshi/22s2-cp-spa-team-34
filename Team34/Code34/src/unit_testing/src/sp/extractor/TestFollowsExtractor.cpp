#include <filesystem>

#include "FileReader.h"
#include "catch.hpp"

#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/extractor/FollowRelationVisitor.h"
#include "stub/StubFollowsAdder.cpp"
#include "common/ASTBuilder.h"
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

TEST_CASE("Evaluate Follows basic - OK - Stub storage contains expected value") {
    StubFollowsAdder adder;
    FollowRelationVisitor extractor(adder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("x");
    std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(1);
    printNode1->setVariable(variableNode1);
    stmtLstNode1->addStmt(printNode1);
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(2);
    readNode1->setVariable(variableNode2);
    stmtLstNode1->addStmt(readNode1);
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("z");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(constantNode1);
    operatorNode1->addRHS(constantNode2);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(3);
    assignNode1->setVariable(variableNode3);
    assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("main");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);


    extractor.begin(*rootNode1);
    extractor.transfer();

    REQUIRE(adder.containsFollow("1", "2"));
    REQUIRE(adder.containsFollow("2", "3"));
    REQUIRE(!adder.containsFollow("1", "3"));
}

TEST_CASE("Evaluate Follows container - OK - Stub storage contains expected value") {
    StubFollowsAdder adder;
    FollowRelationVisitor extractor(adder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(2);
    readNode1->setVariable(variableNode1);
    stmtLstNode2->addStmt(readNode1);
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("y");
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("*");
    operatorNode1->addLHS(variableNode3);
    operatorNode1->addRHS(constantNode1);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(3);
    assignNode1->setVariable(variableNode2);
    assignNode1->setExpression(operatorNode1); stmtLstNode2->addStmt(assignNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("t");
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("y");
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("z");
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("+");
    operatorNode2->addLHS(variableNode5);
    operatorNode2->addRHS(variableNode6);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(4);
    assignNode2->setVariable(variableNode4);
    assignNode2->setExpression(operatorNode2); stmtLstNode3->addStmt(assignNode2);
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("a");
    std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(5);
    printNode1->setVariable(variableNode7);
    stmtLstNode3->addStmt(printNode1);
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("b");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("==");
    operatorNode3->addLHS(variableNode8);
    operatorNode3->addRHS(constantNode2);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(1);
    ifNode1->setCondition(operatorNode3);
    ifNode1->setThen(stmtLstNode2);
    ifNode1->setElse(stmtLstNode3);
    stmtLstNode1->addStmt(ifNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("*");
    operatorNode4->addLHS(variableNode10);
    operatorNode4->addRHS(constantNode3);
    std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(7);
    assignNode3->setVariable(variableNode9);
    assignNode3->setExpression(operatorNode4); stmtLstNode4->addStmt(assignNode3);
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("r");
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("==");
    operatorNode5->addLHS(variableNode11);
    operatorNode5->addRHS(constantNode4);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(6);
    whileNode1->setCondition(operatorNode5);
    whileNode1->setStmtLst(stmtLstNode4);
    stmtLstNode1->addStmt(whileNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("+");
    operatorNode6->addLHS(variableNode13);
    operatorNode6->addRHS(constantNode5);
    std::shared_ptr<AssignNode> assignNode4 = std::make_shared<AssignNode>(10);
    assignNode4->setVariable(variableNode12);
    assignNode4->setExpression(operatorNode6); stmtLstNode6->addStmt(assignNode4);
    std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode15 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>("+");
    operatorNode7->addLHS(variableNode15);
    operatorNode7->addRHS(constantNode6);
    std::shared_ptr<AssignNode> assignNode5 = std::make_shared<AssignNode>(11);
    assignNode5->setVariable(variableNode14);
    assignNode5->setExpression(operatorNode7); stmtLstNode7->addStmt(assignNode5);
    std::shared_ptr<VariableNode> variableNode16 = std::make_shared<VariableNode>("b");
    std::shared_ptr<ConstantNode> constantNode7 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("==");
    operatorNode8->addLHS(variableNode16);
    operatorNode8->addRHS(constantNode7);
    std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(9);
    ifNode2->setCondition(operatorNode8);
    ifNode2->setThen(stmtLstNode6);
    ifNode2->setElse(stmtLstNode7);
    stmtLstNode5->addStmt(ifNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode8 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode17 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode18 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode8 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>("+");
    operatorNode9->addLHS(variableNode18);
    operatorNode9->addRHS(constantNode8);
    std::shared_ptr<AssignNode> assignNode6 = std::make_shared<AssignNode>(13);
    assignNode6->setVariable(variableNode17);
    assignNode6->setExpression(operatorNode9); stmtLstNode8->addStmt(assignNode6);
    std::shared_ptr<VariableNode> variableNode19 = std::make_shared<VariableNode>("r");
    std::shared_ptr<ConstantNode> constantNode9 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode10 = std::make_shared<OperatorNode>("==");
    operatorNode10->addLHS(variableNode19);
    operatorNode10->addRHS(constantNode9);
    std::shared_ptr<WhileNode> whileNode3 = std::make_shared<WhileNode>(12);
    whileNode3->setCondition(operatorNode10);
    whileNode3->setStmtLst(stmtLstNode8);
    stmtLstNode5->addStmt(whileNode3);
    std::shared_ptr<VariableNode> variableNode20 = std::make_shared<VariableNode>("r");
    std::shared_ptr<ConstantNode> constantNode10 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode11 = std::make_shared<OperatorNode>("==");
    operatorNode11->addLHS(variableNode20);
    operatorNode11->addRHS(constantNode10);
    std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(8);
    whileNode2->setCondition(operatorNode11);
    whileNode2->setStmtLst(stmtLstNode5);
    stmtLstNode1->addStmt(whileNode2);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("followscontainer");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);


    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("Container follows") {
        REQUIRE(adder.containsFollow("1", "6"));
        REQUIRE(adder.containsFollow("6", "8"));
        REQUIRE(!adder.containsFollow("1", "8"));
    }

    SECTION("Basic statement within if follow") {
        REQUIRE(adder.containsFollow("2", "3"));
        REQUIRE(!adder.containsFollow("3", "4"));
        REQUIRE(adder.containsFollow("4", "5"));
    }

    SECTION("Statements within container don't follow") {
        REQUIRE(!adder.containsFollow("5", "6"));
        REQUIRE(!adder.containsFollow("6", "7"));
        REQUIRE(!adder.containsFollow("7", "8"));
    }

    SECTION("Containers within container follow") {
        REQUIRE(adder.containsFollow("9", "12"));
    }
}