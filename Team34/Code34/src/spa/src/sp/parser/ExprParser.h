// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include "SPExpressionParser.h"
#include "sp/node/OperatorNode.h"
#include "sp/node/ExpressionNode.h"

class ExprParser : public SPExpressionParser {
private:
    std::shared_ptr<ExpressionNode> root;
    std::shared_ptr<OperatorNode> parent;
    std::shared_ptr<SPExpressionParser> termParser;
    const std::unordered_set<std::string> PUNCT_SET = std::unordered_set<std::string>({"+", "-"});

public:
    explicit ExprParser(std::vector<Token> tokens);

    void addTermParser(std::shared_ptr<SPExpressionParser> termParser);
    std::shared_ptr<ExpressionNode> consumeTerm();
    std::shared_ptr<OperatorNode> parseSubExpr();
    std::shared_ptr<ExpressionNode> parse() override;
};
