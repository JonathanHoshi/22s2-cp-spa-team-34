#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"
#include "sp/extractor/EntityExtractorVisitor.h"
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

#include "stub/StubStmtAdder.cpp"
#include "stub/StubProcAdder.cpp"
#include "stub/StubConstAdder.cpp"
#include "stub/StubVarAdder.cpp"
#include "common/ASTBuilder.h"

// Format: "Format <NAME> - <ErrorStatus> - <Result>"

TEST_CASE("Evaluate Procedure Insertion - OK - Stub storage contains expected value") {

    StubStmtAdder stmtAdder;
    StubProcAdder procAdder;
    StubConstAdder constAdder;
    StubVarAdder varAdder;

    EntityExtractorVisitor visitor(stmtAdder, procAdder, constAdder, varAdder);

    SECTION("Procedure") {
        std::shared_ptr<RootNode> root = std::make_shared<RootNode>();
        std::shared_ptr<ProcedureNode> prod = std::make_shared<ProcedureNode>("Prod1");
        prod->setStmtList(std::make_shared<StmtLstNode>());
        std::shared_ptr<ProcedureNode> prod2 = std::make_shared<ProcedureNode>("Prod2");
        prod2->setStmtList(std::make_shared<StmtLstNode>());
        root->addProcedure(prod);
        root->addProcedure(prod2);

        visitor.begin(*root);
        visitor.transfer();

        REQUIRE(procAdder.getProcedureCount() == 2);
        REQUIRE(procAdder.find("Prod1"));
        REQUIRE(procAdder.find("Prod1"));
    }
}

