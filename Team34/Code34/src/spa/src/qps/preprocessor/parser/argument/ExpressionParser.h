// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "ArgumentParser.h"
#include "common/exceptions/ParserError.h"
#include "common/exceptions/ErrorStatus.h"
#include "qps/argument/input/ExpressionInput.h"
#include "common/tokenizer/PunctuationToken.h"
#include "common/ASTUtil.h"

class ExpressionParser : public ArgumentParser {
private:
    bool isPartial;
    std::string getExpressionString(std::vector<Token> tokens);
public:
    explicit ExpressionParser(bool isPartial);
    ArgumentResult parse(std::vector<Token> tokens,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
