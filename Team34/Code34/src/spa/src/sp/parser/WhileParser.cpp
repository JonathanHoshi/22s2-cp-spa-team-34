// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <utility>
#include "WhileParser.h"
#include "sp/node/WhileNode.h"

WhileParser::WhileParser(std::vector<Token> tokens)
    : SPStmtParser(tokens) {}

void WhileParser::addCondExprParser(std::shared_ptr<SPExpressionParser> parser) {
    condExprParser = parser;
}

void WhileParser::addStmtLstParser(std::shared_ptr<StmtLstParser> parser) {
    stmtLstParser = parser;
}

std::shared_ptr<StmtLstNode> WhileParser::consumeStmtLst() {
    std::shared_ptr<StmtLstNode> stmtLstNode;

    stmtLstParser->setPos(getPos());
    stmtLstNode = stmtLstParser->parse();
    setPos(stmtLstParser->getPos());

    return stmtLstNode;
}

std::shared_ptr<ExpressionNode> WhileParser::consumeCondExpr() {
    std::shared_ptr<ExpressionNode> condExprNode;

    condExprParser->setPos(getPos());
    condExprParser->setStmtNo(getStmtNo());
    condExprNode = condExprParser->parse();
    setPos(condExprParser->getPos());

    return condExprNode;
}

std::shared_ptr<StmtNode> WhileParser::parse() {
    std::shared_ptr<WhileNode> whileNode;
    std::shared_ptr<ExpressionNode> condExprNode;
    std::shared_ptr<StmtLstNode> stmtLstNode;

    if (!checkToken("IDENTITY", "while")) {
        throw ParserError(ErrorStatus::SYNTAX);
    }

    whileNode = std::make_shared<WhileNode>(getStmtNo());
    verifyTokenAndTraverse("IDENTITY", "while");
    verifyTokenAndTraverse("PUNCTUATION", "(");
    condExprNode = consumeCondExpr();
    verifyTokenAndTraverse("PUNCTUATION", ")");
    verifyTokenAndTraverse("PUNCTUATION", "{");
    stmtLstNode = consumeStmtLst();
    verifyTokenAndTraverse("PUNCTUATION", "}");
    whileNode->setCondition(move(condExprNode));
    whileNode->setStmtLst(move(stmtLstNode));

    return whileNode;
}
