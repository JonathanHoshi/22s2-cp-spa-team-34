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



TEST_CASE("Valid cases") {
    SPParserManager parserManager;
    Tokenizer tokenizer;

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "unit_testing" + separator + "tests";


    SECTION("Testing case 1 - assign, print, call, read stmts") {
        file = file + separator + "single_procedure_1.txt";

        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);

        std::shared_ptr<RootNode> expectedAST = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLst = std::make_shared<StmtLstNode>();
        std::shared_ptr<ProcedureNode> example = std::make_shared<ProcedureNode>("example");
        std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(1);
        std::shared_ptr<VariableNode> flagNode = std::make_shared<VariableNode>("flag");
        std::shared_ptr<VariableNode> xNode = std::make_shared<VariableNode>("x");
        std::shared_ptr<VariableNode> yNode = std::make_shared<VariableNode>("y");
        std::shared_ptr<ConstantNode> constantNode = std::make_shared<ConstantNode>(0);
        std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(2);
        std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(3);
        std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(4, "exampleTwo");

        assignNode->setVariable(move(flagNode));
        assignNode->setExpression(move(constantNode));
        readNode->setVariable(move(xNode));
        printNode->setVariable(move(yNode));
        stmtLst->addStmt(move(assignNode));
        stmtLst->addStmt(move(readNode));
        stmtLst->addStmt(move(printNode));
        stmtLst->addStmt(move(callNode));
        example->setStmtList(move(stmtLst));
        expectedAST->addProcedure(move(example));

        REQUIRE(*expectedAST == *actualAST);
    }

    SECTION("Testing case 2 - if, while stmts") {
        file = file + separator + "single_procedure_2.txt";

        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);

        std::shared_ptr<RootNode> expectedAST = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLst1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst4 = std::make_shared<StmtLstNode>();
        std::shared_ptr<ProcedureNode> example = std::make_shared<ProcedureNode>("example");
        std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(1);
        std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(4);
        std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(2);
        std::shared_ptr<AssignNode> assign = std::make_shared<AssignNode>(3);
        std::shared_ptr<CallNode> call = std::make_shared<CallNode>(5, "exampleTwo");
        std::shared_ptr<OperatorNode> notNode = std::make_shared<OperatorNode>("!");
        std::shared_ptr<OperatorNode> neq = std::make_shared<OperatorNode>("!=");
        std::shared_ptr<OperatorNode> andNode = std::make_shared<OperatorNode>("&&");
        std::shared_ptr<OperatorNode> mte = std::make_shared<OperatorNode>(">=");
        std::shared_ptr<OperatorNode> lte = std::make_shared<OperatorNode>("<=");
        std::shared_ptr<OperatorNode> plus = std::make_shared<OperatorNode>("+");

        neq->addLHS(std::make_shared<VariableNode>("x"));
        neq->addRHS(std::make_shared<ConstantNode>(0));
        notNode->addLHS(neq);
        mte->addLHS(std::make_shared<VariableNode>("y"));
        mte->addRHS(std::make_shared<ConstantNode>(0));
        lte->addLHS(std::make_shared<VariableNode>("x"));
        lte->addRHS(std::make_shared<ConstantNode>(0));
        andNode->addLHS(mte);
        andNode->addRHS(lte);
        plus->addLHS(std::make_shared<VariableNode>("x"));
        plus->addRHS(std::make_shared<ConstantNode>(1));
        assign->setVariable(std::make_shared<VariableNode>("x"));
        assign->setExpression(plus);
        print->setVariable(std::make_shared<VariableNode>("y"));

        expectedAST->addProcedure(example);
        example->setStmtList(stmtLst1);
        stmtLst1->addStmt(ifNode);
        stmtLst1->addStmt(whileNode);
        stmtLst2->addStmt(print);
        stmtLst3->addStmt(assign);
        stmtLst4->addStmt(call);
        ifNode->setCondition(notNode);
        ifNode->setThen(stmtLst2);
        ifNode->setElse(stmtLst3);
        whileNode->setCondition(andNode);
        whileNode->setStmtLst(stmtLst4);

        REQUIRE(*expectedAST == *actualAST);
    }

    SECTION("Testing case 3 - if with nested while stmts") {
        file = file + separator + "single_procedure_3.txt";

        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);

        std::shared_ptr<RootNode> expectedAST = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLst1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst4 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst5 = std::make_shared<StmtLstNode>();
        std::shared_ptr<ProcedureNode> example = std::make_shared<ProcedureNode>("example");
        std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(1);
        std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(3);
        std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(4);
        std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(2);
        std::shared_ptr<AssignNode> assign = std::make_shared<AssignNode>(7);
        std::shared_ptr<CallNode> call3 = std::make_shared<CallNode>(5, "exampleThree");
        std::shared_ptr<CallNode> call2 = std::make_shared<CallNode>(6, "exampleTwo");
        std::shared_ptr<OperatorNode> notNode = std::make_shared<OperatorNode>("!");
        std::shared_ptr<OperatorNode> neq = std::make_shared<OperatorNode>("!=");
        std::shared_ptr<OperatorNode> andNode = std::make_shared<OperatorNode>("&&");
        std::shared_ptr<OperatorNode> mte = std::make_shared<OperatorNode>(">=");
        std::shared_ptr<OperatorNode> lte = std::make_shared<OperatorNode>("<=");
        std::shared_ptr<OperatorNode> plus = std::make_shared<OperatorNode>("+");
        std::shared_ptr<OperatorNode> lt = std::make_shared<OperatorNode>("<");
        std::shared_ptr<OperatorNode> mt = std::make_shared<OperatorNode>(">");
        std::shared_ptr<OperatorNode> orNode = std::make_shared<OperatorNode>("||");

        lt->addLHS(std::make_shared<VariableNode>("z"));
        lt->addRHS(std::make_shared<ConstantNode>(2));
        mt->addLHS(std::make_shared<VariableNode>("x"));
        mt->addRHS(std::make_shared<VariableNode>("y"));
        orNode->addLHS(lt);
        orNode->addRHS(mt);
        neq->addLHS(std::make_shared<VariableNode>("x"));
        neq->addRHS(std::make_shared<ConstantNode>(0));
        notNode->addLHS(neq);
        mte->addLHS(std::make_shared<VariableNode>("y"));
        mte->addRHS(std::make_shared<ConstantNode>(0));
        lte->addLHS(std::make_shared<VariableNode>("x"));
        lte->addRHS(std::make_shared<ConstantNode>(0));
        andNode->addLHS(mte);
        andNode->addRHS(lte);
        plus->addLHS(std::make_shared<VariableNode>("x"));
        plus->addRHS(std::make_shared<ConstantNode>(1));
        assign->setVariable(std::make_shared<VariableNode>("x"));
        assign->setExpression(plus);
        print->setVariable(std::make_shared<VariableNode>("y"));

        expectedAST->addProcedure(example);
        example->setStmtList(stmtLst1);
        stmtLst1->addStmt(ifNode);
        stmtLst2->addStmt(print);
        stmtLst2->addStmt(whileNode);
        stmtLst3->addStmt(assign);
        stmtLst4->addStmt(whileNode2);
        stmtLst4->addStmt(call2);
        stmtLst5->addStmt(call3);
        ifNode->setCondition(notNode);
        ifNode->setThen(stmtLst2);
        ifNode->setElse(stmtLst3);
        whileNode->setCondition(andNode);
        whileNode->setStmtLst(stmtLst4);
        whileNode2->setCondition(orNode);
        whileNode2->setStmtLst(stmtLst5);

        REQUIRE(*expectedAST == *actualAST);
    }

    SECTION("Testing case 4 - while with nested if stmts") {
        file = file + separator + "single_procedure_4.txt";

        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);

        std::shared_ptr<RootNode> expectedAST = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLst1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst4 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst5 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> stmtLst6 = std::make_shared<StmtLstNode>();
        std::shared_ptr<ProcedureNode> example = std::make_shared<ProcedureNode>("example");
        std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(2);
        std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(4);
        std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(1);
        std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(3);
        std::shared_ptr<PrintNode> print2 = std::make_shared<PrintNode>(5);
        std::shared_ptr<AssignNode> assign2 = std::make_shared<AssignNode>(6);
        std::shared_ptr<AssignNode> assign = std::make_shared<AssignNode>(7);
        std::shared_ptr<CallNode> call = std::make_shared<CallNode>(8, "exampleTwo");
        std::shared_ptr<OperatorNode> notNode = std::make_shared<OperatorNode>("!");
        std::shared_ptr<OperatorNode> neq = std::make_shared<OperatorNode>("!=");
        std::shared_ptr<OperatorNode> andNode = std::make_shared<OperatorNode>("&&");
        std::shared_ptr<OperatorNode> mte = std::make_shared<OperatorNode>(">=");
        std::shared_ptr<OperatorNode> lte = std::make_shared<OperatorNode>("<=");
        std::shared_ptr<OperatorNode> plus = std::make_shared<OperatorNode>("+");
        std::shared_ptr<OperatorNode> minus = std::make_shared<OperatorNode>("-");
        std::shared_ptr<OperatorNode> lt = std::make_shared<OperatorNode>("<");

        lt->addLHS(std::make_shared<VariableNode>("x"));
        lt->addRHS(std::make_shared<ConstantNode>(10));
        minus->addLHS(std::make_shared<VariableNode>("y"));
        minus->addRHS(std::make_shared<ConstantNode>(2));
        neq->addLHS(std::make_shared<VariableNode>("x"));
        neq->addRHS(std::make_shared<ConstantNode>(0));
        notNode->addLHS(neq);
        mte->addLHS(std::make_shared<VariableNode>("y"));
        mte->addRHS(std::make_shared<ConstantNode>(0));
        lte->addLHS(std::make_shared<VariableNode>("x"));
        lte->addRHS(std::make_shared<ConstantNode>(0));
        andNode->addLHS(mte);
        andNode->addRHS(lte);
        plus->addLHS(std::make_shared<VariableNode>("x"));
        plus->addRHS(std::make_shared<ConstantNode>(1));
        assign->setVariable(std::make_shared<VariableNode>("x"));
        assign->setExpression(plus);
        assign2->setVariable(std::make_shared<VariableNode>("y"));
        assign2->setExpression(minus);
        print->setVariable(std::make_shared<VariableNode>("y"));
        print2->setVariable(std::make_shared<VariableNode>("x"));

        expectedAST->addProcedure(example);
        example->setStmtList(stmtLst1);
        stmtLst1->addStmt(whileNode);
        stmtLst2->addStmt(print);
        stmtLst2->addStmt(ifNode2);
        stmtLst3->addStmt(assign);
        stmtLst4->addStmt(ifNode);
        stmtLst4->addStmt(call);
        stmtLst5->addStmt(print2);
        stmtLst6->addStmt(assign2);
        ifNode->setCondition(notNode);
        ifNode->setThen(stmtLst2);
        ifNode->setElse(stmtLst3);
        ifNode2->setCondition(lt);
        ifNode2->setThen(stmtLst5);
        ifNode2->setElse(stmtLst6);
        whileNode->setCondition(andNode);
        whileNode->setStmtLst(stmtLst4);

        REQUIRE(*expectedAST == *actualAST);
    }
    SECTION("Test case 5 - Nested brackets in expression") {
        file = file + separator + "single_procedure_5.txt";

        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);

        std::shared_ptr<RootNode> expectedAST = std::make_shared<RootNode>();
        std::shared_ptr<ProcedureNode> procedure = std::make_shared<ProcedureNode>("example");
        std::shared_ptr<StmtLstNode> stmtLst = std::make_shared<StmtLstNode>();
        std::shared_ptr<AssignNode> assign = std::make_shared<AssignNode>(1);
        std::shared_ptr<OperatorNode> times = std::make_shared<OperatorNode>("*");
        std::shared_ptr<OperatorNode> divide = std::make_shared<OperatorNode>("/");
        std::shared_ptr<OperatorNode> plus = std::make_shared<OperatorNode>("+");
        std::shared_ptr<OperatorNode> minus = std::make_shared<OperatorNode>("-");
        std::shared_ptr<OperatorNode> mod = std::make_shared<OperatorNode>("%");

        expectedAST->addProcedure(procedure);
        procedure->setStmtList(stmtLst);
        stmtLst->addStmt(assign);
        assign->setVariable(std::make_shared<VariableNode>("expr"));
        assign->setExpression(minus);
        plus->addLHS(std::make_shared<VariableNode>("x"));
        plus->addRHS(std::make_shared<ConstantNode>(1));
        divide->addLHS(plus);
        divide->addRHS(std::make_shared<ConstantNode>(10));
        times->addLHS(divide);
        times->addRHS(std::make_shared<ConstantNode>(6));
        mod->addLHS(std::make_shared<ConstantNode>(8));
        mod->addRHS(times);
        minus->addLHS(mod);
        minus->addRHS(std::make_shared<ConstantNode>(19));

        REQUIRE(*expectedAST == *actualAST);
    }
    SECTION("Test case 6 - Multiple Procedures") {
        file = file + separator + "complex_simple_code.txt";

        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);

        std::shared_ptr<RootNode> expectedAST = std::make_shared<RootNode>();
        std::shared_ptr<ProcedureNode> banana = std::make_shared<ProcedureNode>("Banana");
        std::shared_ptr<ProcedureNode> potato = std::make_shared<ProcedureNode>("Potato");
        std::shared_ptr<ProcedureNode> ditto = std::make_shared<ProcedureNode>("Ditto");
        std::shared_ptr<StmtLstNode> bananaStmtLst1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> bananaStmtLst2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> bananaStmtLst3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> bananaStmtLst4 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> potatoStmtLst1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> potatoStmtLst2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> potatoStmtLst3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> dittoStmtLst1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<StmtLstNode> dittoStmtLst2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(4);
        std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(10);
        std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(6);
        std::shared_ptr<WhileNode> whileNode2 = std::make_shared<WhileNode>(13);
        std::shared_ptr<AssignNode> assignW = std::make_shared<AssignNode>(1);
        std::shared_ptr<AssignNode> assignW2 = std::make_shared<AssignNode>(14);
        std::shared_ptr<AssignNode> assignX = std::make_shared<AssignNode>(2);
        std::shared_ptr<AssignNode> assignY = std::make_shared<AssignNode>(3);
        std::shared_ptr<AssignNode> assignX2 = std::make_shared<AssignNode>(5);
        std::shared_ptr<AssignNode> assignY2 = std::make_shared<AssignNode>(7);
        std::shared_ptr<CallNode> callPotato = std::make_shared<CallNode>(8, "Potato");
        std::shared_ptr<CallNode> callDitto = std::make_shared<CallNode>(11, "Ditto");
        std::shared_ptr<PrintNode> printY = std::make_shared<PrintNode>(9);
        std::shared_ptr<ReadNode> readX = std::make_shared<ReadNode>(12);
        std::shared_ptr<OperatorNode> plusW = std::make_shared<OperatorNode>("+");
        std::shared_ptr<OperatorNode> timesW = std::make_shared<OperatorNode>("*");
        std::shared_ptr<OperatorNode> divideY = std::make_shared<OperatorNode>("/");
        std::shared_ptr<OperatorNode> timesX = std::make_shared<OperatorNode>("*");
        std::shared_ptr<OperatorNode> plusY = std::make_shared<OperatorNode>("+");
        std::shared_ptr<OperatorNode> mt = std::make_shared<OperatorNode>(">");
        std::shared_ptr<OperatorNode> lt = std::make_shared<OperatorNode>("<");
        std::shared_ptr<OperatorNode> neq = std::make_shared<OperatorNode>("!=");
        std::shared_ptr<OperatorNode> mte = std::make_shared<OperatorNode>(">=");

        expectedAST->addProcedure(banana);
        expectedAST->addProcedure(potato);
        expectedAST->addProcedure(ditto);
        banana->setStmtList(bananaStmtLst1);
        bananaStmtLst1->addStmt(assignW);
        bananaStmtLst1->addStmt(assignX);
        bananaStmtLst1->addStmt(assignY);
        bananaStmtLst1->addStmt(ifNode);
        ifNode->setThen(bananaStmtLst2);
        ifNode->setElse(bananaStmtLst3);
        bananaStmtLst2->addStmt(assignX2);
        bananaStmtLst3->addStmt(whileNode);
        whileNode->setStmtLst(bananaStmtLst4);
        bananaStmtLst4->addStmt(assignY2);
        bananaStmtLst4->addStmt(callPotato);
        plusW->addLHS(std::make_shared<ConstantNode>(1));
        plusW->addRHS(timesW);
        timesW->addLHS(std::make_shared<ConstantNode>(2));
        timesW->addRHS(std::make_shared<ConstantNode>(3));
        assignW->setVariable(std::make_shared<VariableNode>("w"));
        assignW->setExpression(plusW);
        assignX->setVariable(std::make_shared<VariableNode>("x"));
        assignX->setExpression(std::make_shared<ConstantNode>(20));
        divideY->addLHS(std::make_shared<VariableNode>("w"));
        divideY->addRHS(std::make_shared<VariableNode>("x"));
        assignY->setVariable(std::make_shared<VariableNode>("y"));
        assignY->setExpression(divideY);
        mt->addLHS(std::make_shared<VariableNode>("y"));
        mt->addRHS(std::make_shared<ConstantNode>(0));
        ifNode->setCondition(mt);
        timesX->addLHS(std::make_shared<VariableNode>("w"));
        timesX->addRHS(std::make_shared<ConstantNode>(2));
        assignX2->setVariable(std::make_shared<VariableNode>("x"));
        assignX2->setExpression(timesX);
        lt->addLHS(std::make_shared<VariableNode>("y"));
        lt->addRHS(std::make_shared<ConstantNode>(0));
        whileNode->setCondition(lt);
        plusY->addLHS(std::make_shared<VariableNode>("y"));
        plusY->addRHS(std::make_shared<ConstantNode>(1));
        assignY2->setVariable(std::make_shared<VariableNode>("y"));
        assignY2->setExpression(plusY);

        potato->setStmtList(potatoStmtLst1);
        potatoStmtLst2->addStmt(printY);
        potatoStmtLst1->addStmt(ifNode2);
        potatoStmtLst3->addStmt(callDitto);
        ifNode2->setCondition(neq);
        ifNode2->setThen(potatoStmtLst2);
        ifNode2->setElse(potatoStmtLst3);
        neq->addLHS(std::make_shared<VariableNode>("w"));
        neq->addRHS(std::make_shared<ConstantNode>(0));
        printY->setVariable(std::make_shared<VariableNode>("y"));

        ditto->setStmtList(dittoStmtLst1);
        dittoStmtLst2->addStmt(readX);
        dittoStmtLst1->addStmt(whileNode2);
        dittoStmtLst1->addStmt(assignW2);
        readX->setVariable(std::make_shared<VariableNode>("x"));
        mte->addLHS(std::make_shared<ConstantNode>(2));
        mte->addRHS(std::make_shared<ConstantNode>(0));
        whileNode2->setCondition(mte);
        whileNode2->setStmtLst(dittoStmtLst2);
        assignW2->setVariable(std::make_shared<VariableNode>("w"));
        assignW2->setExpression(std::make_shared<VariableNode>("w"));

        REQUIRE(*expectedAST == *actualAST);
    }
    SECTION("Test case 7 - Multiple white spaces") {
        file = file + separator + "white_space.txt";

        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);
        ASTBuilder::buildAST(actualAST, filePath.string() + separator + "unit_testing" + separator + "ast_white_space.txt");

        std::shared_ptr<RootNode> rootNode1 = std::make_shared<RootNode>();
        std::shared_ptr<StmtLstNode> stmtLstNode1 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode1 = std::make_shared<VariableNode>("y2");
        std::shared_ptr<VariableNode> variableNode2 = std::make_shared<VariableNode>("w");
        std::shared_ptr<VariableNode> variableNode3 = std::make_shared<VariableNode>("z");
        std::shared_ptr<ConstantNode> constantNode1 = std::make_shared<ConstantNode>(3);
        std::shared_ptr<OperatorNode> operatorNode2 = std::make_shared<OperatorNode>("/");
        operatorNode2->addLHS(variableNode3);
        operatorNode2->addRHS(constantNode1);
        std::shared_ptr<OperatorNode> operatorNode1 = std::make_shared<OperatorNode>("+");
        operatorNode1->addLHS(variableNode2);
        operatorNode1->addRHS(operatorNode2);
        std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1);
        assignNode1->setVariable(variableNode1);
        assignNode1->setExpression(operatorNode1); stmtLstNode1->addStmt(assignNode1);
        std::shared_ptr<VariableNode> variableNode4 = std::make_shared<VariableNode>("w");
        std::shared_ptr<ConstantNode> constantNode2 = std::make_shared<ConstantNode>(1);
        std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(2);
        assignNode2->setVariable(variableNode4);
        assignNode2->setExpression(constantNode2); stmtLstNode1->addStmt(assignNode2);
        std::shared_ptr<StmtLstNode> stmtLstNode2 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode5 = std::make_shared<VariableNode>("w");
        std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(4);
        readNode1->setVariable(variableNode5);
        stmtLstNode2->addStmt(readNode1);
        std::shared_ptr<StmtLstNode> stmtLstNode3 = std::make_shared<StmtLstNode>();
        std::shared_ptr<VariableNode> variableNode6 = std::make_shared<VariableNode>("w");
        std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(5);
        printNode1->setVariable(variableNode6);
        stmtLstNode3->addStmt(printNode1);
        std::shared_ptr<VariableNode> variableNode7 = std::make_shared<VariableNode>("z");
        std::shared_ptr<VariableNode> variableNode8 = std::make_shared<VariableNode>("y2");
        std::shared_ptr<OperatorNode> operatorNode3 = std::make_shared<OperatorNode>("!=");
        operatorNode3->addLHS(variableNode7);
        operatorNode3->addRHS(variableNode8);
        std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(3);
        ifNode1->setCondition(operatorNode3);
        ifNode1->setThen(stmtLstNode2);
        ifNode1->setElse(stmtLstNode3);
        stmtLstNode1->addStmt(ifNode1);
        std::shared_ptr<ProcedureNode> procedureNode1 = std::make_shared<ProcedureNode>("example");
        procedureNode1->setStmtList(stmtLstNode1);
        rootNode1->addProcedure(procedureNode1);

        REQUIRE(*rootNode1 == *actualAST);
    }
}


