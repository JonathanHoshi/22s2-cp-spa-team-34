// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <utility>
#include "AssignParser.h"
#include "sp/node/AssignNode.h"
#include "sp/node/VariableNode.h"

AssignParser::AssignParser(std::vector<Token> tokens)
    : SPStmtParser(tokens) {}

void AssignParser::addExprParser(std::shared_ptr<SPExpressionParser> parser) {
    exprParser = parser;
}

std::shared_ptr<ExpressionNode> AssignParser::consumeExpr() {
    std::shared_ptr<ExpressionNode> exprNode;

    exprParser->setPos(getPos());
    exprParser->setStmtNo(getStmtNo());
    exprNode = exprParser->parse();
    setPos(exprParser->getPos());

    return exprNode;
}

std::shared_ptr<StmtNode> AssignParser::parse() {
    std::shared_ptr<AssignNode> assignNode;
    std::shared_ptr<VariableNode> variableNode;
    std::shared_ptr<ExpressionNode> exprNode;

    if (!checkToken("IDENTITY")) {
        throw ParserError(ErrorStatus::SYNTAX);
    }

    variableNode = std::make_shared<VariableNode>(verifyTokenAndGetValue("IDENTITY"));
    traverse();
    verifyTokenAndTraverse("PUNCTUATION", "=");
    exprNode = consumeExpr();
    verifyTokenAndTraverse("PUNCTUATION", ";");
    assignNode = std::make_shared<AssignNode>(getStmtNo());
    assignNode->setExpression(move(exprNode));
    assignNode->setVariable(move(variableNode));

    return assignNode;
}
