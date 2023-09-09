#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"
#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/extractor/ModifyRelationVisitor.h"
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

#include "stub/StubModifiesAdder.cpp"
#include "common/ASTBuilder.h"

TEST_CASE("Evaluate Unit test Modifies - OK - Stub storage contains expected value") {

    StubModifiesAdder adder;

    ModifyRelationVisitor visitor(adder);


    SECTION("Integration test") { //to be split up
        std::shared_ptr<RootNode> root = std::make_shared<RootNode>();
        std::shared_ptr<ProcedureNode> prod = std::make_shared<ProcedureNode>("p1");
        root->addProcedure(prod);

        std::shared_ptr<StmtLstNode> stmtLst1 = std::make_shared<StmtLstNode>();
        prod->setStmtList(stmtLst1);

        std::shared_ptr<ReadNode> read1 = std::make_shared<ReadNode>(1);
        stmtLst1->addStmt(read1);
        std::shared_ptr<VariableNode> var1 = std::make_shared<VariableNode>("x");
        read1->setVariable(var1);

        std::shared_ptr<ReadNode> read2 = std::make_shared<ReadNode>(2);
        stmtLst1->addStmt(read2);
        std::shared_ptr<VariableNode> var2 = std::make_shared<VariableNode>("y");
        read2->setVariable(var2);

        std::shared_ptr<PrintNode> print3 = std::make_shared<PrintNode>(3);
        stmtLst1->addStmt(print3);
        std::shared_ptr<VariableNode> var3 = std::make_shared<VariableNode>("z");
        print3->setVariable(var3);

        visitor.begin(*root);
        visitor.transfer();

        REQUIRE(adder.containsModifiesS(1, "x"));
        REQUIRE(adder.containsModifiesS(2, "y"));
        REQUIRE(!adder.containsModifiesS(3, "z"));
        REQUIRE(adder.containsModifiesP("p1", "x"));
        REQUIRE(adder.containsModifiesP("p1", "y"));
        REQUIRE(!adder.containsModifiesP("p1", "z"));
    }
}

TEST_CASE("Evaluate basic statements modifies - OK - Stub storage contains expected value") {
    StubModifiesAdder adder;
    ModifyRelationVisitor extractor(adder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(1);
    readNode1->setVariable(variableNode1);
    stmtLstNode1->addStmt(readNode1);
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(variableNode3);
    operatorNode1->addRHS(constantNode1);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(2);
    assignNode1->setVariable(variableNode2);
    assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("z");
    std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(3);
    printNode1->setVariable(variableNode4);
    stmtLstNode1->addStmt(printNode1);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("main");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);

    extractor.begin(*rootNode1);
    extractor.transfer();

    REQUIRE(adder.containsModifiesS(1, "x"));
    REQUIRE(adder.containsModifiesS(2, "x"));
    REQUIRE(!adder.containsModifiesS(3, "z"));
}

TEST_CASE("Evaluate containers statements modifies - OK - Stub storage contains expected value") {
    StubModifiesAdder adder;
    ModifyRelationVisitor extractor(adder);

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
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("k");
    std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(8);
    printNode2->setVariable(variableNode11);
    stmtLstNode4->addStmt(printNode2);
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("r");
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("==");
    operatorNode5->addLHS(variableNode12);
    operatorNode5->addRHS(constantNode4);
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
        REQUIRE(!adder.containsModifiesS(1, "b"));

        REQUIRE(adder.containsModifiesS(2, "x"));
        REQUIRE(adder.containsModifiesS(3, "y"));
        REQUIRE(adder.containsModifiesS(4, "t"));
        REQUIRE(!adder.containsModifiesS(5, "a"));

        REQUIRE(adder.containsModifiesS(1, "x"));
        REQUIRE(adder.containsModifiesS(1, "y"));
        REQUIRE(adder.containsModifiesS(1, "t"));

        REQUIRE(!adder.containsModifiesS(1, "a"));
    }

    SECTION("while") {
        REQUIRE(!adder.containsModifiesS(6, "r"));
        REQUIRE(adder.containsModifiesS(7, "x"));
        REQUIRE(!adder.containsModifiesS(8, "k"));

        REQUIRE(adder.containsModifiesS(6, "x"));
        REQUIRE(!adder.containsModifiesS(6, "k"));
    }
}