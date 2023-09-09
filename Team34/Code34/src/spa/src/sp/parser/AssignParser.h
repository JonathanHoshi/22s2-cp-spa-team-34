// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <vector>
#include "SPStmtParser.h"
#include "SPExpressionParser.h"

class AssignParser : public SPStmtParser {
private:
    std::shared_ptr<SPExpressionParser> exprParser;

public:
    explicit AssignParser(std::vector<Token> tokens);

    void addExprParser(std::shared_ptr<SPExpressionParser> parser);
    std::shared_ptr<ExpressionNode> consumeExpr();
    std::shared_ptr<StmtNode> parse() override;
};
