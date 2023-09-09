// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <utility>
#include "RelExprParser.h"

RelExprParser::RelExprParser(std::vector<Token> tokens)
    : SPExpressionParser(tokens) {}

void RelExprParser::addExprParser(std::shared_ptr<SPExpressionParser> parser) {
    exprParser = parser;
}

std::shared_ptr<ExpressionNode> RelExprParser::consumeExpr() {
    std::shared_ptr<ExpressionNode> exprNode;

    exprParser->setPos(getPos());
    exprParser->setStmtNo(getStmtNo());
    exprNode = exprParser->parse();
    setPos(exprParser->getPos());

    return exprNode;
}

std::shared_ptr<ExpressionNode> RelExprParser::parse() {
    std::shared_ptr<OperatorNode> operatorNode;
    std::shared_ptr<ExpressionNode> firstRelFactorNode;
    std::shared_ptr<ExpressionNode> secondRelFactorNode;
    std::string punct;

    firstRelFactorNode = consumeExpr();
    punct = verifyTokenAndGetValue("PUNCTUATION");

    if (PUNCT_SET.find(punct) == PUNCT_SET.end()) {
        throw ParserError(ErrorStatus::SYNTAX);
    }

    traverse();
    operatorNode = std::make_shared<OperatorNode>(punct);
    secondRelFactorNode = consumeExpr();
    operatorNode->addLHS(move(firstRelFactorNode));
    operatorNode->addRHS(move(secondRelFactorNode));

    return operatorNode;
}
