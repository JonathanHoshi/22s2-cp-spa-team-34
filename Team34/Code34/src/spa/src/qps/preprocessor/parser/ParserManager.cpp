// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ParserManager.h"

ParserManager::ParserManager() {
    auto entityParser = std::make_shared<EntityParser>();
    parsers = std::unordered_map<std::string, std::shared_ptr<DeclarationClauseParser>>(
        {{"variable", entityParser},
        {"procedure", entityParser},
        {"stmt", entityParser},
        {"constant", entityParser},
        {"if", entityParser},
        {"while", entityParser},
        {"read", entityParser},
        {"assign", entityParser},
        {"print", entityParser},
        {"call", entityParser},
        {"Select", std::make_shared<SelectParser>()},
        {"such", std::make_shared<SuchThatParser>()},
        {"pattern", std::make_shared<PatternParser>()},
        {"with", std::make_shared<WithParser>()}});
}

void ParserManager::parse(std::vector<Token>& tokens, AbstractQuery& parsedQuery) {
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations =
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>>();
    int pos = 0;
    while (pos < tokens.size()) {
        std::string val = tokens[pos].getValue();
        auto parserIter = parsers.find(val);
        if (parserIter != parsers.end()) {
            std::shared_ptr<DeclarationClauseParser> currParser = parserIter->second;
            ParserResult pr = currParser->parse(tokens, parsedQuery, declarations, pos);
            pos = pr.getPos();
            declarations = pr.getDeclarations();
        } else {
            throw ParserError(ErrorStatus::SYNTAX);
        }
    }
    if (parsedQuery.isSelectionEmpty() && !parsedQuery.getSelectBoolean()) {
        throw ParserError(ErrorStatus::SYNTAX);
    } else {
    }
}
