// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <vector>
#include <memory>
#include <unordered_set>
#include <string>
#include "SPExpressionParser.h"
#include "sp/node/ExpressionNode.h"
#include "sp/node/OperatorNode.h"

class TermParser : public SPExpressionParser {
private:
    std::shared_ptr<ExpressionNode> root;
    std::shared_ptr<SPExpressionParser> factorParser;
    const std::unordered_set<std::string> PUNCT_SET =
        std::unordered_set<std::string>({"*", "/", "%"});

public:
    explicit TermParser(std::vector<Token> tokens);

    void addFactorParser(std::shared_ptr<SPExpressionParser> parser);
    std::shared_ptr<ExpressionNode> consumeFactor();
    std::shared_ptr<OperatorNode> parseSubTerm();
    std::shared_ptr<ExpressionNode> parse() override;
};
