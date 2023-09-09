// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "DeclarationClauseParser.h"
#include "qps/argument/input/ExpressionInput.h"
#include "qps/argument/input/StringInput.h"
#include "common/ASTUtil.h"
#include "qps/clause/strategy/pattern/AssignStrategy.h"
#include "common/tokenizer/PunctuationToken.h"
#include "qps/argument/validator/PatternFirstArg.h"
#include "qps/preprocessor/parser/utils/ArgumentResult.h"
#include "qps/preprocessor/parser/argument/PatternFirstArgParser.h"
#include "qps/preprocessor/parser/argument/AssignPatternSecondArgParser.h"
#include "qps/preprocessor/parser/utils/PatternSyntaxChecker.h"

class AssignPatternParser : public DeclarationClauseParser, public PatternSyntaxChecker  {
private:
    std::shared_ptr<Argument> synonym;
    void addPatternClause(std::shared_ptr<Argument> firstArg, std::shared_ptr<Argument> secondArg,
        AbstractQuery& parsedQuery);

public:
    explicit AssignPatternParser(std::shared_ptr<Argument> synonym);
    ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
