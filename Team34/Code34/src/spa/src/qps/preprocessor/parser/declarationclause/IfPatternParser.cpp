// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "IfPatternParser.h"

IfPatternParser::IfPatternParser(std::shared_ptr<Argument> synonym) :
    DeclarationClauseParser(), PatternSyntaxChecker(false) {
    this->synonym = synonym;
}

ParserResult IfPatternParser::parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    pos += consumeOpenBracket(tokens[pos]);

    ArgumentResult firstArgResult = PatternFirstArgParser().parse(tokens, declarations, pos);
    pos = firstArgResult.getPos();
    updateIfSemantic(firstArgResult.getErrorStatus(), parsedQuery);

    for (int i = 0; i < 2; i++) {
        pos += consumeComma(tokens[pos]);
        pos += ArgumentParser::consumeWildcard(tokens[pos]);
    }

    pos += consumeCloseBracket(tokens[pos]);
    if (!isSyntaxCheck) {
        parsedQuery.addClause(std::make_shared<Clause>(std::make_shared<IfStrategy>(),
               synonym, firstArgResult.getArg()));
    }
    return {declarations, pos};
}
