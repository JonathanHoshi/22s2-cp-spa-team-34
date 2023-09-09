// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

#include "common/tokenizer/Token.h"
#include "qps/query/AbstractQuery.h"
#include "qps/argument/Argument.h"
#include "qps/preprocessor/parser/utils/ParserResult.h"
#include "common/exceptions/ParserError.h"



class DeclarationClauseParser {
public:
    DeclarationClauseParser();
    static int consumeOpenBracket(Token token);
    static int consumeCloseBracket(Token token);
    static int consumeComma(Token token);
    static int consumeEquals(Token token);
    static int consumeAnd(Token token);
    static bool isBoolean(Token token);
    static bool isTransitive(Token token);
    static bool isQuotation(Token token);
    static bool isAnd(Token token);
    static void updateIfSemantic(ErrorStatus errorStatus, AbstractQuery& parsedQuery);
    virtual ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) = 0;
};
