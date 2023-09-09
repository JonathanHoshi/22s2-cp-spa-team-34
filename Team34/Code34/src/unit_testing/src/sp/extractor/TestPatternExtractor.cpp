#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"

#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/extractor/PatternExtractorVisitor.h"
#include "stub/StubAssignPatternAdder.cpp"
#include "stub/StubWhilePatternAdder.cpp"
#include "stub/StubIfPatternAdder.cpp"
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

TEST_CASE("Evaluate Pattern - OK - Stub storage contains expected value") {
    StubAssignPatternAdder assignAdder;
    StubIfPatternAdder ifAdder;
    StubWhilePatternAdder whileAdder;
    PatternExtractorVisitor extractor(assignAdder, ifAdder, whileAdder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("+");
    operatorNode2->addLHS(variableNode2);
    operatorNode2->addRHS(variableNode3);
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("z");
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(operatorNode2);
    operatorNode1->addRHS(variableNode4);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
    assignNode1->setVariable(variableNode1);
    assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("y");
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("z");
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("*");
    operatorNode4->addLHS(variableNode7);
    operatorNode4->addRHS(variableNode8);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("+");
    operatorNode3->addLHS(variableNode6);
    operatorNode3->addRHS(operatorNode4);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(2);
    assignNode2->setVariable(variableNode5);
    assignNode2->setExpression(operatorNode3); stmtLstNode1->addStmt(assignNode2);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("main");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);


    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("Basic Full") {
        REQUIRE(assignAdder.checkFullPattern(1, "x", "x + y + z"));
        REQUIRE(!assignAdder.checkFullPattern(1, "x", "y + z"));
        REQUIRE(!assignAdder.checkFullPattern(1, "y", "x + y + z"));
        REQUIRE(!assignAdder.checkFullPattern(2, "x", "x + y + z"));
    }

    SECTION("Left != Right") {
        REQUIRE(!assignAdder.checkPatternExist(1, "y"));
    }

    SECTION("Basic Partial") {
        REQUIRE(assignAdder.checkPartialPattern(1, "x", "x + y"));
        REQUIRE(assignAdder.checkPartialPattern(1, "x", "x + y + z"));

        REQUIRE(!assignAdder.checkPartialPattern(1, "x", "y + z"));
        REQUIRE(!assignAdder.checkPartialPattern(1, "y", "x + y"));
        REQUIRE(!assignAdder.checkPartialPattern(2, "x", "x + y"));
    }

    SECTION("Order of operations") {
        REQUIRE(assignAdder.checkFullPattern(2, "x", "x + y * z"));
        REQUIRE(!assignAdder.checkPartialPattern(2, "x", "x + y"));
        REQUIRE(assignAdder.checkPartialPattern(2, "x", "y * z"));
        REQUIRE(assignAdder.checkPartialPattern(2, "x", "y * z"));
    }
}

