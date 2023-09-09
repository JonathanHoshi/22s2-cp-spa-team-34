#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"
#include "sp/extractor/CFGExtractorVisitor.h"
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
#include "stub/StubNextAdder.cpp"
#include "common/ASTBuilder.h"

TEST_CASE("Test CFG extraction - OK - Stub storage contains expected number of entities") {
    StubNextAdder adder;
    CFGExtractorVisitor extractor(adder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(variableNode2);
    operatorNode1->addRHS(constantNode1);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
    assignNode1->setVariable(variableNode1);
    assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("b");
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("b");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("+");
    operatorNode2->addLHS(variableNode4);
    operatorNode2->addRHS(constantNode2);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(2);
    assignNode2->setVariable(variableNode3);
    assignNode2->setExpression(operatorNode2); stmtLstNode1->addStmt(assignNode2);
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("b");
    std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(3);
    printNode1->setVariable(variableNode5);
    stmtLstNode1->addStmt(printNode1);
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("c");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(4);
    readNode1->setVariable(variableNode6);
    stmtLstNode1->addStmt(readNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(6, "p2");
    stmtLstNode2->addStmt(callNode1);
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("d");
    std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(7);
    readNode2->setVariable(variableNode7);
    stmtLstNode2->addStmt(readNode2);
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("f");
    std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(8);
    printNode2->setVariable(variableNode8);
    stmtLstNode2->addStmt(printNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(4);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("+");
    operatorNode3->addLHS(constantNode3);
    operatorNode3->addRHS(constantNode4);
    std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(9);
    assignNode3->setVariable(variableNode9);
    assignNode3->setExpression(operatorNode3); stmtLstNode3->addStmt(assignNode3);
    std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(10, "p3");
    stmtLstNode3->addStmt(callNode2);
    std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("c");
    std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("==");
    operatorNode5->addLHS(variableNode10);
    operatorNode5->addRHS(constantNode5);
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("d");
    std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(4);
    std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("==");
    operatorNode6->addLHS(variableNode11);
    operatorNode6->addRHS(constantNode6);
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("&&");
    operatorNode4->addLHS(operatorNode5);
    operatorNode4->addRHS(operatorNode6);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(5);
    ifNode1->setCondition(operatorNode4);
    ifNode1->setThen(stmtLstNode2);
    ifNode1->setElse(stmtLstNode3);
    stmtLstNode1->addStmt(ifNode1);
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("c");
    std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("c");
    std::shared_ptr<ConstantNode> constantNode7 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>("+");
    operatorNode7->addLHS(variableNode13);
    operatorNode7->addRHS(constantNode7);
    std::shared_ptr<AssignNode> assignNode4 = std::make_shared<AssignNode>(11);
    assignNode4->setVariable(variableNode12);
    assignNode4->setExpression(operatorNode7); stmtLstNode1->addStmt(assignNode4);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode15 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode16 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("+");
    operatorNode8->addLHS(variableNode15);
    operatorNode8->addRHS(variableNode16);
    std::shared_ptr<AssignNode> assignNode5 = std::make_shared<AssignNode>(13);
    assignNode5->setVariable(variableNode14);
    assignNode5->setExpression(operatorNode8); stmtLstNode4->addStmt(assignNode5);
    std::shared_ptr<VariableNode> variableNode17 = std::make_shared<VariableNode>("b");
    std::shared_ptr<ReadNode> readNode3 = std::make_shared<ReadNode>(14);
    readNode3->setVariable(variableNode17);
    stmtLstNode4->addStmt(readNode3);
    std::shared_ptr<VariableNode> variableNode18 = std::make_shared<VariableNode>("f");
    std::shared_ptr<ConstantNode> constantNode8 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>("==");
    operatorNode9->addLHS(variableNode18);
    operatorNode9->addRHS(constantNode8);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(12);
    whileNode1->setCondition(operatorNode9);
    whileNode1->setStmtLst(stmtLstNode4);
    stmtLstNode1->addStmt(whileNode1);
    std::shared_ptr<VariableNode> variableNode19 = std::make_shared<VariableNode>("c");
    std::shared_ptr<ConstantNode> constantNode9 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode6 = std::make_shared<AssignNode>(15);
    assignNode6->setVariable(variableNode19);
    assignNode6->setExpression(constantNode9); stmtLstNode1->addStmt(assignNode6);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("p1");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode20 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode10 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode7 = std::make_shared<AssignNode>(17);
    assignNode7->setVariable(variableNode20);
    assignNode7->setExpression(constantNode10); stmtLstNode6->addStmt(assignNode7);
    std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode21 = std::make_shared<VariableNode>("b");
    std::shared_ptr<ConstantNode> constantNode11 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode8 = std::make_shared<AssignNode>(19);
    assignNode8->setVariable(variableNode21);
    assignNode8->setExpression(constantNode11); stmtLstNode7->addStmt(assignNode8);
    std::shared_ptr<StmtLstNode> stmtLstNode8 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode22 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode12 = std::make_shared<ConstantNode>(4);
    std::shared_ptr<AssignNode> assignNode9 = std::make_shared<AssignNode>(20);
    assignNode9->setVariable(variableNode22);
    assignNode9->setExpression(constantNode12); stmtLstNode8->addStmt(assignNode9);
    std::shared_ptr<VariableNode> variableNode23 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode24 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode10 = std::make_shared<OperatorNode>("==");
    operatorNode10->addLHS(variableNode23);
    operatorNode10->addRHS(variableNode24);
    std::shared_ptr<IfNode> ifNode3 = std::make_shared<IfNode>(18);
    ifNode3->setCondition(operatorNode10);
    ifNode3->setThen(stmtLstNode7);
    ifNode3->setElse(stmtLstNode8);
    stmtLstNode6->addStmt(ifNode3);
    std::shared_ptr<StmtLstNode> stmtLstNode9 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode10 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode11 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode25 = std::make_shared<VariableNode>("c");
    std::shared_ptr<ConstantNode> constantNode13 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode10 = std::make_shared<AssignNode>(23);
    assignNode10->setVariable(variableNode25);
    assignNode10->setExpression(constantNode13); stmtLstNode11->addStmt(assignNode10);
    std::shared_ptr<VariableNode> variableNode26 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode27 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode11 = std::make_shared<OperatorNode>("==");
    operatorNode11->addLHS(variableNode26);
    operatorNode11->addRHS(variableNode27);
    std::shared_ptr<WhileNode> whileNode3 = std::make_shared<WhileNode>(22);
    whileNode3->setCondition(operatorNode11);
    whileNode3->setStmtLst(stmtLstNode11);
    stmtLstNode10->addStmt(whileNode3);
    std::shared_ptr<StmtLstNode> stmtLstNode12 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode28 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode14 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode11 = std::make_shared<AssignNode>(25);
    assignNode11->setVariable(variableNode28);
    assignNode11->setExpression(constantNode14); stmtLstNode12->addStmt(assignNode11);
    std::shared_ptr<VariableNode> variableNode29 = std::make_shared<VariableNode>("d");
    std::shared_ptr<ConstantNode> constantNode15 = std::make_shared<ConstantNode>(4);
    std::shared_ptr<OperatorNode> operatorNode12 = std::make_shared<OperatorNode>("==");
    operatorNode12->addLHS(variableNode29);
    operatorNode12->addRHS(constantNode15);
    std::shared_ptr<WhileNode> whileNode4 = std::make_shared<WhileNode>(24);
    whileNode4->setCondition(operatorNode12);
    whileNode4->setStmtLst(stmtLstNode12);
    stmtLstNode10->addStmt(whileNode4);
    std::shared_ptr<VariableNode> variableNode30 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode31 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode13 = std::make_shared<OperatorNode>("==");
    operatorNode13->addLHS(variableNode30);
    operatorNode13->addRHS(variableNode31);
    std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(21);
    whileNode2->setCondition(operatorNode13);
    whileNode2->setStmtLst(stmtLstNode10);
    stmtLstNode9->addStmt(whileNode2);
    std::shared_ptr<VariableNode> variableNode32 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode16 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode12 = std::make_shared<AssignNode>(26);
    assignNode12->setVariable(variableNode32);
    assignNode12->setExpression(constantNode16); stmtLstNode9->addStmt(assignNode12);
    std::shared_ptr<StmtLstNode> stmtLstNode13 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode14 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode33 = std::make_shared<VariableNode>("b");
    std::shared_ptr<ConstantNode> constantNode17 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode13 = std::make_shared<AssignNode>(29);
    assignNode13->setVariable(variableNode33);
    assignNode13->setExpression(constantNode17); stmtLstNode14->addStmt(assignNode13);
    std::shared_ptr<StmtLstNode> stmtLstNode15 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode34 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode18 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode14 = std::make_shared<AssignNode>(30);
    assignNode14->setVariable(variableNode34);
    assignNode14->setExpression(constantNode18); stmtLstNode15->addStmt(assignNode14);
    std::shared_ptr<CallNode> callNode3 = std::make_shared<CallNode>(31, "p3");
    stmtLstNode15->addStmt(callNode3);
    std::shared_ptr<VariableNode> variableNode35 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode36 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode14 = std::make_shared<OperatorNode>("==");
    operatorNode14->addLHS(variableNode35);
    operatorNode14->addRHS(variableNode36);
    std::shared_ptr<IfNode> ifNode4 = std::make_shared<IfNode>(28);
    ifNode4->setCondition(operatorNode14);
    ifNode4->setThen(stmtLstNode14);
    ifNode4->setElse(stmtLstNode15);
    stmtLstNode13->addStmt(ifNode4);
    std::shared_ptr<VariableNode> variableNode37 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode38 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode15 = std::make_shared<OperatorNode>("==");
    operatorNode15->addLHS(variableNode37);
    operatorNode15->addRHS(variableNode38);
    std::shared_ptr<WhileNode> whileNode5 = std::make_shared<WhileNode>(27);
    whileNode5->setCondition(operatorNode15);
    whileNode5->setStmtLst(stmtLstNode13);
    stmtLstNode9->addStmt(whileNode5);
    std::shared_ptr<VariableNode> variableNode39 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode40 = std::make_shared<VariableNode>("b");
    std::shared_ptr<OperatorNode> operatorNode16 = std::make_shared<OperatorNode>("==");
    operatorNode16->addLHS(variableNode39);
    operatorNode16->addRHS(variableNode40);
    std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(16);
    ifNode2->setCondition(operatorNode16);
    ifNode2->setThen(stmtLstNode6);
    ifNode2->setElse(stmtLstNode9);
    stmtLstNode5->addStmt(ifNode2);
    std::shared_ptr<VariableNode> variableNode41 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode19 = std::make_shared<ConstantNode>(5);
    std::shared_ptr<AssignNode> assignNode15 = std::make_shared<AssignNode>(32);
    assignNode15->setVariable(variableNode41);
    assignNode15->setExpression(constantNode19); stmtLstNode5->addStmt(assignNode15);
    std::shared_ptr<ProcedureNode> procedureNode2 = std::make_shared<ProcedureNode>("p2");
    procedureNode2->setStmtList(stmtLstNode5);
    rootNode1->addProcedure(procedureNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode16 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode42 = std::make_shared<VariableNode>("c");
    std::shared_ptr<ConstantNode> constantNode20 = std::make_shared<ConstantNode>(4);
    std::shared_ptr<AssignNode> assignNode16 = std::make_shared<AssignNode>(33);
    assignNode16->setVariable(variableNode42);
    assignNode16->setExpression(constantNode20); stmtLstNode16->addStmt(assignNode16);
    std::shared_ptr<StmtLstNode> stmtLstNode17 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode18 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode43 = std::make_shared<VariableNode>("a");
    std::shared_ptr<PrintNode> printNode3 = std::make_shared<PrintNode>(36);
    printNode3->setVariable(variableNode43);
    stmtLstNode18->addStmt(printNode3);
    std::shared_ptr<VariableNode> variableNode44 = std::make_shared<VariableNode>("b");
    std::shared_ptr<ReadNode> readNode4 = std::make_shared<ReadNode>(37);
    readNode4->setVariable(variableNode44);
    stmtLstNode18->addStmt(readNode4);
    std::shared_ptr<VariableNode> variableNode45 = std::make_shared<VariableNode>("b");
    std::shared_ptr<ConstantNode> constantNode21 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode17 = std::make_shared<OperatorNode>("==");
    operatorNode17->addLHS(variableNode45);
    operatorNode17->addRHS(constantNode21);
    std::shared_ptr<WhileNode> whileNode7 = std::make_shared<WhileNode>(35);
    whileNode7->setCondition(operatorNode17);
    whileNode7->setStmtLst(stmtLstNode18);
    stmtLstNode17->addStmt(whileNode7);
    std::shared_ptr<StmtLstNode> stmtLstNode19 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode46 = std::make_shared<VariableNode>("a");
    std::shared_ptr<PrintNode> printNode4 = std::make_shared<PrintNode>(39);
    printNode4->setVariable(variableNode46);
    stmtLstNode19->addStmt(printNode4);
    std::shared_ptr<StmtLstNode> stmtLstNode20 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode47 = std::make_shared<VariableNode>("b");
    std::shared_ptr<ConstantNode> constantNode22 = std::make_shared<ConstantNode>(5);
    std::shared_ptr<AssignNode> assignNode17 = std::make_shared<AssignNode>(40);
    assignNode17->setVariable(variableNode47);
    assignNode17->setExpression(constantNode22); stmtLstNode20->addStmt(assignNode17);
    std::shared_ptr<VariableNode> variableNode48 = std::make_shared<VariableNode>("c");
    std::shared_ptr<ConstantNode> constantNode23 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode18 = std::make_shared<OperatorNode>("==");
    operatorNode18->addLHS(variableNode48);
    operatorNode18->addRHS(constantNode23);
    std::shared_ptr<IfNode> ifNode5 = std::make_shared<IfNode>(38);
    ifNode5->setCondition(operatorNode18);
    ifNode5->setThen(stmtLstNode19);
    ifNode5->setElse(stmtLstNode20);
    stmtLstNode17->addStmt(ifNode5);
    std::shared_ptr<StmtLstNode> stmtLstNode21 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode49 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode24 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode18 = std::make_shared<AssignNode>(42);
    assignNode18->setVariable(variableNode49);
    assignNode18->setExpression(constantNode24); stmtLstNode21->addStmt(assignNode18);
    std::shared_ptr<VariableNode> variableNode50 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode25 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode19 = std::make_shared<OperatorNode>("==");
    operatorNode19->addLHS(variableNode50);
    operatorNode19->addRHS(constantNode25);
    std::shared_ptr<WhileNode> whileNode8 = std::make_shared<WhileNode>(41);
    whileNode8->setCondition(operatorNode19);
    whileNode8->setStmtLst(stmtLstNode21);
    stmtLstNode17->addStmt(whileNode8);
    std::shared_ptr<VariableNode> variableNode51 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode26 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode20 = std::make_shared<OperatorNode>("==");
    operatorNode20->addLHS(variableNode51);
    operatorNode20->addRHS(constantNode26);
    std::shared_ptr<WhileNode> whileNode6 = std::make_shared<WhileNode>(34);
    whileNode6->setCondition(operatorNode20);
    whileNode6->setStmtLst(stmtLstNode17);
    stmtLstNode16->addStmt(whileNode6);
    std::shared_ptr<VariableNode> variableNode52 = std::make_shared<VariableNode>("c");
    std::shared_ptr<ConstantNode> constantNode27 = std::make_shared<ConstantNode>(4);
    std::shared_ptr<AssignNode> assignNode19 = std::make_shared<AssignNode>(43);
    assignNode19->setVariable(variableNode52);
    assignNode19->setExpression(constantNode27); stmtLstNode16->addStmt(assignNode19);
    std::shared_ptr<ProcedureNode> procedureNode3 = std::make_shared<ProcedureNode>("p3");
    procedureNode3->setStmtList(stmtLstNode16);
    rootNode1->addProcedure(procedureNode3);


    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("Basic statements") {
        REQUIRE(adder.containsNext(1, 2));
        REQUIRE(adder.containsNext(2, 3));
    }

    SECTION("Basic negative") {
        REQUIRE_FALSE(adder.containsNext(2, 1));
        REQUIRE_FALSE(adder.containsNext(1, 3));
    }

    SECTION("Next into container") {
        REQUIRE(adder.containsNext(4, 5));
        REQUIRE(adder.containsNext(11, 12));
    }

    SECTION("Next into container negative") {
        REQUIRE_FALSE(adder.containsNext(5, 4));
        REQUIRE_FALSE(adder.containsNext(12, 11));
        REQUIRE_FALSE(adder.containsNext(4, 6));
    }

    SECTION("Within container") {
        REQUIRE(adder.containsNext(6, 7));
        REQUIRE(adder.containsNext(9, 10));
        REQUIRE(adder.containsNext(13, 14));
    }

    SECTION("Within container negative") {
        REQUIRE_FALSE(adder.containsNext(7, 6));
        REQUIRE_FALSE(adder.containsNext(10, 9));
        REQUIRE_FALSE(adder.containsNext(14, 13));
    }

    SECTION("If statement") {
        REQUIRE(adder.containsNext(5, 6));
        REQUIRE(adder.containsNext(5, 9));
        REQUIRE(adder.containsNext(8, 11));
        REQUIRE(adder.containsNext(10, 11));
    }

    SECTION("If statement negative") {
        REQUIRE_FALSE(adder.containsNext(6, 5));
        REQUIRE_FALSE(adder.containsNext(9, 5));
        REQUIRE_FALSE(adder.containsNext(11, 8));
        REQUIRE_FALSE(adder.containsNext(11, 10));
        REQUIRE_FALSE(adder.containsNext(8, 5));
        REQUIRE_FALSE(adder.containsNext(10, 5));
    }

    SECTION("While statement") {
        REQUIRE(adder.containsNext(12, 13));
        REQUIRE(adder.containsNext(12, 15));
        REQUIRE(adder.containsNext(13, 14));
        REQUIRE(adder.containsNext(14, 12));
    }

    SECTION("While statement out") {
        REQUIRE_FALSE(adder.containsNext(13, 12));
        REQUIRE_FALSE(adder.containsNext(14, 13));
        REQUIRE_FALSE(adder.containsNext(12, 14));
        REQUIRE_FALSE(adder.containsNext(14, 15));
    }

    SECTION("Containers within containers") {
        REQUIRE(adder.containsNext(16, 21));
        REQUIRE(adder.containsNext(21, 22));
        REQUIRE(adder.containsNext(22, 23));
        REQUIRE(adder.containsNext(23, 22));
        REQUIRE_FALSE(adder.containsNext(23, 24));
        REQUIRE(adder.containsNext(22, 24));
        REQUIRE(adder.containsNext(24, 21));
    }

    SECTION("Multiple out of containers") {
        REQUIRE(adder.containsNext(19, 32));
        REQUIRE(adder.containsNext(20, 32));
        REQUIRE(adder.containsNext(27, 32));
    }
}