// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "DeclarationClauseParser.h"
#include "qps/argument/input/IntInput.h"
#include "qps/argument/entity/stmt/StmtEntity.h"
#include "qps/argument/validator/ParentFollowsNextArg.h"
#include "qps/preprocessor/factory/clause/TransitiveClauseCreator.h"
#include "qps/preprocessor/factory/clause/ParentClauseCreator.h"
#include "qps/preprocessor/factory/clause/FollowsClauseCreator.h"
#include "qps/preprocessor/parser/utils/ArgumentResult.h"
#include "qps/preprocessor/parser/argument/ParentFollowsNextAffectsArgParser.h"
#include "qps/preprocessor/factory/clause/NextClauseCreator.h"
#include "qps/preprocessor/factory/clause/AffectsClauseCreator.h"

class ParentFollowsNextAffectsParser : public DeclarationClauseParser {
private:
    std::unordered_map<std::string, std::shared_ptr<TransitiveClauseCreator>> clauseCreators;
public:
    ParentFollowsNextAffectsParser();
    ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
