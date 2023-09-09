// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "SPExpressionParser.h"

class FactorParser : public SPExpressionParser {
private:
    std::shared_ptr<SPExpressionParser> exprParser;
    std::unordered_map<std::string,
        std::shared_ptr<ExpressionNode>(FactorParser::*)()> factor_map = {
            {"IDENTITY", &FactorParser::processVariable},
            {"NUMBER", &FactorParser::processConstant},
            {"PUNCTUATION", &FactorParser::processExpr}
    };
public:
    explicit FactorParser(std::vector<Token> tokens);

    void addExprParser(std::shared_ptr<SPExpressionParser> parser);
    std::shared_ptr<ExpressionNode> consumeExpr();
    std::shared_ptr<ExpressionNode> processVariable();
    std::shared_ptr<ExpressionNode> processConstant();
    std::shared_ptr<ExpressionNode> processExpr();
    std::shared_ptr<ExpressionNode> parse() override;
};
