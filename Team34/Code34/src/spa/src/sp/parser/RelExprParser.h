// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#pragma once
#include <vector>
#include <memory>
#include <unordered_set>
#include <string>
#include "SPExpressionParser.h"
#include "sp/node/ExpressionNode.h"
#include "sp/node/OperatorNode.h"


class RelExprParser : public SPExpressionParser {
private:
    std::shared_ptr<SPExpressionParser> exprParser;
    std::unordered_set<std::string> PUNCT_SET =
        std::unordered_set<std::string>({">", ">=", "<", "<=", "==", "!="});

public:
    explicit RelExprParser(std::vector<Token> tokens);

    void addExprParser(std::shared_ptr<SPExpressionParser> parser);
    std::shared_ptr<ExpressionNode> consumeExpr();
    std::shared_ptr<ExpressionNode> parse() override;
};
