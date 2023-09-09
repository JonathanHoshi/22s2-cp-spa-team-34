// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "sp/node/ExpressionNode.h"
#include "common/tokenizer/Tokenizer.h"

class ASTUtil {
public:
    static bool checkFullEqual(const ExpressionNode& referenceTree,
        const ExpressionNode& queryTree);
    static bool checkPartialEqual(const ExpressionNode& referenceTree,
        const ExpressionNode& queryTree);
    static std::shared_ptr<ExpressionNode> convertToAST(std::string patternExpr);
    static std::shared_ptr<ExpressionNode> convertToAST(std::vector<Token> tokens);
};
