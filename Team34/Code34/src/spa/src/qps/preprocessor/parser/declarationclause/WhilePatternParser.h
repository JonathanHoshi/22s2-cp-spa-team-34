// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "DeclarationClauseParser.h"
#include "qps/preprocessor/parser/utils/ArgumentResult.h"
#include "qps/preprocessor/parser/argument/PatternFirstArgParser.h"
#include "qps/clause/strategy/pattern/WhileStrategy.h"
#include "qps/preprocessor/parser/utils/PatternSyntaxChecker.h"

class WhilePatternParser : public DeclarationClauseParser, public PatternSyntaxChecker {
private:
    std::shared_ptr<Argument> synonym;
public:
    explicit WhilePatternParser(std::shared_ptr<Argument> synonym);
    ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
