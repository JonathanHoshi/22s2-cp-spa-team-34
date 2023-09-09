// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

#include "qps/preprocessor/parser/utils/ArgumentResult.h"
#include "qps/argument/entity/EntityArgument.h"
#include "common/tokenizer/Token.h"
#include "common/exceptions/ParserError.h"
#include "common/tokenizer/IdentityToken.h"

class ArgumentParser {
protected:
    ErrorStatus errorStatus;
public:
    ArgumentParser();
    static bool isQuotation(Token token);
    static bool isWildcard(Token token);
    static int consumeWildcard(Token token);
    static int consumeQuote(Token token);
    static int consumeDot(Token token);
    static void checkName(Token token);
    virtual ArgumentResult parse(std::vector<Token> tokens,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) = 0;
};
