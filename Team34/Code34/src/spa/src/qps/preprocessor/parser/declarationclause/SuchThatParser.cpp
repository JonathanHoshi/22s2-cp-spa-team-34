// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "SuchThatParser.h"

SuchThatParser::SuchThatParser() : DeclarationClauseParser() {
    std::shared_ptr<ModifiesUsesParser> modifiesUsesParser = std::make_shared<ModifiesUsesParser>();
    std::shared_ptr<ParentFollowsNextAffectsParser> parentFollowsNextAffectsParser =
        std::make_shared<ParentFollowsNextAffectsParser>();
    clauseParsers = std::unordered_map<std::string, std::shared_ptr<DeclarationClauseParser>>{
        {"Modifies", modifiesUsesParser},
        {"Uses", modifiesUsesParser},
        {"Follows", parentFollowsNextAffectsParser},
        {"Parent", parentFollowsNextAffectsParser},
        {"Next", parentFollowsNextAffectsParser},
        {"Calls", std::make_shared<CallsParser>()},
        {"Affects", parentFollowsNextAffectsParser}
    };
}


ParserResult SuchThatParser::parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    int clauses = 0;
    pos++;  // consume "such"
    std::string that = tokens[pos].getValue();
    if (that != "that") {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    pos++;  // consume "that"
    while (pos < tokens.size() && (clauses == 0 || isAnd(tokens[pos]))) {
        pos = clauses == 0 ? pos : pos + consumeAnd(tokens[pos]);
        if (pos >= tokens.size()) {
            throw ParserError(ErrorStatus::SYNTAX);
        }
        auto parserIter = clauseParsers.find(tokens[pos].getValue());
        if (parserIter == clauseParsers.end()) {
            throw ParserError(ErrorStatus::SYNTAX);
        }
        ParserResult pr = parserIter->second->parse(tokens, parsedQuery, declarations, pos);
        pos = pr.getPos();
        declarations = pr.getDeclarations();
        clauses++;
    }
    if (clauses == 0) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return {declarations, pos};
}
