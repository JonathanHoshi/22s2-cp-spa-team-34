#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"

#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/extractor/UsesRelationVisitor.h"

#include "stub/StubUsesAdder.cpp"
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

TEST_CASE("Evaluate Uses basic - OK - Stub storage contains expected value") {
    StubUsesAdder adder;
    UsesRelationVisitor extractor(adder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("c");
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("*");
    operatorNode2->addLHS(variableNode2);
    operatorNode2->addRHS(variableNode3);
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("b");
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("+");
    operatorNode4->addLHS(variableNode4);
    operatorNode4->addRHS(variableNode5);
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("z");
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("*");
    operatorNode3->addLHS(operatorNode4);
    operatorNode3->addRHS(variableNode6);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(operatorNode2);
    operatorNode1->addRHS(operatorNode3);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
    assignNode1->setVariable(variableNode1);
    assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("t");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(2);
    assignNode2->setVariable(variableNode7);
    assignNode2->setExpression(constantNode1); stmtLstNode1->addStmt(assignNode2);
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("a");
    std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(3);
    printNode1->setVariable(variableNode8);
    stmtLstNode1->addStmt(printNode1);
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("k");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(4);
    readNode1->setVariable(variableNode9);
    stmtLstNode1->addStmt(readNode1);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("p12");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);

    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("Assignment/Factors/Terms") {
        REQUIRE(adder.containsUsesS(1, "a"));
        REQUIRE(adder.containsUsesS(1, "c"));
        REQUIRE(adder.containsUsesS(1, "b"));
        REQUIRE(adder.containsUsesS(1, "y"));
        REQUIRE(adder.containsUsesS(1, "z"));
        REQUIRE(!adder.containsUsesS(1, "x"));
    }

    SECTION("Print/Read/Number assignment") {
        REQUIRE(!adder.containsUsesS(4, "k"));
        REQUIRE(!adder.containsUsesS(2, "t"));
        REQUIRE(!adder.containsUsesS(2, "1"));
        REQUIRE(adder.containsUsesS(3, "a"));
    }
}

TEST_CASE("Evaluate Uses nest - OK - Stub storage contains expected value") {
    StubUsesAdder adder;
    UsesRelationVisitor extractor(adder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(variableNode2);
    operatorNode1->addRHS(constantNode1);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(3);
    assignNode1->setVariable(variableNode1);
    assignNode1->setExpression(operatorNode1); stmtLstNode3->addStmt(assignNode1);
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("==");
    operatorNode2->addLHS(variableNode3);
    operatorNode2->addRHS(variableNode4);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(2);
    whileNode1->setCondition(operatorNode2);
    whileNode1->setStmtLst(stmtLstNode3);
    stmtLstNode2->addStmt(whileNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("+");
    operatorNode3->addLHS(variableNode6);
    operatorNode3->addRHS(constantNode2);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(5);
    assignNode2->setVariable(variableNode5);
    assignNode2->setExpression(operatorNode3); stmtLstNode4->addStmt(assignNode2);
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("c");
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("==");
    operatorNode4->addLHS(variableNode7);
    operatorNode4->addRHS(constantNode3);
    std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(4);
    whileNode2->setCondition(operatorNode4);
    whileNode2->setStmtLst(stmtLstNode4);
    stmtLstNode2->addStmt(whileNode2);
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("e");
    std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("f");
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("g");
    std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("*");
    operatorNode6->addLHS(variableNode10);
    operatorNode6->addRHS(variableNode11);
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("+");
    operatorNode5->addLHS(variableNode9);
    operatorNode5->addRHS(operatorNode6);
    std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(6);
    assignNode3->setVariable(variableNode8);
    assignNode3->setExpression(operatorNode5); stmtLstNode2->addStmt(assignNode3);
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("k");
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<AssignNode> assignNode4 = std::make_shared<AssignNode>(7);
    assignNode4->setVariable(variableNode12);
    assignNode4->setExpression(constantNode4); stmtLstNode2->addStmt(assignNode4);
    std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("i");
    std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(8);
    printNode1->setVariable(variableNode13);
    stmtLstNode2->addStmt(printNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("j");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(9);
    readNode1->setVariable(variableNode14);
    stmtLstNode5->addStmt(readNode1);
    std::shared_ptr<VariableNode> variableNode15 = std::make_shared<VariableNode>("h");
    std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>("==");
    operatorNode7->addLHS(variableNode15);
    operatorNode7->addRHS(constantNode5);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(1);
    ifNode1->setCondition(operatorNode7);
    ifNode1->setThen(stmtLstNode2);
    ifNode1->setElse(stmtLstNode5);
    stmtLstNode1->addStmt(ifNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode16 = std::make_shared<VariableNode>("c");
    std::shared_ptr<VariableNode> variableNode17 = std::make_shared<VariableNode>("d");
    std::shared_ptr<VariableNode> variableNode18 = std::make_shared<VariableNode>("e");
    std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("+");
    operatorNode8->addLHS(variableNode17);
    operatorNode8->addRHS(variableNode18);
    std::shared_ptr<AssignNode> assignNode5 = std::make_shared<AssignNode>(11);
    assignNode5->setVariable(variableNode16);
    assignNode5->setExpression(operatorNode8); stmtLstNode6->addStmt(assignNode5);
    std::shared_ptr<VariableNode> variableNode19 = std::make_shared<VariableNode>("t");
    std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<AssignNode> assignNode6 = std::make_shared<AssignNode>(12);
    assignNode6->setVariable(variableNode19);
    assignNode6->setExpression(constantNode6); stmtLstNode6->addStmt(assignNode6);
    std::shared_ptr<VariableNode> variableNode20 = std::make_shared<VariableNode>("o");
    std::shared_ptr<ConstantNode> constantNode7 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode10 = std::make_shared<OperatorNode>("==");
    operatorNode10->addLHS(variableNode20);
    operatorNode10->addRHS(constantNode7);
    std::shared_ptr<VariableNode> variableNode21 = std::make_shared<VariableNode>("p");
    std::shared_ptr<ConstantNode> constantNode8 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode11 = std::make_shared<OperatorNode>("==");
    operatorNode11->addLHS(variableNode21);
    operatorNode11->addRHS(constantNode8);
    std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>("&&");
    operatorNode9->addLHS(operatorNode10);
    operatorNode9->addRHS(operatorNode11);
    std::shared_ptr<WhileNode> whileNode3 = std::make_shared<WhileNode>(10);
    whileNode3->setCondition(operatorNode9);
    whileNode3->setStmtLst(stmtLstNode6);
    stmtLstNode1->addStmt(whileNode3);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("p123");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);

    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("condition/equality") {
        REQUIRE(adder.containsUsesS(1, "h"));
        REQUIRE(adder.containsUsesS(10, "o"));
        REQUIRE(adder.containsUsesS(10, "p"));
    }

    SECTION("statements within if/while") {
        REQUIRE(adder.containsUsesS(1, "a"));
        REQUIRE(adder.containsUsesS(1, "b"));
        REQUIRE(adder.containsUsesS(1, "c"));
        REQUIRE(adder.containsUsesS(1, "e"));
        REQUIRE(adder.containsUsesS(1, "f"));
        REQUIRE(adder.containsUsesS(1, "g"));
        REQUIRE(adder.containsUsesS(1, "i"));
        REQUIRE(!adder.containsUsesS(1, "k"));
        REQUIRE(!adder.containsUsesS(1, "j"));

        REQUIRE(adder.containsUsesS(10, "d"));
        REQUIRE(adder.containsUsesS(10, "e"));
        REQUIRE(!adder.containsUsesS(10, "t"));
    }
}