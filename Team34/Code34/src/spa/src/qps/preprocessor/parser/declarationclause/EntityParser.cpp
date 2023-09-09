// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "EntityParser.h"

EntityParser::EntityParser() : DeclarationClauseParser() {}

ParserResult EntityParser::parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
    int pos) {
    std::string type = tokens[pos].getValue();
    pos++;
    if (tokens.size() - pos <= 1) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    while (pos < tokens.size()) {
        std::string name = tokens[pos].getValue();
        pos++;
        if (declarations.find(name) != declarations.end()) {
            parsedQuery.updateStatus(ErrorStatus::SEMANTIC);
        }
        if (NameValidator::validate(name)) {
            std::shared_ptr<EntityCreator> entityCreator =
                CreatorMap::entityCreators.find(type)->second;
            Token commaOrSemi = tokens[pos];
            std::shared_ptr<EntityArgument> newEntity = entityCreator->create(name);
            if (commaOrSemi.getValue() == ";") {
                pos++;
                declarations.insert({name, newEntity});
                return ParserResult(declarations, pos);
            }
            pos += consumeComma(commaOrSemi);
            declarations.insert({name, newEntity});
        }
    }
    throw ParserError(ErrorStatus::SYNTAX);
}