TEST_CASE("Testing edge cases") {
    SPParserManager parserManager;
    Tokenizer tokenizer;

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "unit_testing";

    file = file + separator + "tests" + separator + "edge_case1.txt";
    std::string contents = FileReader::readFile(file);
    std::vector<Token> tokens = tokenizer.tokenize(contents);
    std::shared_ptr<RootNode> actualAST = parserManager.parse(tokens);

    std::shared_ptr<RootNode> expectedAST = std::make_shared<RootNode>();
    std::shared_ptr<ProcedureNode> example = std::make_shared<ProcedureNode>("example");
    expectedAST->addProcedure(example);
    std::shared_ptr<StmtLstNode> firstStmtLst = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> secondStmtLst = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> thirdStmtLst = std::make_shared<StmtLstNode>();
    std::shared_ptr<StmtLstNode> fourthStmtLst = std::make_shared<StmtLstNode>();
    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(1);
    std::shared_ptr<WhileNode> whileNode1 = std::make_shared<WhileNode>(8);
    std::shared_ptr<OperatorNode> eqNode = std::make_shared<OperatorNode>("==");
    std::shared_ptr<OperatorNode> plusNode1 = std::make_shared<OperatorNode>("+");
    example->setStmtList(firstStmtLst);
    firstStmtLst->addStmt(ifNode1);
    firstStmtLst->addStmt(whileNode1);
    plusNode1->addLHS(std::make_shared<VariableNode>("x"));
    plusNode1->addRHS(std::make_shared<ConstantNode>(1));
    eqNode->addLHS(plusNode1);
    std::shared_ptr<OperatorNode> plusNode2 = std::make_shared<OperatorNode>("+");
    std::shared_ptr<OperatorNode> divideNode = std::make_shared<OperatorNode>("/");
    divideNode->addLHS(std::make_shared<ConstantNode>(69));
    divideNode->addRHS(std::make_shared<ConstantNode>(4));
    plusNode2->addLHS(std::make_shared<VariableNode>("y"));
    plusNode2->addRHS(divideNode);
    eqNode->addRHS(plusNode2);
    ifNode1->setCondition(eqNode);
    ifNode1->setThen(secondStmtLst);
    ifNode1->setElse(thirdStmtLst);
    std::shared_ptr<OperatorNode> neqNode = std::make_shared<OperatorNode>("!=");
    std::shared_ptr<OperatorNode> plusNode3 = std::make_shared<OperatorNode>("+");
    std::shared_ptr<OperatorNode> timesNode = std::make_shared<OperatorNode>("*");
    std::shared_ptr<OperatorNode> minusNode = std::make_shared<OperatorNode>("-");
    plusNode3->addLHS(std::make_shared<VariableNode>("x"));
    plusNode3->addRHS(std::make_shared<ConstantNode>(1));
    timesNode->addLHS(plusNode3);
    timesNode->addRHS(std::make_shared<ConstantNode>(5));
    minusNode->addLHS(std::make_shared<VariableNode>("y"));
    minusNode->addRHS(std::make_shared<ConstantNode>(2));
    neqNode->addLHS(timesNode);
    neqNode->addRHS(minusNode);
    whileNode1->setCondition(neqNode);
    whileNode1->setStmtLst(fourthStmtLst);

    std::shared_ptr<AssignNode> assign1 = std::make_shared<AssignNode>(2);
    std::shared_ptr<AssignNode> assign2 = std::make_shared<AssignNode>(3);
    std::shared_ptr<AssignNode> assign3 = std::make_shared<AssignNode>(4);
    std::shared_ptr<AssignNode> assign4 = std::make_shared<AssignNode>(5);
    std::shared_ptr<AssignNode> assign5 = std::make_shared<AssignNode>(6);
    std::shared_ptr<CallNode> callNode = std::make_shared<CallNode>(8, "anotherExample");
    std::shared_ptr<OperatorNode> x = std::make_shared<OperatorNode>("*");
    x->addLHS(std::make_shared<VariableNode>("print"));
    x->addRHS(std::make_shared<ConstantNode>(1));
    assign1->setVariable(std::make_shared<VariableNode>("print"));
    assign1->setExpression(x);
    std::shared_ptr<OperatorNode> y = std::make_shared<OperatorNode>("/");
    y->addLHS(std::make_shared<VariableNode>("if"));
    y->addRHS(std::make_shared<ConstantNode>(2));
    assign2->setVariable(std::make_shared<VariableNode>("if"));
    assign2->setExpression(y);
    std::shared_ptr<OperatorNode> a = std::make_shared<OperatorNode>("%");
    a->addLHS(std::make_shared<VariableNode>("read"));
    a->addRHS(std::make_shared<ConstantNode>(1));
    assign3->setVariable(std::make_shared<VariableNode>("read"));
    assign3->setExpression(a);
    std::shared_ptr<OperatorNode> b = std::make_shared<OperatorNode>("-");
    b->addLHS(std::make_shared<VariableNode>("while"));
    b->addRHS(std::make_shared<ConstantNode>(1));
    assign4->setVariable(std::make_shared<VariableNode>("while"));
    assign4->setExpression(b);
    std::shared_ptr<OperatorNode> c = std::make_shared<OperatorNode>("*");
    c->addLHS(std::make_shared<VariableNode>("call"));
    c->addRHS(std::make_shared<ConstantNode>(2));
    assign5->setVariable(std::make_shared<VariableNode>("call"));
    assign5->setExpression(c);
    secondStmtLst->addStmt(assign1);
    secondStmtLst->addStmt(assign2);
    thirdStmtLst->addStmt(assign3);
    thirdStmtLst->addStmt(assign4);
    thirdStmtLst->addStmt(assign5);
    fourthStmtLst->addStmt(callNode);

    REQUIRE(*expectedAST == *actualAST);
}

