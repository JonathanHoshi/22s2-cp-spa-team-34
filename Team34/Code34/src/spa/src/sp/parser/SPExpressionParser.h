// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <vector>
#include <memory>
#include "SPParser.h"
#include "sp/node/ExpressionNode.h"

class SPExpressionParser : public SPParser {
public:
    explicit SPExpressionParser(std::vector<Token> tokens);

    virtual std::shared_ptr<ExpressionNode> parse() = 0;
};
