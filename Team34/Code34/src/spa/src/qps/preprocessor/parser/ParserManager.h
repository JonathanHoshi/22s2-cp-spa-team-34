// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "qps/preprocessor/parser/declarationclause/DeclarationClauseParser.h"
#include "qps/preprocessor/parser/declarationclause/EntityParser.h"
#include "qps/preprocessor/parser/declarationclause/SelectParser.h"
#include "qps/preprocessor/parser/declarationclause/PatternParser.h"
#include "qps/preprocessor/parser/declarationclause/WithParser.h"
#include "common/tokenizer/Token.h"
#include "qps/preprocessor/parser/declarationclause/SuchThatParser.h"
#include "qps/query/AbstractQuery.h"


class ParserManager {
private:
    std::unordered_map<std::string, std::shared_ptr<DeclarationClauseParser>> parsers;
public:
    ParserManager();
    void parse(std::vector<Token>& tokens, AbstractQuery& parsedQuery);
};