TEST_CASE("Invalid cases") {
    SPParserManager parserManager;
    Tokenizer tokenizer;
    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "unit_testing" + separator + "tests";

    SECTION("Test case 1 - Never terminate with ';'") {
        file = file + separator + "invalid_1.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST;
        ErrorStatus errorMsg;

        try {
            actualAST = parserManager.parse(tokens);
        } catch (ParserError e) {
            errorMsg = e.status();
        }

        REQUIRE(errorMsg == ErrorStatus::SYNTAX);
    }
    SECTION("Test case 2 - Space separated number") {
        file = file + separator + "invalid_2.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST;
        ErrorStatus errorMsg;

        try {
            actualAST = parserManager.parse(tokens);
        } catch (ParserError e) {
            errorMsg = e.status();
        }

        REQUIRE(errorMsg == ErrorStatus::SYNTAX);
    }
    SECTION("Test case 3 - Print with constant") {
        file = file + separator + "invalid_3.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST;
        ErrorStatus errorMsg;

        try {
            actualAST = parserManager.parse(tokens);
        } catch (ParserError e) {
            errorMsg = e.status();
        }

        REQUIRE(errorMsg == ErrorStatus::SYNTAX);
    }
    SECTION("Test case 4 - Read with constant") {
        file = file + separator + "invalid_4.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST;
        ErrorStatus errorMsg;

        try {
            actualAST = parserManager.parse(tokens);
        } catch (ParserError e) {
            errorMsg = e.status();
        }

        REQUIRE(errorMsg == ErrorStatus::SYNTAX);
    }
    SECTION("Test case 5 - Call with constant") {
        file = file + separator + "invalid_5.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST;
        ErrorStatus errorMsg;

        try {
            actualAST = parserManager.parse(tokens);
        } catch (ParserError e) {
            errorMsg = e.status();
        }

        REQUIRE(errorMsg == ErrorStatus::SYNTAX);
    }
    SECTION("Test case 6 - Empty StmtLst in If") {
        file = file + separator + "invalid_6.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST;
        ErrorStatus errorMsg;

        try {
            actualAST = parserManager.parse(tokens);
        } catch (ParserError e) {
            errorMsg = e.status();
        }

        REQUIRE(errorMsg == ErrorStatus::SYNTAX);
    }
    SECTION("Test case 7 - Empty StmtLst In While") {
        file = file + separator + "invalid_7.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST;
        ErrorStatus errorMsg;

        try {
            actualAST = parserManager.parse(tokens);
        } catch (ParserError e) {
            errorMsg = e.status();
        }

        REQUIRE(errorMsg == ErrorStatus::SYNTAX);
    }
    SECTION("Test case 8 - Leading zeros") {
        file = file + separator + "invalid_8.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST;
        ErrorStatus errorMsg;

        try {
            actualAST = parserManager.parse(tokens);
        } catch (ParserError e) {
            errorMsg = e.status();
        }

        REQUIRE(tokenizer.hasError());
    }

    SECTION("Test case 9 - Leading zeros") {
        file = file + separator + "invalid_9.txt";
        std::string contents = FileReader::readFile(file);
        std::vector<Token> tokens = tokenizer.tokenize(contents);
        std::shared_ptr<RootNode> actualAST;
        ErrorStatus errorMsg;

        try {
            actualAST = parserManager.parse(tokens);
        } catch (ParserError e) {
            errorMsg = e.status();
        }

        REQUIRE(tokenizer.hasError());
    }
}