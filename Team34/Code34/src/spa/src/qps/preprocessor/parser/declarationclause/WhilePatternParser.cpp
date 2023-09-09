// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "WhilePatternParser.h"

WhilePatternParser::WhilePatternParser(std::shared_ptr<Argument> synonym) :
    DeclarationClauseParser(), PatternSyntaxChecker(false) {
    this->synonym = synonym;
}

ParserResult WhilePatternParser::parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    pos += consumeOpenBracket(tokens[pos]);

    ArgumentResult firstArgResult = PatternFirstArgParser().parse(tokens, declarations, pos);
    pos = firstArgResult.getPos();
    updateIfSemantic(firstArgResult.getErrorStatus(), parsedQuery);

    pos += consumeComma(tokens[pos]);
    pos += ArgumentParser::consumeWildcard(tokens[pos]);
    pos += consumeCloseBracket(tokens[pos]);

    if (!isSyntaxCheck) {
        parsedQuery.addClause(std::make_shared<Clause>(std::make_shared<WhileStrategy>(),
           synonym, firstArgResult.getArg()));
    }
    return {declarations, pos};
}
