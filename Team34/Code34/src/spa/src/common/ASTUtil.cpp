// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <string>
#include <memory>
#include <vector>
#include "ASTUtil.h"
#include "sp/parser/SPParserManager.h"

bool ASTUtil::checkFullEqual(const ExpressionNode& referenceTree,
    const ExpressionNode& queryTree) {
    return referenceTree == queryTree;
}

bool ASTUtil::checkPartialEqual(const ExpressionNode& referenceTree,
    const ExpressionNode& queryTree) {
    return referenceTree.checkPartial(queryTree);
}

std::shared_ptr<ExpressionNode> ASTUtil::convertToAST(std::string patternExpr) {
    SPParserManager exprParserManager;
    Tokenizer tokenizer;

    return exprParserManager.parseExpr(tokenizer.tokenize(patternExpr));
}

std::shared_ptr<ExpressionNode> ASTUtil::convertToAST(std::vector<Token> tokens) {
    SPParserManager exprParserManager;

    return exprParserManager.parseExpr(tokens);
}