TEST_CASE("Evaluate Advanced assign Pattern - OK - Stub storage contains expected value") {
    StubAssignPatternAdder assignAdder;
    StubIfPatternAdder ifAdder;
    StubWhilePatternAdder whileAdder;
    PatternExtractorVisitor extractor(assignAdder, ifAdder, whileAdder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("+");
    operatorNode3->addLHS(variableNode2);
    operatorNode3->addRHS(variableNode3);
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("z");
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("+");
    operatorNode2->addLHS(operatorNode3);
    operatorNode2->addRHS(variableNode4);
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(operatorNode2);
    operatorNode1->addRHS(variableNode5);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
    assignNode1->setVariable(variableNode1);
    assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("y");
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("z");
    std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("+");
    operatorNode6->addLHS(variableNode8);
    operatorNode6->addRHS(variableNode9);
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("+");
    operatorNode5->addLHS(variableNode7);
    operatorNode5->addRHS(operatorNode6);
    std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("+");
    operatorNode4->addLHS(operatorNode5);
    operatorNode4->addRHS(variableNode10);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(2);
    assignNode2->setVariable(variableNode6);
    assignNode2->setExpression(operatorNode4); stmtLstNode1->addStmt(assignNode2);
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode10 = std::make_shared<OperatorNode>("+");
    operatorNode10->addLHS(variableNode12);
    operatorNode10->addRHS(variableNode13);
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>("+");
    operatorNode9->addLHS(operatorNode10);
    operatorNode9->addRHS(constantNode1);
    std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("z");
    std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("+");
    operatorNode8->addLHS(operatorNode9);
    operatorNode8->addRHS(variableNode14);
    std::shared_ptr<VariableNode> variableNode15 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>("+");
    operatorNode7->addLHS(operatorNode8);
    operatorNode7->addRHS(variableNode15);
    std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(3);
    assignNode3->setVariable(variableNode11);
    assignNode3->setExpression(operatorNode7); stmtLstNode1->addStmt(assignNode3);
    std::shared_ptr<VariableNode> variableNode16 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode17 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode18 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode13 = std::make_shared<OperatorNode>("+");
    operatorNode13->addLHS(variableNode17);
    operatorNode13->addRHS(variableNode18);
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<VariableNode> variableNode19 = std::make_shared<VariableNode>("z");
    std::shared_ptr<OperatorNode> operatorNode14 = std::make_shared<OperatorNode>("+");
    operatorNode14->addLHS(constantNode2);
    operatorNode14->addRHS(variableNode19);
    std::shared_ptr<OperatorNode> operatorNode12 = std::make_shared<OperatorNode>("+");
    operatorNode12->addLHS(operatorNode13);
    operatorNode12->addRHS(operatorNode14);
    std::shared_ptr<VariableNode> variableNode20 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode11 = std::make_shared<OperatorNode>("+");
    operatorNode11->addLHS(operatorNode12);
    operatorNode11->addRHS(variableNode20);
    std::shared_ptr<AssignNode> assignNode4 = std::make_shared<AssignNode>(4);
    assignNode4->setVariable(variableNode16);
    assignNode4->setExpression(operatorNode11); stmtLstNode1->addStmt(assignNode4);
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode21 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(6);
    readNode1->setVariable(variableNode21);
    stmtLstNode2->addStmt(readNode1);
    std::shared_ptr<VariableNode> variableNode22 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode23 = std::make_shared<VariableNode>("b");
    std::shared_ptr<VariableNode> variableNode24 = std::make_shared<VariableNode>("c");
    std::shared_ptr<VariableNode> variableNode25 = std::make_shared<VariableNode>("d");
    std::shared_ptr<OperatorNode> operatorNode16 = std::make_shared<OperatorNode>("*");
    operatorNode16->addLHS(variableNode24);
    operatorNode16->addRHS(variableNode25);
    std::shared_ptr<OperatorNode> operatorNode15 = std::make_shared<OperatorNode>("+");
    operatorNode15->addLHS(variableNode23);
    operatorNode15->addRHS(operatorNode16);
    std::shared_ptr<AssignNode> assignNode5 = std::make_shared<AssignNode>(7);
    assignNode5->setVariable(variableNode22);
    assignNode5->setExpression(operatorNode15); stmtLstNode2->addStmt(assignNode5);
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode26 = std::make_shared<VariableNode>("a");
    std::shared_ptr<VariableNode> variableNode27 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode17 = std::make_shared<OperatorNode>("+");
    operatorNode17->addLHS(variableNode27);
    operatorNode17->addRHS(constantNode3);
    std::shared_ptr<AssignNode> assignNode6 = std::make_shared<AssignNode>(8);
    assignNode6->setVariable(variableNode26);
    assignNode6->setExpression(operatorNode17); stmtLstNode3->addStmt(assignNode6);
    std::shared_ptr<VariableNode> variableNode28 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode29 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode19 = std::make_shared<OperatorNode>("+");
    operatorNode19->addLHS(variableNode29);
    operatorNode19->addRHS(constantNode4);
    std::shared_ptr<OperatorNode> operatorNode18 = std::make_shared<OperatorNode>("==");
    operatorNode18->addLHS(variableNode28);
    operatorNode18->addRHS(operatorNode19);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(5);
    ifNode1->setCondition(operatorNode18);
    ifNode1->setThen(stmtLstNode2);
    ifNode1->setElse(stmtLstNode3);
    stmtLstNode1->addStmt(ifNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode30 = std::make_shared<VariableNode>("b");
    std::shared_ptr<VariableNode> variableNode31 = std::make_shared<VariableNode>("b");
    std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode20 = std::make_shared<OperatorNode>("+");
    operatorNode20->addLHS(variableNode31);
    operatorNode20->addRHS(constantNode5);
    std::shared_ptr<AssignNode> assignNode7 = std::make_shared<AssignNode>(10);
    assignNode7->setVariable(variableNode30);
    assignNode7->setExpression(operatorNode20); stmtLstNode4->addStmt(assignNode7);
    std::shared_ptr<VariableNode> variableNode32 = std::make_shared<VariableNode>("x");
    std::shared_ptr<VariableNode> variableNode33 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode23 = std::make_shared<OperatorNode>("+");
    operatorNode23->addLHS(variableNode32);
    operatorNode23->addRHS(variableNode33);
    std::shared_ptr<VariableNode> variableNode34 = std::make_shared<VariableNode>("z");
    std::shared_ptr<OperatorNode> operatorNode22 = std::make_shared<OperatorNode>("+");
    operatorNode22->addLHS(operatorNode23);
    operatorNode22->addRHS(variableNode34);
    std::shared_ptr<VariableNode> variableNode35 = std::make_shared<VariableNode>("y");
    std::shared_ptr<VariableNode> variableNode36 = std::make_shared<VariableNode>("a");
    std::shared_ptr<OperatorNode> operatorNode25 = std::make_shared<OperatorNode>("+");
    operatorNode25->addLHS(variableNode35);
    operatorNode25->addRHS(variableNode36);
    std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode24 = std::make_shared<OperatorNode>("+");
    operatorNode24->addLHS(operatorNode25);
    operatorNode24->addRHS(constantNode6);
    std::shared_ptr<OperatorNode> operatorNode21 = std::make_shared<OperatorNode>("==");
    operatorNode21->addLHS(operatorNode22);
    operatorNode21->addRHS(operatorNode24);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(9);
    whileNode1->setCondition(operatorNode21);
    whileNode1->setStmtLst(stmtLstNode4);
    stmtLstNode1->addStmt(whileNode1);
    std::shared_ptr<VariableNode> variableNode37 = std::make_shared<VariableNode>("print");
    std::shared_ptr<VariableNode> variableNode38 = std::make_shared<VariableNode>("read");
    std::shared_ptr<VariableNode> variableNode39 = std::make_shared<VariableNode>("procedure");
    std::shared_ptr<ConstantNode> constantNode7 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<OperatorNode> operatorNode27 = std::make_shared<OperatorNode>("*");
    operatorNode27->addLHS(variableNode39);
    operatorNode27->addRHS(constantNode7);
    std::shared_ptr<OperatorNode> operatorNode26 = std::make_shared<OperatorNode>("+");
    operatorNode26->addLHS(variableNode38);
    operatorNode26->addRHS(operatorNode27);
    std::shared_ptr<AssignNode> assignNode8 = std::make_shared<AssignNode>(11);
    assignNode8->setVariable(variableNode37);
    assignNode8->setExpression(operatorNode26); stmtLstNode1->addStmt(assignNode8);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("main");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);

    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("Brackets") {
        REQUIRE(assignAdder.checkFullPattern(1, "x", "x + y + z + y"));
        REQUIRE(assignAdder.checkPartialPattern(1, "x", "x + y"));
        REQUIRE(assignAdder.checkPartialPattern(1, "x", "(((x + y)))"));

        REQUIRE(!assignAdder.checkFullPattern(2, "x", "x + y + z + y"));
        REQUIRE(assignAdder.checkFullPattern(2, "x", "x + (y + z) + y"));
        REQUIRE(!assignAdder.checkPartialPattern(2, "x", "x + y"));
        REQUIRE(assignAdder.checkPartialPattern(2, "x", "y + z"));

        REQUIRE(assignAdder.checkFullPattern(3, "x", "x + y + 3 + z + y"));
        REQUIRE(assignAdder.checkPartialPattern(3, "x", "x + y + 3"));
        REQUIRE(!assignAdder.checkPartialPattern(3, "x", "z + y"));

        REQUIRE(assignAdder.checkPartialPattern(4, "x", "x + y"));
        REQUIRE(assignAdder.checkPartialPattern(4, "x", "3 + z"));
        REQUIRE(assignAdder.checkPartialPattern(4, "x", "x + y + (3 + z)"));
        REQUIRE(!assignAdder.checkPartialPattern(4, "x", "(3 + z) + y"));
    }

    SECTION("Containers conditions don't apply to assign patterns") {
        REQUIRE(!assignAdder.checkPatternExist(5, "x"));
        REQUIRE(!assignAdder.checkPatternExist(5, "y"));
        REQUIRE(!assignAdder.checkPatternExist(9, "x"));
        REQUIRE(!assignAdder.checkPatternExist(9, "y"));
        REQUIRE(!assignAdder.checkPatternExist(9, "z"));
    }

    SECTION("Statements within containers") {
        REQUIRE(!assignAdder.checkPatternExist(6, "a"));
        REQUIRE(assignAdder.checkFullPattern(7, "a", "b + c * d"));
    }

    SECTION("Keywords within statements") {
        REQUIRE(assignAdder.checkFullPattern(11, "print", "read + procedure * 3"));
    }

    SECTION("While Pattern Basic") {
        REQUIRE(whileAdder.contains(9, "x"));
        REQUIRE(whileAdder.contains(9, "y"));
        REQUIRE(whileAdder.contains(9, "z"));
        REQUIRE(whileAdder.contains(9, "a"));
    }

    SECTION("While Pattern Negative") {
        REQUIRE_FALSE(whileAdder.contains(9, "1"));
        REQUIRE_FALSE(whileAdder.contains(5, "x"));
        REQUIRE_FALSE(whileAdder.contains(5, "y"));
    }

    SECTION("If Pattern Basic") {
        REQUIRE(ifAdder.contains(5, "x"));
        REQUIRE(ifAdder.contains(5, "y"));
    }

    SECTION("If Pattern Negative") {
        REQUIRE_FALSE(ifAdder.contains(5, "1"));
        REQUIRE_FALSE(ifAdder.contains(9, "x"));
        REQUIRE_FALSE(ifAdder.contains(9, "y"));
        REQUIRE_FALSE(ifAdder.contains(9, "z"));
        REQUIRE_FALSE(ifAdder.contains(9, "a"));
    }
}

TEST_CASE("Evaluate IfWhile Pattern - OK - Stub storage contains expected value") {
    StubAssignPatternAdder assignAdder;
    StubIfPatternAdder ifAdder;
    StubWhilePatternAdder whileAdder;
    PatternExtractorVisitor extractor(assignAdder, ifAdder, whileAdder);

    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("k");
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("l");
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("m");
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
    operatorNode1->addLHS(variableNode2);
    operatorNode1->addRHS(variableNode3);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(3);
    assignNode1->setVariable(variableNode1);
    assignNode1->setExpression(operatorNode1); stmtLstNode3->addStmt(assignNode1);
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("i");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("==");
    operatorNode3->addLHS(variableNode4);
    operatorNode3->addRHS(constantNode1);
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("j");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("==");
    operatorNode4->addLHS(variableNode5);
    operatorNode4->addRHS(constantNode2);
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("&&");
    operatorNode2->addLHS(operatorNode3);
    operatorNode2->addRHS(operatorNode4);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(2);
    whileNode1->setCondition(operatorNode2);
    whileNode1->setStmtLst(stmtLstNode3);
    stmtLstNode2->addStmt(whileNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("n");
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("o");
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("p");
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("+");
    operatorNode5->addLHS(variableNode7);
    operatorNode5->addRHS(variableNode8);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(5);
    assignNode2->setVariable(variableNode6);
    assignNode2->setExpression(operatorNode5); stmtLstNode5->addStmt(assignNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("w");
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(7);
    assignNode3->setVariable(variableNode9);
    assignNode3->setExpression(constantNode3); stmtLstNode6->addStmt(assignNode3);
    std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("v");
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(3);
    std::shared_ptr<AssignNode> assignNode4 = std::make_shared<AssignNode>(8);
    assignNode4->setVariable(variableNode10);
    assignNode4->setExpression(constantNode4); stmtLstNode7->addStmt(assignNode4);
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("z");
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("y");
    std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("==");
    operatorNode6->addLHS(variableNode11);
    operatorNode6->addRHS(variableNode12);
    std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(6);
    ifNode2->setCondition(operatorNode6);
    ifNode2->setThen(stmtLstNode6);
    ifNode2->setElse(stmtLstNode7);
    stmtLstNode5->addStmt(ifNode2);
    std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("k");
    std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("==");
    operatorNode8->addLHS(variableNode13);
    operatorNode8->addRHS(constantNode5);
    std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("l");
    std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>("==");
    operatorNode9->addLHS(variableNode14);
    operatorNode9->addRHS(constantNode6);
    std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>("&&");
    operatorNode7->addLHS(operatorNode8);
    operatorNode7->addRHS(operatorNode9);
    std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(4);
    whileNode2->setCondition(operatorNode7);
    whileNode2->setStmtLst(stmtLstNode5);
    stmtLstNode4->addStmt(whileNode2);
    std::shared_ptr<VariableNode> variableNode15 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode7 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode11 = std::make_shared<OperatorNode>("==");
    operatorNode11->addLHS(variableNode15);
    operatorNode11->addRHS(constantNode7);
    std::shared_ptr<VariableNode> variableNode16 = std::make_shared<VariableNode>("b");
    std::shared_ptr<VariableNode> variableNode17 = std::make_shared<VariableNode>("c");
    std::shared_ptr<VariableNode> variableNode18 = std::make_shared<VariableNode>("d");
    std::shared_ptr<OperatorNode> operatorNode16 = std::make_shared<OperatorNode>("+");
    operatorNode16->addLHS(variableNode17);
    operatorNode16->addRHS(variableNode18);
    std::shared_ptr<VariableNode> variableNode19 = std::make_shared<VariableNode>("e");
    std::shared_ptr<OperatorNode> operatorNode15 = std::make_shared<OperatorNode>("*");
    operatorNode15->addLHS(operatorNode16);
    operatorNode15->addRHS(variableNode19);
    std::shared_ptr<VariableNode> variableNode20 = std::make_shared<VariableNode>("f");
    std::shared_ptr<OperatorNode> operatorNode14 = std::make_shared<OperatorNode>("+");
    operatorNode14->addLHS(operatorNode15);
    operatorNode14->addRHS(variableNode20);
    std::shared_ptr<OperatorNode> operatorNode13 = std::make_shared<OperatorNode>("==");
    operatorNode13->addLHS(variableNode16);
    operatorNode13->addRHS(operatorNode14);
    std::shared_ptr<VariableNode> variableNode21 = std::make_shared<VariableNode>("h");
    std::shared_ptr<ConstantNode> constantNode8 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode17 = std::make_shared<OperatorNode>("==");
    operatorNode17->addLHS(variableNode21);
    operatorNode17->addRHS(constantNode8);
    std::shared_ptr<OperatorNode> operatorNode12 = std::make_shared<OperatorNode>("&&");
    operatorNode12->addLHS(operatorNode13);
    operatorNode12->addRHS(operatorNode17);
    std::shared_ptr<OperatorNode> operatorNode10 = std::make_shared<OperatorNode>("&&");
    operatorNode10->addLHS(operatorNode11);
    operatorNode10->addRHS(operatorNode12);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(1);
    ifNode1->setCondition(operatorNode10);
    ifNode1->setThen(stmtLstNode2);
    ifNode1->setElse(stmtLstNode4);
    stmtLstNode1->addStmt(ifNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode8 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode22 = std::make_shared<VariableNode>("r");
    std::shared_ptr<VariableNode> variableNode23 = std::make_shared<VariableNode>("s");
    std::shared_ptr<VariableNode> variableNode24 = std::make_shared<VariableNode>("t");
    std::shared_ptr<OperatorNode> operatorNode18 = std::make_shared<OperatorNode>("+");
    operatorNode18->addLHS(variableNode23);
    operatorNode18->addRHS(variableNode24);
    std::shared_ptr<AssignNode> assignNode5 = std::make_shared<AssignNode>(10);
    assignNode5->setVariable(variableNode22);
    assignNode5->setExpression(operatorNode18); stmtLstNode8->addStmt(assignNode5);
    std::shared_ptr<VariableNode> variableNode25 = std::make_shared<VariableNode>("q");
    std::shared_ptr<ConstantNode> constantNode9 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode19 = std::make_shared<OperatorNode>("==");
    operatorNode19->addLHS(variableNode25);
    operatorNode19->addRHS(constantNode9);
    std::shared_ptr<WhileNode> whileNode3 = std::make_shared<WhileNode>(9);
    whileNode3->setCondition(operatorNode19);
    whileNode3->setStmtLst(stmtLstNode8);
    stmtLstNode1->addStmt(whileNode3);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("a1");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode9 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode10 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode11 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode26 = std::make_shared<VariableNode>("k");
    std::shared_ptr<VariableNode> variableNode27 = std::make_shared<VariableNode>("l");
    std::shared_ptr<VariableNode> variableNode28 = std::make_shared<VariableNode>("m");
    std::shared_ptr<OperatorNode> operatorNode20 = std::make_shared<OperatorNode>("+");
    operatorNode20->addLHS(variableNode27);
    operatorNode20->addRHS(variableNode28);
    std::shared_ptr<AssignNode> assignNode6 = std::make_shared<AssignNode>(13);
    assignNode6->setVariable(variableNode26);
    assignNode6->setExpression(operatorNode20); stmtLstNode11->addStmt(assignNode6);
    std::shared_ptr<StmtLstNode> stmtLstNode12 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode13 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode29 = std::make_shared<VariableNode>("n");
    std::shared_ptr<VariableNode> variableNode30 = std::make_shared<VariableNode>("o");
    std::shared_ptr<VariableNode> variableNode31 = std::make_shared<VariableNode>("p");
    std::shared_ptr<OperatorNode> operatorNode21 = std::make_shared<OperatorNode>("+");
    operatorNode21->addLHS(variableNode30);
    operatorNode21->addRHS(variableNode31);
    std::shared_ptr<AssignNode> assignNode7 = std::make_shared<AssignNode>(15);
    assignNode7->setVariable(variableNode29);
    assignNode7->setExpression(operatorNode21); stmtLstNode13->addStmt(assignNode7);
    std::shared_ptr<VariableNode> variableNode32 = std::make_shared<VariableNode>("k");
    std::shared_ptr<ConstantNode> constantNode10 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode23 = std::make_shared<OperatorNode>("==");
    operatorNode23->addLHS(variableNode32);
    operatorNode23->addRHS(constantNode10);
    std::shared_ptr<VariableNode> variableNode33 = std::make_shared<VariableNode>("l");
    std::shared_ptr<ConstantNode> constantNode11 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode24 = std::make_shared<OperatorNode>("==");
    operatorNode24->addLHS(variableNode33);
    operatorNode24->addRHS(constantNode11);
    std::shared_ptr<OperatorNode> operatorNode22 = std::make_shared<OperatorNode>("&&");
    operatorNode22->addLHS(operatorNode23);
    operatorNode22->addRHS(operatorNode24);
    std::shared_ptr<WhileNode> whileNode5 = std::make_shared<WhileNode>(14);
    whileNode5->setCondition(operatorNode22);
    whileNode5->setStmtLst(stmtLstNode13);
    stmtLstNode12->addStmt(whileNode5);
    std::shared_ptr<VariableNode> variableNode34 = std::make_shared<VariableNode>("i");
    std::shared_ptr<ConstantNode> constantNode12 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode26 = std::make_shared<OperatorNode>("==");
    operatorNode26->addLHS(variableNode34);
    operatorNode26->addRHS(constantNode12);
    std::shared_ptr<VariableNode> variableNode35 = std::make_shared<VariableNode>("j");
    std::shared_ptr<ConstantNode> constantNode13 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode27 = std::make_shared<OperatorNode>("==");
    operatorNode27->addLHS(variableNode35);
    operatorNode27->addRHS(constantNode13);
    std::shared_ptr<OperatorNode> operatorNode25 = std::make_shared<OperatorNode>("&&");
    operatorNode25->addLHS(operatorNode26);
    operatorNode25->addRHS(operatorNode27);
    std::shared_ptr<IfNode> ifNode3 = std::make_shared<IfNode>(12);
    ifNode3->setCondition(operatorNode25);
    ifNode3->setThen(stmtLstNode11);
    ifNode3->setElse(stmtLstNode12);
    stmtLstNode10->addStmt(ifNode3);
    std::shared_ptr<VariableNode> variableNode36 = std::make_shared<VariableNode>("a");
    std::shared_ptr<ConstantNode> constantNode14 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode29 = std::make_shared<OperatorNode>("==");
    operatorNode29->addLHS(variableNode36);
    operatorNode29->addRHS(constantNode14);
    std::shared_ptr<VariableNode> variableNode37 = std::make_shared<VariableNode>("b");
    std::shared_ptr<VariableNode> variableNode38 = std::make_shared<VariableNode>("c");
    std::shared_ptr<VariableNode> variableNode39 = std::make_shared<VariableNode>("d");
    std::shared_ptr<OperatorNode> operatorNode34 = std::make_shared<OperatorNode>("+");
    operatorNode34->addLHS(variableNode38);
    operatorNode34->addRHS(variableNode39);
    std::shared_ptr<VariableNode> variableNode40 = std::make_shared<VariableNode>("e");
    std::shared_ptr<OperatorNode> operatorNode33 = std::make_shared<OperatorNode>("*");
    operatorNode33->addLHS(operatorNode34);
    operatorNode33->addRHS(variableNode40);
    std::shared_ptr<VariableNode> variableNode41 = std::make_shared<VariableNode>("f");
    std::shared_ptr<OperatorNode> operatorNode32 = std::make_shared<OperatorNode>("+");
    operatorNode32->addLHS(operatorNode33);
    operatorNode32->addRHS(variableNode41);
    std::shared_ptr<OperatorNode> operatorNode31 = std::make_shared<OperatorNode>("==");
    operatorNode31->addLHS(variableNode37);
    operatorNode31->addRHS(operatorNode32);
    std::shared_ptr<VariableNode> variableNode42 = std::make_shared<VariableNode>("h");
    std::shared_ptr<ConstantNode> constantNode15 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode35 = std::make_shared<OperatorNode>("==");
    operatorNode35->addLHS(variableNode42);
    operatorNode35->addRHS(constantNode15);
    std::shared_ptr<OperatorNode> operatorNode30 = std::make_shared<OperatorNode>("&&");
    operatorNode30->addLHS(operatorNode31);
    operatorNode30->addRHS(operatorNode35);
    std::shared_ptr<OperatorNode> operatorNode28 = std::make_shared<OperatorNode>("&&");
    operatorNode28->addLHS(operatorNode29);
    operatorNode28->addRHS(operatorNode30);
    std::shared_ptr<WhileNode> whileNode4 = std::make_shared<WhileNode>(11);
    whileNode4->setCondition(operatorNode28);
    whileNode4->setStmtLst(stmtLstNode10);
    stmtLstNode9->addStmt(whileNode4);
    std::shared_ptr<VariableNode> variableNode43 = std::make_shared<VariableNode>("r");
    std::shared_ptr<VariableNode> variableNode44 = std::make_shared<VariableNode>("s");
    std::shared_ptr<VariableNode> variableNode45 = std::make_shared<VariableNode>("t");
    std::shared_ptr<OperatorNode> operatorNode36 = std::make_shared<OperatorNode>("+");
    operatorNode36->addLHS(variableNode44);
    operatorNode36->addRHS(variableNode45);
    std::shared_ptr<AssignNode> assignNode8 = std::make_shared<AssignNode>(16);
    assignNode8->setVariable(variableNode43);
    assignNode8->setExpression(operatorNode36); stmtLstNode9->addStmt(assignNode8);
    std::shared_ptr<ProcedureNode> procedureNode2 = std::make_shared<ProcedureNode>("a2");
    procedureNode2->setStmtList(stmtLstNode9);
    rootNode1->addProcedure(procedureNode2);

    extractor.begin(*rootNode1);
    extractor.transfer();

    SECTION("If Pattern long expressions") {
        REQUIRE(ifAdder.contains(1, "a"));
        REQUIRE(ifAdder.contains(1, "b"));
        REQUIRE(ifAdder.contains(1, "c"));
        REQUIRE(ifAdder.contains(1, "d"));
        REQUIRE(ifAdder.contains(1, "e"));
        REQUIRE(ifAdder.contains(1, "f"));
        REQUIRE(ifAdder.contains(1, "h"));
        REQUIRE(ifAdder.contains(6, "y"));
        REQUIRE(ifAdder.contains(6, "z"));
        REQUIRE(ifAdder.contains(12, "i"));
        REQUIRE(ifAdder.contains(12, "j"));
    }

    SECTION("If Pattern negative") {
        REQUIRE(ifAdder.size(1) == 7);
        REQUIRE(ifAdder.size(6) == 2);
        REQUIRE(ifAdder.size(12) == 2);
    }

    SECTION("While Pattern long expressions") {
        REQUIRE(whileAdder.contains(2, "i"));
        REQUIRE(whileAdder.contains(2, "j"));
        REQUIRE(whileAdder.contains(4, "k"));
        REQUIRE(whileAdder.contains(4, "l"));
        REQUIRE(whileAdder.contains(9, "q"));
        REQUIRE(whileAdder.contains(11, "a"));
        REQUIRE(whileAdder.contains(11, "b"));
        REQUIRE(whileAdder.contains(11, "c"));
        REQUIRE(whileAdder.contains(11, "d"));
        REQUIRE(whileAdder.contains(11, "e"));
        REQUIRE(whileAdder.contains(11, "f"));
        REQUIRE(whileAdder.contains(11, "h"));
        REQUIRE(whileAdder.contains(14, "k"));
        REQUIRE(whileAdder.contains(14, "l"));
    }

    SECTION("While Pattern long expressions") {
        REQUIRE(whileAdder.contains(2, "i"));
        REQUIRE(whileAdder.contains(2, "j"));
        REQUIRE(whileAdder.contains(4, "k"));
        REQUIRE(whileAdder.contains(4, "l"));
        REQUIRE(whileAdder.contains(9, "q"));
        REQUIRE(whileAdder.contains(11, "a"));
        REQUIRE(whileAdder.contains(11, "b"));
        REQUIRE(whileAdder.contains(11, "c"));
        REQUIRE(whileAdder.contains(11, "d"));
        REQUIRE(whileAdder.contains(11, "e"));
        REQUIRE(whileAdder.contains(11, "f"));
        REQUIRE(whileAdder.contains(11, "h"));
        REQUIRE(whileAdder.contains(14, "k"));
        REQUIRE(whileAdder.contains(14, "l"));
    }

    SECTION("While Pattern negative") {
        REQUIRE(whileAdder.size(2) == 2);
        REQUIRE(whileAdder.size(4) == 2);
        REQUIRE(whileAdder.size(9) == 1);
        REQUIRE(whileAdder.size(11) == 7);
        REQUIRE(whileAdder.size(14) == 2);
    }

    SECTION("Assign nested within containers") {
        REQUIRE(assignAdder.checkFullPattern(3, "k", "l + m"));
        REQUIRE(assignAdder.checkFullPattern(5, "n", "o + p"));
        REQUIRE(assignAdder.checkFullPattern(7, "w", "3"));
        REQUIRE(assignAdder.checkFullPattern(8, "v", "3"));
        REQUIRE(assignAdder.checkFullPattern(10, "r", "s + t"));
        REQUIRE(assignAdder.checkFullPattern(13, "k", "l + m"));
        REQUIRE(assignAdder.checkFullPattern(15, "n", "o + p"));
        REQUIRE(assignAdder.checkFullPattern(16, "r", "s + t"));
        REQUIRE(assignAdder.patternMap.size() == 8);
    }
}
