// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <vector>
#include <unordered_set>
#include <string>
#include "SPExpressionParser.h"
#include "sp/node/ExpressionNode.h"
#include "sp/node/OperatorNode.h"


class CondExprParser : public SPExpressionParser {
private:
    std::shared_ptr<SPExpressionParser> relExprParser;
    const std::unordered_set<std::string> PUNCT_SET = std::unordered_set<std::string>({"&&", "||"});

public:
    explicit CondExprParser(std::vector<Token> tokens);

    void addRelExprParser(std::shared_ptr<SPExpressionParser> parser);
    std::shared_ptr<OperatorNode> processOperatorNode();
    std::shared_ptr<ExpressionNode> consumeRelExpr();
    std::shared_ptr<ExpressionNode> processCondExpr();
    std::shared_ptr<ExpressionNode> parse() override;
};