TEST_CASE("Test extraction entity basic count - OK - Stub storage contains expected number of entities") {
    StubStmtAdder stmtAdder;
    StubProcAdder procAdder;
    StubConstAdder constAdder;
    StubVarAdder varAdder;

    EntityExtractorVisitor visitor(stmtAdder, procAdder, constAdder, varAdder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(1);
    readNode1->setVariable(variableNode1);
    stmtLstNode1->addStmt(readNode1);
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("read");
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("read");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(variableNode3);
    operatorNode1->addRHS(constantNode1);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(2);
    assignNode1->setVariable(variableNode2);
    assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("b");
    std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(3);
    printNode1->setVariable(variableNode4);
    stmtLstNode1->addStmt(printNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("+");
    operatorNode2->addLHS(variableNode6);
    operatorNode2->addRHS(constantNode2);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(5);
    assignNode2->setVariable(variableNode5);
    assignNode2->setExpression(operatorNode2); stmtLstNode2->addStmt(assignNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("+");
    operatorNode3->addLHS(variableNode8);
    operatorNode3->addRHS(constantNode3);
    std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(6);
    assignNode3->setVariable(variableNode7);
    assignNode3->setExpression(operatorNode3); stmtLstNode3->addStmt(assignNode3);
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("==");
    operatorNode4->addLHS(variableNode9);
    operatorNode4->addRHS(constantNode4);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(4);
    ifNode1->setCondition(operatorNode4);
    ifNode1->setThen(stmtLstNode2);
    ifNode1->setElse(stmtLstNode3);
    stmtLstNode1->addStmt(ifNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("+");
    operatorNode5->addLHS(variableNode11);
    operatorNode5->addRHS(constantNode5);
    std::shared_ptr<AssignNode> assignNode4 = std::make_shared<AssignNode>(8);
    assignNode4->setVariable(variableNode10);
    assignNode4->setExpression(operatorNode5); stmtLstNode4->addStmt(assignNode4);
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("==");
    operatorNode6->addLHS(variableNode12);
    operatorNode6->addRHS(constantNode6);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(7);
    whileNode1->setCondition(operatorNode6);
    whileNode1->setStmtLst(stmtLstNode4);
    stmtLstNode1->addStmt(whileNode1);
    std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(9, "a3");
    stmtLstNode1->addStmt(callNode1);
    std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(10, "a4");
    stmtLstNode1->addStmt(callNode2);
    std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("k");
    std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(11);
    printNode2->setVariable(variableNode13);
    stmtLstNode1->addStmt(printNode2);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("a1");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("a1");
    std::shared_ptr<PrintNode> printNode3 = std::make_shared<PrintNode>(12);
    printNode3->setVariable(variableNode14);
    stmtLstNode5->addStmt(printNode3);
    std::shared_ptr<VariableNode> variableNode15 = std::make_shared<VariableNode>("a2");
    std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(13);
    readNode2->setVariable(variableNode15);
    stmtLstNode5->addStmt(readNode2);
    std::shared_ptr<VariableNode> variableNode16 = std::make_shared<VariableNode>("procedure");
    std::shared_ptr<VariableNode> variableNode17 = std::make_shared<VariableNode>("procedure");
    std::shared_ptr<ConstantNode> constantNode7 = std::make_shared<ConstantNode>(12);
    std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>("+");
    operatorNode7->addLHS(variableNode17);
    operatorNode7->addRHS(constantNode7);
    std::shared_ptr<AssignNode> assignNode5 = std::make_shared<AssignNode>(14);
    assignNode5->setVariable(variableNode16);
    assignNode5->setExpression(operatorNode7); stmtLstNode5->addStmt(assignNode5);
    std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode18 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode19 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode8 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("+");
    operatorNode8->addLHS(variableNode19);
    operatorNode8->addRHS(constantNode8);
    std::shared_ptr<AssignNode> assignNode6 = std::make_shared<AssignNode>(16);
    assignNode6->setVariable(variableNode18);
    assignNode6->setExpression(operatorNode8); stmtLstNode6->addStmt(assignNode6);
    std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode20 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode21 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode9 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>("+");
    operatorNode9->addLHS(variableNode21);
    operatorNode9->addRHS(constantNode9);
    std::shared_ptr<AssignNode> assignNode7 = std::make_shared<AssignNode>(17);
    assignNode7->setVariable(variableNode20);
    assignNode7->setExpression(operatorNode9); stmtLstNode7->addStmt(assignNode7);
    std::shared_ptr<VariableNode> variableNode22 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode23 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode11 = std::make_shared<OperatorNode>("+");
    operatorNode11->addLHS(variableNode22);
    operatorNode11->addRHS(variableNode23);
    std::shared_ptr<VariableNode> variableNode24 = std::make_shared<VariableNode>("c");
    std::shared_ptr<OperatorNode> operatorNode10 = std::make_shared<OperatorNode>("==");
    operatorNode10->addLHS(operatorNode11);
    operatorNode10->addRHS(variableNode24);
    std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(15);
    ifNode2->setCondition(operatorNode10);
    ifNode2->setThen(stmtLstNode6);
    ifNode2->setElse(stmtLstNode7);
    stmtLstNode5->addStmt(ifNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode8 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode25 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode26 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode10 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode12 = std::make_shared<OperatorNode>("+");
    operatorNode12->addLHS(variableNode26);
    operatorNode12->addRHS(constantNode10);
    std::shared_ptr<AssignNode> assignNode8 = std::make_shared<AssignNode>(19);
    assignNode8->setVariable(variableNode25);
    assignNode8->setExpression(operatorNode12); stmtLstNode8->addStmt(assignNode8);
    std::shared_ptr<VariableNode> variableNode27 = std::make_shared<VariableNode>("d");
    std::shared_ptr<VariableNode> variableNode28 = std::make_shared<VariableNode>("e");
    std::shared_ptr<OperatorNode> operatorNode14 = std::make_shared<OperatorNode>("+");
    operatorNode14->addLHS(variableNode27);
    operatorNode14->addRHS(variableNode28);
    std::shared_ptr<ConstantNode> constantNode11 = std::make_shared<ConstantNode>(500);
    std::shared_ptr<OperatorNode> operatorNode13 = std::make_shared<OperatorNode>("==");
    operatorNode13->addLHS(operatorNode14);
    operatorNode13->addRHS(constantNode11);
    std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(18);
    whileNode2->setCondition(operatorNode13);
    whileNode2->setStmtLst(stmtLstNode8);
    stmtLstNode5->addStmt(whileNode2);
    std::shared_ptr<ProcedureNode> procedureNode2 = std::make_shared<ProcedureNode>("a2");
    procedureNode2->setStmtList(stmtLstNode5);
    rootNode1->addProcedure(procedureNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode9 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode29 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode30 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode12 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode15 = std::make_shared<OperatorNode>("+");
    operatorNode15->addLHS(variableNode30);
    operatorNode15->addRHS(constantNode12);
    std::shared_ptr<AssignNode> assignNode9 = std::make_shared<AssignNode>(20);
    assignNode9->setVariable(variableNode29);
    assignNode9->setExpression(operatorNode15); stmtLstNode9->addStmt(assignNode9);
    std::shared_ptr<ProcedureNode> procedureNode3 = std::make_shared<ProcedureNode>("a3");
    procedureNode3->setStmtList(stmtLstNode9);
    rootNode1->addProcedure(procedureNode3);


    visitor.begin(*rootNode1);
    visitor.transfer();

    REQUIRE(stmtAdder.getReadCount() == 2);
    REQUIRE(stmtAdder.getPrintCount() == 3);
    REQUIRE(varAdder.getVarCount() == 12);
    REQUIRE(constAdder.getConstCount() == 4);
    REQUIRE(procAdder.getProcedureCount() == 3);
    REQUIRE(stmtAdder.getCallCount() == 2);
    REQUIRE(stmtAdder.getAssignCount() == 9);
    REQUIRE(stmtAdder.getIfCount() == 2);
    REQUIRE(stmtAdder.getWhileCount() == 2);
}

TEST_CASE("Test extraction entity containers count - OK - Stub storage contains expected number of entities") {
    StubStmtAdder stmtAdder;
    StubProcAdder procAdder;
    StubConstAdder constAdder;
    StubVarAdder varAdder;

    EntityExtractorVisitor visitor(stmtAdder, procAdder, constAdder, varAdder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("e");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(3);
    readNode1->setVariable(variableNode1);
    stmtLstNode3->addStmt(readNode1);
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("f");
    std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(4);
    printNode1->setVariable(variableNode2);
    stmtLstNode3->addStmt(printNode1);
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("b");
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("c");
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("d");
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("+");
    operatorNode3->addLHS(variableNode4);
    operatorNode3->addRHS(variableNode5);
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("+");
    operatorNode2->addLHS(operatorNode3);
    operatorNode2->addRHS(constantNode1);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("==");
    operatorNode1->addLHS(variableNode3);
    operatorNode1->addRHS(operatorNode2);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(2);
    whileNode1->setCondition(operatorNode1);
    whileNode1->setStmtLst(stmtLstNode3);
    stmtLstNode2->addStmt(whileNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("g");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("h");
    std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>("+");
    operatorNode7->addLHS(constantNode3);
    operatorNode7->addRHS(variableNode7);
    std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("+");
    operatorNode6->addLHS(constantNode2);
    operatorNode6->addRHS(operatorNode7);
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("i");
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("+");
    operatorNode5->addLHS(operatorNode6);
    operatorNode5->addRHS(variableNode8);
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(4);
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("+");
    operatorNode4->addLHS(operatorNode5);
    operatorNode4->addRHS(constantNode4);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(5);
    assignNode1->setVariable(variableNode6);
    assignNode1->setExpression(operatorNode4); stmtLstNode4->addStmt(assignNode1);
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("==");
    operatorNode8->addLHS(variableNode9);
    operatorNode8->addRHS(constantNode5);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(1);
    ifNode1->setCondition(operatorNode8);
    ifNode1->setThen(stmtLstNode2);
    ifNode1->setElse(stmtLstNode4);
    stmtLstNode1->addStmt(ifNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(7, "h");
    stmtLstNode5->addStmt(callNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>("+");
    operatorNode9->addLHS(variableNode11);
    operatorNode9->addRHS(constantNode6);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(9);
    assignNode2->setVariable(variableNode10);
    assignNode2->setExpression(operatorNode9); stmtLstNode6->addStmt(assignNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("m");
    std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("n");
    std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("o");
    std::shared_ptr<OperatorNode> operatorNode10 = std::make_shared<OperatorNode>("+");
    operatorNode10->addLHS(variableNode13);
    operatorNode10->addRHS(variableNode14);
    std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(10);
    assignNode3->setVariable(variableNode12);
    assignNode3->setExpression(operatorNode10); stmtLstNode7->addStmt(assignNode3);
    std::shared_ptr<VariableNode> variableNode15 = std::make_shared<VariableNode>("k");
    std::shared_ptr<ConstantNode> constantNode7 = std::make_shared<ConstantNode>(8);
    std::shared_ptr<OperatorNode> operatorNode14 = std::make_shared<OperatorNode>("+");
    operatorNode14->addLHS(variableNode15);
    operatorNode14->addRHS(constantNode7);
    std::shared_ptr<ConstantNode> constantNode8 = std::make_shared<ConstantNode>(9);
    std::shared_ptr<OperatorNode> operatorNode13 = std::make_shared<OperatorNode>("+");
    operatorNode13->addLHS(operatorNode14);
    operatorNode13->addRHS(constantNode8);
    std::shared_ptr<ConstantNode> constantNode9 = std::make_shared<ConstantNode>(10);
    std::shared_ptr<OperatorNode> operatorNode12 = std::make_shared<OperatorNode>("+");
    operatorNode12->addLHS(operatorNode13);
    operatorNode12->addRHS(constantNode9);
    std::shared_ptr<VariableNode> variableNode16 = std::make_shared<VariableNode>("l");
    std::shared_ptr<ConstantNode> constantNode10 = std::make_shared<ConstantNode>(11);
    std::shared_ptr<OperatorNode> operatorNode15 = std::make_shared<OperatorNode>("+");
    operatorNode15->addLHS(variableNode16);
    operatorNode15->addRHS(constantNode10);
    std::shared_ptr<OperatorNode> operatorNode11 = std::make_shared<OperatorNode>("==");
    operatorNode11->addLHS(operatorNode12);
    operatorNode11->addRHS(operatorNode15);
    std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(8);
    ifNode2->setCondition(operatorNode11);
    ifNode2->setThen(stmtLstNode6);
    ifNode2->setElse(stmtLstNode7);
    stmtLstNode5->addStmt(ifNode2);
    std::shared_ptr<VariableNode> variableNode17 = std::make_shared<VariableNode>("j");
    std::shared_ptr<ConstantNode> constantNode11 = std::make_shared<ConstantNode>(5);
    std::shared_ptr<ConstantNode> constantNode12 = std::make_shared<ConstantNode>(6);
    std::shared_ptr<OperatorNode> operatorNode18 = std::make_shared<OperatorNode>("+");
    operatorNode18->addLHS(constantNode11);
    operatorNode18->addRHS(constantNode12);
    std::shared_ptr<ConstantNode> constantNode13 = std::make_shared<ConstantNode>(7);
    std::shared_ptr<OperatorNode> operatorNode17 = std::make_shared<OperatorNode>("+");
    operatorNode17->addLHS(operatorNode18);
    operatorNode17->addRHS(constantNode13);
    std::shared_ptr<OperatorNode> operatorNode16 = std::make_shared<OperatorNode>("==");
    operatorNode16->addLHS(variableNode17);
    operatorNode16->addRHS(operatorNode17);
    std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(6);
    whileNode2->setCondition(operatorNode16);
    whileNode2->setStmtLst(stmtLstNode5);
    stmtLstNode1->addStmt(whileNode2);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("a1");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);


    visitor.begin(*rootNode1);
    visitor.transfer();

    REQUIRE(stmtAdder.getReadCount() == 1);
    REQUIRE(stmtAdder.getPrintCount() == 1);
    REQUIRE(varAdder.getVarCount() == 15);
    REQUIRE(constAdder.getConstCount() == 11);
    REQUIRE(procAdder.getProcedureCount() == 1);
    REQUIRE(stmtAdder.getCallCount() == 1);
    REQUIRE(stmtAdder.getAssignCount() == 3);
    REQUIRE(stmtAdder.getIfCount() == 2);
    REQUIRE(stmtAdder.getWhileCount() == 2);
}


