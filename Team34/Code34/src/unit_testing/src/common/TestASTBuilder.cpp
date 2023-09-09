#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include "catch.hpp"
#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "common/ASTUtil.h"
#include "FileReader.h"
#include "common/exceptions/ParserError.h"
#include "sp/node/ReadNode.h"
#include "sp/node/PrintNode.h"
#include "sp/node/CallNode.h"
#include "sp/node/AssignNode.h"
#include "sp/node/ConstantNode.h"
#include "sp/node/VariableNode.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/RootNode.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/IfNode.h"
#include "sp/node/WhileNode.h"
#include "sp/node/OperatorNode.h"
#include "common/ASTBuilder.h"



TEST_CASE("ASTBuilder - Valid cases") {
    SPParserManager parserManager;
    Tokenizer tokenizer;

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "unit_testing" + separator + "tests";
    std::string astBuildPath = filePath.string() + separator + "unit_testing";

    SECTION("Testing case 1 - assign, print, call, read stmts") {
        file = file + separator + "single_procedure_1.txt";
        astBuildPath = astBuildPath + separator + "ast1.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);
        ASTBuilder::buildAST(actualAST, astBuildPath);

        std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("flag");
        std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
        assignNode1->setVariable(variableNode1);
        assignNode1->setExpression(constantNode1); stmtLstNode1->addStmt(assignNode1);
        std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(2);
        readNode1->setVariable(variableNode2);
        stmtLstNode1->addStmt(readNode1);
        std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("y");
        std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(3);
        printNode1->setVariable(variableNode3);
        stmtLstNode1->addStmt(printNode1);
        std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(4, "exampleTwo");
        stmtLstNode1->addStmt(callNode1);
        std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("example");
        procedureNode1->setStmtList(stmtLstNode1);
        rootNode1->addProcedure(procedureNode1);

        REQUIRE(*rootNode1 == *actualAST);
    }

    SECTION("Testing case 2 - if, while stmts") {
        file = file + separator + "single_procedure_2.txt";
        astBuildPath = astBuildPath + separator + "ast2.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);
        ASTBuilder::buildAST(actualAST, astBuildPath);

        std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("y");
        std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(2);
        printNode1->setVariable(variableNode1);
        stmtLstNode2->addStmt(printNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
        std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
        std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
        operatorNode1->addLHS(variableNode3);
        operatorNode1->addRHS(constantNode1);
        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(3);
        assignNode1->setVariable(variableNode2);
        assignNode1->setExpression(operatorNode1); stmtLstNode3->addStmt(assignNode1);
        std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("!=");
        operatorNode3->addLHS(variableNode4);
        operatorNode3->addRHS(constantNode2);
        std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("!");
        operatorNode2->addLHS(operatorNode3);
        std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(1);
        ifNode1->setCondition(operatorNode2);
        ifNode1->setThen(stmtLstNode2);
        ifNode1->setElse(stmtLstNode3);
        stmtLstNode1->addStmt(ifNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(5, "exampleTwo");
        stmtLstNode4->addStmt(callNode1);
        std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("y");
        std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>(">=");
        operatorNode5->addLHS(variableNode5);
        operatorNode5->addRHS(constantNode3);
        std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("<=");
        operatorNode6->addLHS(variableNode6);
        operatorNode6->addRHS(constantNode4);
        std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("&&");
        operatorNode4->addLHS(operatorNode5);
        operatorNode4->addRHS(operatorNode6);
        std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(4);
        whileNode1->setCondition(operatorNode4);
        whileNode1->setStmtLst(stmtLstNode4);
        stmtLstNode1->addStmt(whileNode1);
        std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("example");
        procedureNode1->setStmtList(stmtLstNode1);
        rootNode1->addProcedure(procedureNode1);

        REQUIRE(*rootNode1 == *actualAST);
    }

    SECTION("Testing case 3 - if with nested while stmts") {
        file = file + separator + "single_procedure_3.txt";
        astBuildPath = astBuildPath + separator + "ast3.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);
        ASTBuilder::buildAST(actualAST, astBuildPath);

        std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("y");
        std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(2);
        printNode1->setVariable(variableNode1);
        stmtLstNode2->addStmt(printNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(5, "exampleThree");
        stmtLstNode4->addStmt(callNode1);
        std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("z");
        std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(2);
        std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("<");
        operatorNode2->addLHS(variableNode2);
        operatorNode2->addRHS(constantNode1);
        std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("x");
        std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("y");
        std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>(">");
        operatorNode3->addLHS(variableNode3);
        operatorNode3->addRHS(variableNode4);
        std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("||");
        operatorNode1->addLHS(operatorNode2);
        operatorNode1->addRHS(operatorNode3);
        std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(4);
        whileNode2->setCondition(operatorNode1);
        whileNode2->setStmtLst(stmtLstNode4);
        stmtLstNode3->addStmt(whileNode2);
        std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(6, "exampleTwo");
        stmtLstNode3->addStmt(callNode2);
        std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("y");
        std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>(">=");
        operatorNode5->addLHS(variableNode5);
        operatorNode5->addRHS(constantNode2);
        std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("<=");
        operatorNode6->addLHS(variableNode6);
        operatorNode6->addRHS(constantNode3);
        std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("&&");
        operatorNode4->addLHS(operatorNode5);
        operatorNode4->addRHS(operatorNode6);
        std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(3);
        whileNode1->setCondition(operatorNode4);
        whileNode1->setStmtLst(stmtLstNode3);
        stmtLstNode2->addStmt(whileNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("x");
        std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(1);
        std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>("+");
        operatorNode7->addLHS(variableNode8);
        operatorNode7->addRHS(constantNode4);
        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(7);
        assignNode1->setVariable(variableNode7);
        assignNode1->setExpression(operatorNode7); stmtLstNode5->addStmt(assignNode1);
        std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>("!=");
        operatorNode9->addLHS(variableNode9);
        operatorNode9->addRHS(constantNode5);
        std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("!");
        operatorNode8->addLHS(operatorNode9);
        std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(1);
        ifNode1->setCondition(operatorNode8);
        ifNode1->setThen(stmtLstNode2);
        ifNode1->setElse(stmtLstNode5);
        stmtLstNode1->addStmt(ifNode1);
        std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("example");
        procedureNode1->setStmtList(stmtLstNode1);
        rootNode1->addProcedure(procedureNode1);


        REQUIRE(*rootNode1 == *actualAST);
    }

    SECTION("Testing case 4 - while with nested if stmts") {
        file = file + separator + "single_procedure_4.txt";
        astBuildPath = astBuildPath + separator + "ast4.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);
        ASTBuilder::buildAST(actualAST, astBuildPath);

        std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("y");
        std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(3);
        printNode1->setVariable(variableNode1);
        stmtLstNode3->addStmt(printNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
        std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(5);
        printNode2->setVariable(variableNode2);
        stmtLstNode4->addStmt(printNode2);
        std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("y");
        std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("y");
        std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(2);
        std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("-");
        operatorNode1->addLHS(variableNode4);
        operatorNode1->addRHS(constantNode1);
        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(6);
        assignNode1->setVariable(variableNode3);
        assignNode1->setExpression(operatorNode1); stmtLstNode5->addStmt(assignNode1);
        std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(10);
        std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("<");
        operatorNode2->addLHS(variableNode5);
        operatorNode2->addRHS(constantNode2);
        std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(4);
        ifNode2->setCondition(operatorNode2);
        ifNode2->setThen(stmtLstNode4);
        ifNode2->setElse(stmtLstNode5);
        stmtLstNode3->addStmt(ifNode2);
        std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("x");
        std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(1);
        std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("+");
        operatorNode3->addLHS(variableNode7);
        operatorNode3->addRHS(constantNode3);
        std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(7);
        assignNode2->setVariable(variableNode6);
        assignNode2->setExpression(operatorNode3); stmtLstNode6->addStmt(assignNode2);
        std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("!=");
        operatorNode5->addLHS(variableNode8);
        operatorNode5->addRHS(constantNode4);
        std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("!");
        operatorNode4->addLHS(operatorNode5);
        std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(2);
        ifNode1->setCondition(operatorNode4);
        ifNode1->setThen(stmtLstNode3);
        ifNode1->setElse(stmtLstNode6);
        stmtLstNode2->addStmt(ifNode1);
        std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(8, "exampleTwo");
        stmtLstNode2->addStmt(callNode1);
        std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("y");
        std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>(">=");
        operatorNode7->addLHS(variableNode9);
        operatorNode7->addRHS(constantNode5);
        std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("<=");
        operatorNode8->addLHS(variableNode10);
        operatorNode8->addRHS(constantNode6);
        std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("&&");
        operatorNode6->addLHS(operatorNode7);
        operatorNode6->addRHS(operatorNode8);
        std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(1);
        whileNode1->setCondition(operatorNode6);
        whileNode1->setStmtLst(stmtLstNode2);
        stmtLstNode1->addStmt(whileNode1);
        std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("example");
        procedureNode1->setStmtList(stmtLstNode1);
        rootNode1->addProcedure(procedureNode1);

        REQUIRE(*rootNode1 == *actualAST);
    }
    SECTION("Test case 5 - Nested brackets in expression") {
        file = file + separator + "single_procedure_5.txt";

        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);
        astBuildPath = astBuildPath + separator + "ast5.txt";
        ASTBuilder::buildAST(actualAST, astBuildPath);

        std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("expr");
        std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(8);
        std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(1);
        std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("+");
        operatorNode5->addLHS(variableNode2);
        operatorNode5->addRHS(constantNode2);
        std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(10);
        std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("/");
        operatorNode4->addLHS(operatorNode5);
        operatorNode4->addRHS(constantNode3);
        std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(6);
        std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("*");
        operatorNode3->addLHS(operatorNode4);
        operatorNode3->addRHS(constantNode4);
        std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("%");
        operatorNode2->addLHS(constantNode1);
        operatorNode2->addRHS(operatorNode3);
        std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(19);
        std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("-");
        operatorNode1->addLHS(operatorNode2);
        operatorNode1->addRHS(constantNode5);
        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
        assignNode1->setVariable(variableNode1);
        assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
        std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("example");
        procedureNode1->setStmtList(stmtLstNode1);
        rootNode1->addProcedure(procedureNode1);

        REQUIRE(*rootNode1 == *actualAST);
    }
    SECTION("Test case 6 - Multiple Procedures") {
        file = file + separator + "complex_simple_code.txt";

        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);
        astBuildPath = astBuildPath + separator + "ast6.txt";
        ASTBuilder::buildAST(actualAST, astBuildPath);

        std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("w");
        std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
        std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(2);
        std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(3);
        std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("*");
        operatorNode2->addLHS(constantNode2);
        operatorNode2->addRHS(constantNode3);
        std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
        operatorNode1->addLHS(constantNode1);
        operatorNode1->addRHS(operatorNode2);
        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
        assignNode1->setVariable(variableNode1);
        assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
        std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(20);
        std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(2);
        assignNode2->setVariable(variableNode2);
        assignNode2->setExpression(constantNode4); stmtLstNode1->addStmt(assignNode2);
        std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("y");
        std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("w");
        std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("x");
        std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("/");
        operatorNode3->addLHS(variableNode4);
        operatorNode3->addRHS(variableNode5);
        std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(3);
        assignNode3->setVariable(variableNode3);
        assignNode3->setExpression(operatorNode3); stmtLstNode1->addStmt(assignNode3);
        std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("x");
        std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("w");
        std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(2);
        std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("*");
        operatorNode4->addLHS(variableNode7);
        operatorNode4->addRHS(constantNode5);
        std::shared_ptr<AssignNode> assignNode4 = std::make_shared<AssignNode>(5);
        assignNode4->setVariable(variableNode6);
        assignNode4->setExpression(operatorNode4); stmtLstNode2->addStmt(assignNode4);
        std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("y");
        std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("y");
        std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(1);
        std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("+");
        operatorNode5->addLHS(variableNode9);
        operatorNode5->addRHS(constantNode6);
        std::shared_ptr<AssignNode> assignNode5 = std::make_shared<AssignNode>(7);
        assignNode5->setVariable(variableNode8);
        assignNode5->setExpression(operatorNode5); stmtLstNode4->addStmt(assignNode5);
        std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(8, "Potato");
        stmtLstNode4->addStmt(callNode1);
        std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("y");
        std::shared_ptr<ConstantNode> constantNode7 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("<");
        operatorNode6->addLHS(variableNode10);
        operatorNode6->addRHS(constantNode7);
        std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(6);
        whileNode1->setCondition(operatorNode6);
        whileNode1->setStmtLst(stmtLstNode4);
        stmtLstNode3->addStmt(whileNode1);
        std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("y");
        std::shared_ptr<ConstantNode> constantNode8 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>(">");
        operatorNode7->addLHS(variableNode11);
        operatorNode7->addRHS(constantNode8);
        std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(4);
        ifNode1->setCondition(operatorNode7);
        ifNode1->setThen(stmtLstNode2);
        ifNode1->setElse(stmtLstNode3);
        stmtLstNode1->addStmt(ifNode1);
        std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("Banana");
        procedureNode1->setStmtList(stmtLstNode1);
        rootNode1->addProcedure(procedureNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode5 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode6 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("y");
        std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(10);
        printNode1->setVariable(variableNode12);
        stmtLstNode6->addStmt(printNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode7 = std::make_shared<StmtLstNode>();
        std::shared_ptr<CallNode> callNode2 = std::make_shared<CallNode>(11, "Ditto");
        stmtLstNode7->addStmt(callNode2);
        std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("w");
        std::shared_ptr<ConstantNode> constantNode9 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("!=");
        operatorNode8->addLHS(variableNode13);
        operatorNode8->addRHS(constantNode9);
        std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(9);
        ifNode2->setCondition(operatorNode8);
        ifNode2->setThen(stmtLstNode6);
        ifNode2->setElse(stmtLstNode7);
        stmtLstNode5->addStmt(ifNode2);
        std::shared_ptr<ProcedureNode> procedureNode2 = std::make_shared<ProcedureNode>("Potato");
        procedureNode2->setStmtList(stmtLstNode5);
        rootNode1->addProcedure(procedureNode2);
        std::shared_ptr<StmtLstNode> stmtLstNode8 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode9 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("x");
        std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(13);
        readNode1->setVariable(variableNode14);
        stmtLstNode9->addStmt(readNode1);
        std::shared_ptr<ConstantNode> constantNode10 = std::make_shared<ConstantNode>(2);
        std::shared_ptr<ConstantNode> constantNode11 = std::make_shared<ConstantNode>(0);
        std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>(">=");
        operatorNode9->addLHS(constantNode10);
        operatorNode9->addRHS(constantNode11);
        std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(12);
        whileNode2->setCondition(operatorNode9);
        whileNode2->setStmtLst(stmtLstNode9);
        stmtLstNode8->addStmt(whileNode2);
        std::shared_ptr<VariableNode> variableNode15 = std::make_shared<VariableNode>("w");
        std::shared_ptr<VariableNode> variableNode16 = std::make_shared<VariableNode>("w");
        std::shared_ptr<AssignNode> assignNode6 = std::make_shared<AssignNode>(14);
        assignNode6->setVariable(variableNode15);
        assignNode6->setExpression(variableNode16); stmtLstNode8->addStmt(assignNode6);
        std::shared_ptr<ProcedureNode> procedureNode3 = std::make_shared<ProcedureNode>("Ditto");
        procedureNode3->setStmtList(stmtLstNode8);
        rootNode1->addProcedure(procedureNode3);

        REQUIRE(*rootNode1 == *actualAST);
    }
}


TEST_CASE("ASTBuilder - Testing edge cases") {
    SPParserManager parserManager;
    Tokenizer tokenizer;

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "unit_testing";
    std::string astBuildPath = file + separator + "ast_edgecase.txt";
    file = file + separator + "tests" + separator + "edge_case1.txt";

    std::string contents = FileReader::readFile(file);
    std::vector<Token> tokens = tokenizer.tokenize(contents);
    std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);

    ASTBuilder::buildAST(actualAST, astBuildPath);
    std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("print");
    std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("print");
    std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("*");
    operatorNode1->addLHS(variableNode2);
    operatorNode1->addRHS(constantNode1);
    std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(2);
    assignNode1->setVariable(variableNode1);
    assignNode1->setExpression(operatorNode1); stmtLstNode2->addStmt(assignNode1);
    std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("if");
    std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("if");
    std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("/");
    operatorNode2->addLHS(variableNode4);
    operatorNode2->addRHS(constantNode2);
    std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(3);
    assignNode2->setVariable(variableNode3);
    assignNode2->setExpression(operatorNode2); stmtLstNode2->addStmt(assignNode2);
    std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
    std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("read");
    std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("read");
    std::shared_ptr<ConstantNode> constantNode3 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("%");
    operatorNode3->addLHS(variableNode6);
    operatorNode3->addRHS(constantNode3);
    std::shared_ptr<AssignNode> assignNode3 = std::make_shared<AssignNode>(4);
    assignNode3->setVariable(variableNode5);
    assignNode3->setExpression(operatorNode3); stmtLstNode3->addStmt(assignNode3);
    std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("while");
    std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("while");
    std::shared_ptr<ConstantNode> constantNode4 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode4 = std::make_shared<OperatorNode>("-");
    operatorNode4->addLHS(variableNode8);
    operatorNode4->addRHS(constantNode4);
    std::shared_ptr<AssignNode> assignNode4 = std::make_shared<AssignNode>(5);
    assignNode4->setVariable(variableNode7);
    assignNode4->setExpression(operatorNode4); stmtLstNode3->addStmt(assignNode4);
    std::shared_ptr<VariableNode> variableNode9 = std::make_shared<VariableNode>("call");
    std::shared_ptr<VariableNode> variableNode10 = std::make_shared<VariableNode>("call");
    std::shared_ptr<ConstantNode> constantNode5 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode5 = std::make_shared<OperatorNode>("*");
    operatorNode5->addLHS(variableNode10);
    operatorNode5->addRHS(constantNode5);
    std::shared_ptr<AssignNode> assignNode5 = std::make_shared<AssignNode>(6);
    assignNode5->setVariable(variableNode9);
    assignNode5->setExpression(operatorNode5); stmtLstNode3->addStmt(assignNode5);
    std::shared_ptr<VariableNode> variableNode11 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode6 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode7 = std::make_shared<OperatorNode>("+");
    operatorNode7->addLHS(variableNode11);
    operatorNode7->addRHS(constantNode6);
    std::shared_ptr<VariableNode> variableNode12 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode7 = std::make_shared<ConstantNode>(69);
    std::shared_ptr<ConstantNode> constantNode8 = std::make_shared<ConstantNode>(4);
    std::shared_ptr<OperatorNode> operatorNode9 = std::make_shared<OperatorNode>("/");
    operatorNode9->addLHS(constantNode7);
    operatorNode9->addRHS(constantNode8);
    std::shared_ptr<OperatorNode> operatorNode8 = std::make_shared<OperatorNode>("+");
    operatorNode8->addLHS(variableNode12);
    operatorNode8->addRHS(operatorNode9);
    std::shared_ptr<OperatorNode> operatorNode6 = std::make_shared<OperatorNode>("==");
    operatorNode6->addLHS(operatorNode7);
    operatorNode6->addRHS(operatorNode8);
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(1);
    ifNode1->setCondition(operatorNode6);
    ifNode1->setThen(stmtLstNode2);
    ifNode1->setElse(stmtLstNode3);
    stmtLstNode1->addStmt(ifNode1);
    std::shared_ptr<StmtLstNode> stmtLstNode4 = std::make_shared<StmtLstNode>();
    std::shared_ptr<CallNode> callNode1 = std::make_shared<CallNode>(8, "anotherExample");
    stmtLstNode4->addStmt(callNode1);
    std::shared_ptr<VariableNode> variableNode13 = std::make_shared<VariableNode>("x");
    std::shared_ptr<ConstantNode> constantNode9 = std::make_shared<ConstantNode>(1);
    std::shared_ptr<OperatorNode> operatorNode12 = std::make_shared<OperatorNode>("+");
    operatorNode12->addLHS(variableNode13);
    operatorNode12->addRHS(constantNode9);
    std::shared_ptr<ConstantNode> constantNode10 = std::make_shared<ConstantNode>(5);
    std::shared_ptr<OperatorNode> operatorNode11 = std::make_shared<OperatorNode>("*");
    operatorNode11->addLHS(operatorNode12);
    operatorNode11->addRHS(constantNode10);
    std::shared_ptr<VariableNode> variableNode14 = std::make_shared<VariableNode>("y");
    std::shared_ptr<ConstantNode> constantNode11 = std::make_shared<ConstantNode>(2);
    std::shared_ptr<OperatorNode> operatorNode13 = std::make_shared<OperatorNode>("-");
    operatorNode13->addLHS(variableNode14);
    operatorNode13->addRHS(constantNode11);
    std::shared_ptr<OperatorNode> operatorNode10 = std::make_shared<OperatorNode>("!=");
    operatorNode10->addLHS(operatorNode11);
    operatorNode10->addRHS(operatorNode13);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(7);
    whileNode1->setCondition(operatorNode10);
    whileNode1->setStmtLst(stmtLstNode4);
    stmtLstNode1->addStmt(whileNode1);
    std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("example");
    procedureNode1->setStmtList(stmtLstNode1);
    rootNode1->addProcedure(procedureNode1);


    REQUIRE(*rootNode1 == *actualAST);
}
