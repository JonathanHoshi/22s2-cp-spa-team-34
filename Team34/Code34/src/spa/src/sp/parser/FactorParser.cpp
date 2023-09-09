// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "FactorParser.h"
#include "sp/node/VariableNode.h"
#include "sp/node/ConstantNode.h"

FactorParser::FactorParser(std::vector<Token> tokens)
    : SPExpressionParser(tokens) {}

void FactorParser::addExprParser(std::shared_ptr<SPExpressionParser> parser) {
    exprParser = parser;
}

std::shared_ptr<ExpressionNode> FactorParser::consumeExpr() {
    std::shared_ptr<ExpressionNode> exprNode;

    exprParser->setPos(getPos());
    exprParser->setStmtNo(getStmtNo());
    exprNode = exprParser->parse();
    setPos(exprParser->getPos());

    return exprNode;
}

std::shared_ptr<ExpressionNode> FactorParser::processVariable() {
    std::shared_ptr<VariableNode> variableNode =
        std::make_shared<VariableNode>(verifyTokenAndGetValue("IDENTITY"));
    traverse();

    return variableNode;
}

std::shared_ptr<ExpressionNode> FactorParser::processConstant() {
    std::shared_ptr<ConstantNode> constantNode =
        std::make_shared<ConstantNode>(stoi(verifyTokenAndGetValue("NUMBER")));
    traverse();

    return constantNode;
}

std::shared_ptr<ExpressionNode> FactorParser::processExpr() {
    std::shared_ptr<ExpressionNode> exprNode;

    verifyTokenAndTraverse("PUNCTUATION", "(");
    exprNode = consumeExpr();
    verifyTokenAndTraverse("PUNCTUATION", ")");
    return exprNode;
}

std::shared_ptr<ExpressionNode> FactorParser::parse() {
    std::string type = currToken.getType();

    if (factor_map.find(type) == factor_map.end()) {
        throw ParserError(ErrorStatus::SYNTAX);
    }

    return (this->*factor_map[type])();
}
