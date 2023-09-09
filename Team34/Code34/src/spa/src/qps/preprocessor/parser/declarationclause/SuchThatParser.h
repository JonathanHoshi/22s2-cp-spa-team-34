// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "DeclarationClauseParser.h"
#include "ModifiesUsesParser.h"
#include "ParentFollowsNextAffectsParser.h"
#include "CallsParser.h"

class SuchThatParser : public DeclarationClauseParser {
private:
    std::unordered_map<std::string, std::shared_ptr<DeclarationClauseParser>> clauseParsers;
public:
    SuchThatParser();
    ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos);
};
