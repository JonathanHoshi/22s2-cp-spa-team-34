// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <stdio.h>
#include "ASTBuilder.h"
#include "AST_parsers/AssignNodeParser.h"
#include "AST_parsers/CallNodeParser.h"
#include "AST_parsers/ConstantNodeParser.h"
#include "AST_parsers/IfNodeParser.h"
#include "AST_parsers/WhileNodeParser.h"
#include "AST_parsers/OperatorNodeParser.h"
#include "AST_parsers/PrintNodeParser.h"
#include "AST_parsers/ReadNodeParser.h"
#include "AST_parsers/ProcedureNodeParser.h"
#include "AST_parsers/RootNodeParser.h"
#include "AST_parsers/StmtLstNodeParser.h"
#include "AST_parsers/VariableNodeParser.h"


void ASTBuilder::buildAST(std::shared_ptr<RootNode> AST, std::string path) {
    std::shared_ptr<AssignNodeParser> assignNodeParser =
        std::make_shared<AssignNodeParser>(path);
    std::shared_ptr<CallNodeParser> callNodeParser =
        std::make_shared<CallNodeParser>(path);
    std::shared_ptr<ConstantNodeParser> constantNodeParser =
        std::make_shared<ConstantNodeParser>(path);
    std::shared_ptr<IfNodeParser> ifNodeParser =
        std::make_shared<IfNodeParser>(path);
    std::shared_ptr<WhileNodeParser> whileNodeParser =
        std::make_shared<WhileNodeParser>(path);
    std::shared_ptr<OperatorNodeParser> operatorNodeParser =
        std::make_shared<OperatorNodeParser>(path);
    std::shared_ptr<PrintNodeParser> printNodeParser =
        std::make_shared<PrintNodeParser>(path);
    std::shared_ptr<ReadNodeParser> readNodeParser =
        std::make_shared<ReadNodeParser>(path);
    std::shared_ptr<ProcedureNodeParser> procedureNodeParser =
        std::make_shared<ProcedureNodeParser>(path);
    std::shared_ptr<RootNodeParser> rootNodeParser =
        std::make_shared<RootNodeParser>(path);
    std::shared_ptr<StmtLstNodeParser> stmtLstNodeParser =
        std::make_shared<StmtLstNodeParser>(path);
    std::shared_ptr<VariableNodeParser> variableNodeParser =
        std::make_shared<VariableNodeParser>(path);
    rootNodeParser->addProcedureNodeParser(procedureNodeParser);
    procedureNodeParser->addStmtLstNodeParser(stmtLstNodeParser);
    stmtLstNodeParser->addAssignNodeParser(assignNodeParser);
    stmtLstNodeParser->addCallNodeParser(callNodeParser);
    stmtLstNodeParser->addIfNodeParser(ifNodeParser);
    stmtLstNodeParser->addPrintNodeParser(printNodeParser);
    stmtLstNodeParser->addReadNodeParser(readNodeParser);
    stmtLstNodeParser->addWhileNodeParser(whileNodeParser);
    assignNodeParser->addOperatorNodeParser(operatorNodeParser);
    assignNodeParser->addVariableNodeParser(variableNodeParser);
    ifNodeParser->addOperatorNodeParser(operatorNodeParser);
    ifNodeParser->addStmtLstNodeParser(stmtLstNodeParser);
    whileNodeParser->addOperatorNodeParser(operatorNodeParser);
    whileNodeParser->addStmtLstNodeParser(stmtLstNodeParser);
    readNodeParser->addVariableNodeParser(variableNodeParser);
    printNodeParser->addVariableNodeParser(variableNodeParser);
    operatorNodeParser->addConstantNodeParser(constantNodeParser);
    operatorNodeParser->addVariableNodeParser(variableNodeParser);
    char* path_arr = new char[path.length() + 1];
    remove(strcpy(path_arr, path.c_str()));
    rootNodeParser->parse(AST.get());
}
