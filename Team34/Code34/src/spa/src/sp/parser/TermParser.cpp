// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <utility>
#include "TermParser.h"

TermParser::TermParser(std::vector<Token> tokens)
    :SPExpressionParser(tokens) {}

void TermParser::addFactorParser(std::shared_ptr<SPExpressionParser> parser) {
    factorParser = parser;
}

std::shared_ptr<ExpressionNode> TermParser::consumeFactor() {
    std::shared_ptr<ExpressionNode> factorNode;

    factorParser->setPos(getPos());
    factorParser->setStmtNo(getStmtNo());
    factorNode = factorParser->parse();
    setPos(factorParser->getPos());

    return factorNode;
}

std::shared_ptr<OperatorNode> TermParser::parseSubTerm() {
    std::shared_ptr<OperatorNode> operatorNode;
    std::shared_ptr<OperatorNode> parentNode;
    std::shared_ptr<ExpressionNode> factorNode;

    std::string punct = currToken.getValue();

    if (PUNCT_SET.find(punct) == PUNCT_SET.end()) {
        return nullptr;
    }

    verifyTokenAndTraverse("PUNCTUATION");
    operatorNode = std::make_shared<OperatorNode>(punct);

    // solve first term first
    factorNode = consumeFactor();
    parentNode = parseSubTerm();
    operatorNode->addRHS(move(factorNode));

    if (parentNode == nullptr) {
        root = operatorNode;
    } else {
        parentNode->addLHS(operatorNode);
    }

    return operatorNode;
}

std::shared_ptr<ExpressionNode> TermParser::parse() {
    std::shared_ptr<OperatorNode> parentNode;
    std::shared_ptr<ExpressionNode> factorNode;

    // solve LHS first
    factorNode = consumeFactor();

    // get the parent node
    parentNode = parseSubTerm();

    if (parentNode == nullptr) {
        return factorNode;
    } else {
        // assign term to the LHS of expr
        parentNode->addLHS(move(factorNode));
        return root;
    }
}
