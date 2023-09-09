// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>

#include "DeclarationClauseParser.h"
#include "common/tokenizer/Token.h"
#include "qps/preprocessor/validator/NameValidator.h"
#include "qps/query/AbstractQuery.h"
#include "qps/preprocessor/factory/entity/EntityCreator.h"
#include "qps/preprocessor/factory/utils/CreatorMap.h"

class EntityParser : public DeclarationClauseParser {
public:
    EntityParser();
    ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
