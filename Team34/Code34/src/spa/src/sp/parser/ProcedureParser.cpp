// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <string>
#include <utility>
#include "ProcedureParser.h"

ProcedureParser::ProcedureParser(std::vector<Token> tokens)
    : SPParser(tokens) {}

void ProcedureParser::addStmtLstParser(std::shared_ptr<StmtLstParser> parser) {
    stmtLstParser = parser;
}

std::shared_ptr<StmtLstNode> ProcedureParser::consumeStmtLst() {
    std::shared_ptr<StmtLstNode> stmtLstNode;

    stmtLstParser->setPos(getPos());
    stmtLstNode = stmtLstParser->parse();
    setPos(stmtLstParser->getPos());

    return stmtLstNode;
}

std::shared_ptr<ProcedureNode> ProcedureParser::parse() {
    std::shared_ptr<ProcedureNode> procedureNode;
    std::shared_ptr<StmtLstNode> stmtLstNode;
    std::string name;

    verifyTokenAndTraverse("IDENTITY", "procedure");
    name = verifyTokenAndGetValue("IDENTITY");
    traverse();
    verifyTokenAndTraverse("PUNCTUATION", "{");
    stmtLstNode = consumeStmtLst();
    verifyTokenAndTraverse("PUNCTUATION", "}");
    procedureNode = std::make_shared<ProcedureNode>(name);
    procedureNode->setStmtList(move(stmtLstNode));

    return procedureNode;
}
