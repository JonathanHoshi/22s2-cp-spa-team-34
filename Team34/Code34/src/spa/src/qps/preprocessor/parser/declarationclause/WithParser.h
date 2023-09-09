// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "DeclarationClauseParser.h"
#include "qps/preprocessor/parser/argument/WithArgParser.h"
#include "qps/preprocessor/factory/clause/WithClauseCreator.h"
#include "qps/preprocessor/validator/WithArgsValidator.h"

class WithParser : public DeclarationClauseParser {
public:
    WithParser();
    ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
