// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "SPParserManager.h"
#include "ProgramParser.h"
#include "ReadParser.h"
#include "CallParser.h"
#include "PrintParser.h"
#include "IfParser.h"
#include "WhileParser.h"
#include "AssignParser.h"
#include "CondExprParser.h"
#include "RelExprParser.h"
#include "ExprParser.h"
#include "TermParser.h"
#include "FactorParser.h"

SPParserManager::SPParserManager() {}

std::shared_ptr<RootNode> SPParserManager::parse(std::vector<Token> tokens) {
    std::shared_ptr<ProgramParser> programParser = std::make_shared<ProgramParser>(tokens);
    std::shared_ptr<ProcedureParser> procedureParser = std::make_shared<ProcedureParser>(tokens);
    std::shared_ptr<StmtLstParser> stmtLstParser = std::make_shared<StmtLstParser>(tokens);
    std::shared_ptr<ReadParser> readParser = std::make_shared<ReadParser>(tokens);
    std::shared_ptr<PrintParser> printParser = std::make_shared<PrintParser>(tokens);
    std::shared_ptr<CallParser> callParser = std::make_shared<CallParser>(tokens);
    std::shared_ptr<IfParser> ifParser = std::make_shared<IfParser>(tokens);
    std::shared_ptr<WhileParser> whileParser = std::make_shared<WhileParser>(tokens);
    std::shared_ptr<AssignParser> assignParser = std::make_shared<AssignParser>(tokens);
    std::shared_ptr<CondExprParser> condExprParser = std::make_shared<CondExprParser>(tokens);
    std::shared_ptr<RelExprParser> relExprParser = std::make_shared<RelExprParser>(tokens);
    std::shared_ptr<ExprParser> exprParser = std::make_shared<ExprParser>(tokens);
    std::shared_ptr<TermParser> termParser = std::make_shared<TermParser>(tokens);
    std::shared_ptr<FactorParser> factorParser = std::make_shared<FactorParser>(tokens);

    // establishing chain of responsibility for parsers
    programParser->addProcedureParser(procedureParser);
    procedureParser->addStmtLstParser(stmtLstParser);
    stmtLstParser->addStmtParser(assignParser);
    stmtLstParser->addStmtParser(readParser);
    stmtLstParser->addStmtParser(printParser);
    stmtLstParser->addStmtParser(callParser);
    stmtLstParser->addStmtParser(ifParser);
    stmtLstParser->addStmtParser(whileParser);
    whileParser->addCondExprParser(condExprParser);
    whileParser->addStmtLstParser(stmtLstParser);
    ifParser->addCondExprParser(condExprParser);
    ifParser->addStmtLstParser(stmtLstParser);
    assignParser->addExprParser(exprParser);
    condExprParser->addRelExprParser(relExprParser);
    relExprParser->addExprParser(exprParser);
    exprParser->addTermParser(termParser);
    termParser->addFactorParser(factorParser);
    factorParser->addExprParser(exprParser);

    return programParser->parse();
}

std::shared_ptr<ExpressionNode> SPParserManager::parseExpr(std::vector<Token> tokens) {
    std::shared_ptr<ExprParser> exprParser = std::make_shared<ExprParser>(tokens);
    std::shared_ptr<TermParser> termParser = std::make_shared<TermParser>(tokens);
    std::shared_ptr<FactorParser> factorParser = std::make_shared<FactorParser>(tokens);

    // establishing chain of responsibility for parsers
    exprParser->addTermParser(termParser);
    termParser->addFactorParser(factorParser);
    factorParser->addExprParser(exprParser);

    return exprParser->parse();
}
