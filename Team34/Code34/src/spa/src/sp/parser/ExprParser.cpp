// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <utility>
#include "ExprParser.h"

ExprParser::ExprParser(std::vector<Token> tokens)
    : SPExpressionParser(tokens) {}

void ExprParser::addTermParser(std::shared_ptr<SPExpressionParser> parser) {
    termParser = parser;
}

std::shared_ptr<ExpressionNode> ExprParser::consumeTerm() {
    std::shared_ptr<ExpressionNode> termNode;

    termParser->setPos(getPos());
    termParser->setStmtNo(getStmtNo());
    termNode = termParser->parse();
    setPos(termParser->getPos());

    return termNode;
}

std::shared_ptr<OperatorNode> ExprParser::parseSubExpr() {
    std::shared_ptr<OperatorNode> operatorNode;
    std::shared_ptr<OperatorNode> parentNode;
    std::shared_ptr<ExpressionNode> termNode;

    std::string punct = currToken.getValue();

    if (PUNCT_SET.find(punct) == PUNCT_SET.end()) {
        return nullptr;
    }

    verifyTokenAndTraverse("PUNCTUATION");
    operatorNode = std::make_shared<OperatorNode>(punct);

    // solve first term first
    termNode = consumeTerm();
    parentNode = parseSubExpr();
    operatorNode->addRHS(move(termNode));

    if (parentNode == nullptr) {
        root = operatorNode;
    } else {
        parentNode->addLHS(operatorNode);
    }

    return operatorNode;
}

// Parse from left to right manner (bottom up approach for the AST)
std::shared_ptr<ExpressionNode> ExprParser::parse() {
    std::shared_ptr<OperatorNode> parentNode;
    std::shared_ptr<ExpressionNode> termNode;

    // solve first term first
    termNode = consumeTerm();

    // get the RHS and attach termNode to parent
    parentNode = parseSubExpr();

    if (parentNode == nullptr) {
        return termNode;
    } else {
        parentNode->addLHS(move(termNode));
        return root;
    }
}
