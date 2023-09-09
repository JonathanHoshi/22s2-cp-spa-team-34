// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "qps/argument/entity/stmt/AssignStmtEntity.h"
#include "DeclarationClauseParser.h"
#include "AssignPatternParser.h"
#include "qps/preprocessor/parser/argument/PatternTypeParser.h"
#include "qps/argument/entity/stmt/IfStmtEntity.h"
#include "qps/argument/entity/stmt/WhileStmtEntity.h"
#include "qps/preprocessor/parser/declarationclause/IfPatternParser.h"
#include "qps/preprocessor/parser/declarationclause/WhilePatternParser.h"

class PatternParser : public DeclarationClauseParser {
private:
    std::shared_ptr<DeclarationClauseParser> getParser(std::string synonymType,
        std::shared_ptr<Argument> arg);
    ParserResult checkForSyntaxError(std::vector<Token> tokens, AbstractQuery& parsedQuery,
         std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
         int pos);
    ParserResult parseValidSynonym(std::string synonymType,
        std::shared_ptr<Argument> arg, std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos);
public:
    PatternParser();
    ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
