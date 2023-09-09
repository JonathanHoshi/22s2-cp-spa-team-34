// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <utility>
#include "IfParser.h"
#include "sp/node/IfNode.h"

IfParser::IfParser(std::vector<Token> tokens)
    : SPStmtParser(tokens) {}

void IfParser::addCondExprParser(std::shared_ptr<SPExpressionParser> parser) {
    condExprParser = parser;
}

void IfParser::addStmtLstParser(std::shared_ptr<StmtLstParser> parser) {
    stmtLstParser = parser;
}

std::shared_ptr<StmtLstNode> IfParser::consumeStmtLst() {
    std::shared_ptr<StmtLstNode> stmtLstNode;

    stmtLstParser->setPos(getPos());
    stmtLstNode = stmtLstParser->parse();
    setPos(stmtLstParser->getPos());

    return stmtLstNode;
}

std::shared_ptr<ExpressionNode> IfParser::consumeCondExpr() {
    std::shared_ptr<ExpressionNode> condExprNode;

    condExprParser->setPos(getPos());
    condExprParser->setStmtNo(getStmtNo());
    condExprNode = condExprParser->parse();
    setPos(condExprParser->getPos());

    return condExprNode;
}

std::shared_ptr<StmtNode> IfParser::parse() {
    std::shared_ptr<ExpressionNode> condExprNode;
    std::shared_ptr<IfNode> ifNode;
    std::shared_ptr<StmtLstNode> thenNode;
    std::shared_ptr<StmtLstNode> elseNode;

    if (!checkToken("IDENTITY", "if")) {
        throw ParserError(ErrorStatus::SYNTAX);
    }

    // if (cond_expr) then { stmtLst } else { stmtLst }
    ifNode = std::make_shared<IfNode>(getStmtNo());
    verifyTokenAndTraverse("IDENTITY", "if");
    verifyTokenAndTraverse("PUNCTUATION", "(");
    condExprNode = consumeCondExpr();
    verifyTokenAndTraverse("PUNCTUATION", ")");
    verifyTokenAndTraverse("IDENTITY", "then");
    verifyTokenAndTraverse("PUNCTUATION", "{");
    thenNode = consumeStmtLst();
    verifyTokenAndTraverse("PUNCTUATION", "}");
    verifyTokenAndTraverse("IDENTITY", "else");
    verifyTokenAndTraverse("PUNCTUATION", "{");
    elseNode = consumeStmtLst();
    verifyTokenAndTraverse("PUNCTUATION", "}");
    ifNode->setCondition(move(condExprNode));
    ifNode->setThen(move(thenNode));
    ifNode->setElse(move(elseNode));

    return ifNode;
}
