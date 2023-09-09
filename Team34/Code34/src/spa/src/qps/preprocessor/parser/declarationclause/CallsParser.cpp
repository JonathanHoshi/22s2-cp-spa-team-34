// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "CallsParser.h"

CallsParser::CallsParser() : DeclarationClauseParser() {}

ParserResult CallsParser::parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    pos++;  // consume calls token

    bool isTrans = isTransitive(tokens[pos]);
    pos = isTrans ? pos + 1 : pos;

    pos += consumeOpenBracket(tokens[pos]);

    // get first arg
    CallsArgParser argParser;
    ArgumentResult firstArgResult = argParser.parse(tokens, declarations, pos);
    std::shared_ptr<Argument> firstArg = firstArgResult.getArg();
    pos = firstArgResult.getPos();
    updateIfSemantic(firstArgResult.getErrorStatus(), parsedQuery);

    pos += consumeComma(tokens[pos]);

    // get second arg
    ArgumentResult secondArgResult = argParser.parse(tokens, declarations, pos);
    std::shared_ptr<Argument> secondArg = secondArgResult.getArg();
    pos = secondArgResult.getPos();
    updateIfSemantic(secondArgResult.getErrorStatus(), parsedQuery);

    pos += consumeCloseBracket(tokens[pos]);

    parsedQuery.addClause(CallsClauseCreator(isTrans).create(firstArg, secondArg));

    return {declarations, pos};
}
