// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "DeclarationClauseParser.h"
#include "qps/preprocessor/parser/argument/CallsArgParser.h"
#include "qps/preprocessor/factory/clause/CallsClauseCreator.h"

class CallsParser : public DeclarationClauseParser {
public:
    CallsParser();
    ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
