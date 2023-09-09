// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <utility>
#include "CondExprParser.h"

CondExprParser::CondExprParser(std::vector<Token> tokens)
    : SPExpressionParser(tokens) {}

void CondExprParser::addRelExprParser(std::shared_ptr<SPExpressionParser> parser) {
    relExprParser = parser;
}

std::shared_ptr<ExpressionNode> CondExprParser::consumeRelExpr() {
    std::shared_ptr<ExpressionNode> relExprNode;

    relExprParser->setPos(getPos());
    relExprParser->setStmtNo(getStmtNo());
    relExprNode = relExprParser->parse();
    setPos(relExprParser->getPos());

    return relExprNode;
}

std::shared_ptr<ExpressionNode> CondExprParser::processCondExpr() {
    std::shared_ptr<ExpressionNode> condExprNode;

    verifyTokenAndTraverse("PUNCTUATION", "(");
    condExprNode = parse();
    verifyTokenAndTraverse("PUNCTUATION", ")");

    return condExprNode;
}

std::shared_ptr<OperatorNode> CondExprParser::processOperatorNode() {
    std::string punct = verifyTokenAndGetValue("PUNCTUATION");

    if (PUNCT_SET.find(punct) == PUNCT_SET.end()) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    traverse();

    return std::make_shared<OperatorNode>(punct);
}

// 2 children parsers: CondExprParser & RelExprParser
std::shared_ptr<ExpressionNode> CondExprParser::parse() {
    std::shared_ptr<ExpressionNode> firstCondExprNode;
    std::shared_ptr<ExpressionNode> secondCondExprNode;
    std::shared_ptr<ExpressionNode> relExprNode;
    std::shared_ptr<OperatorNode> operatorNode;

    try {
        // try to verify if is rel_expr
        // handles the following edge case:
        // e.g while((x + 1) * 2 != y - 2)
        return consumeRelExpr();
    } catch (ParserError e) {
        // verifies that it is not a single rel_expr
    }

    if (checkToken("PUNCTUATION", "!")) {
        traverse();
        operatorNode = std::make_shared<OperatorNode>("!");
        operatorNode->addRHS(move(processCondExpr()));
    } else {
        firstCondExprNode = processCondExpr();
        operatorNode = processOperatorNode();
        secondCondExprNode = processCondExpr();
        operatorNode->addLHS(move(firstCondExprNode));
        operatorNode->addRHS(move(secondCondExprNode));
    }
    return operatorNode;
}
