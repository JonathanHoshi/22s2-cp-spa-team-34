// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "DeclarationClauseParser.h"
#include "qps/argument/input/InputArgument.h"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/stmt/StmtEntity.h"
#include "qps/argument/input/StringInput.h"
#include "qps/argument/input/IntInput.h"
#include "qps/clause/strategy/relation/ModifiesStrategy.h"
#include "qps/clause/Clause.h"
#include "qps/preprocessor/factory/clause/ClauseCreator.h"
#include "qps/preprocessor/factory/clause/ModifiesClauseCreator.h"
#include "qps/preprocessor/factory/clause/UsesClauseCreator.h"
#include "qps/argument/validator/ModifiesUsesSecondArg.h"
#include "qps/preprocessor/parser/utils/ArgumentResult.h"
#include "qps/preprocessor/parser/argument/ModifiesUsesFirstArgParser.h"
#include "qps/preprocessor/parser/argument/ModifiesUsesSecondArgParser.h"

class ModifiesUsesParser : public DeclarationClauseParser {
private:
    std::unordered_map<std::string, std::shared_ptr<ClauseCreator>> clauseCreators;
public:
    ModifiesUsesParser();
    ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
