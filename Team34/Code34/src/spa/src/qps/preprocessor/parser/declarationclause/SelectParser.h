// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "DeclarationClauseParser.h"
#include "qps/preprocessor/parser/utils/ArgumentResult.h"
#include "qps/preprocessor/parser/argument/ElementParser.h"

class SelectParser : public DeclarationClauseParser {
private:
    inline static const std::string tupleStart = "<";
    inline static const std::string tupleEnd = ">";
    bool isTupleStart(Token token);
    bool isTupleEnd(Token token);
    bool isBooleanDeclared(Token token, std::unordered_map<std::string,
        std::shared_ptr<EntityArgument>> declarations);
    void validateTuple(std::vector<std::shared_ptr<Argument>> tuple);
    void addAllElemToSelection(AbstractQuery& parsedQuery,
        std::vector<std::shared_ptr<Argument>> tuple);
    ParserResult parseTuple(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos);
    ParserResult parseBoolean(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos);
public:
    SelectParser();
    ParserResult parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
