// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include "sp/node/RootNode.h"
#include "sp/node/ExpressionNode.h"
#include "common/tokenizer/Token.h"

class SPParserManager {
public:
    SPParserManager();
    std::shared_ptr<RootNode> parse(std::vector<Token> tokens);
    std::shared_ptr<ExpressionNode> parseExpr(std::vector<Token> tokens);
};
