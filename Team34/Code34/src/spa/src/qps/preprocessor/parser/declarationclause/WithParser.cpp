// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "WithParser.h"

WithParser::WithParser() : DeclarationClauseParser() {}

ParserResult WithParser::parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    int clauses = 0;
    pos++;  // consume with
    WithArgParser withArgParser;
    while (pos < tokens.size() && (clauses == 0 || isAnd(tokens[pos]))) {
        pos = clauses == 0 ? pos : pos + consumeAnd(tokens[pos]);
        if (pos >= tokens.size()) {
            throw ParserError(ErrorStatus::SYNTAX);
        }
        ArgumentResult firstArgResult = withArgParser.parse(tokens, declarations, pos);
        std::shared_ptr<Argument> firstArg = firstArgResult.getArg();
        pos = firstArgResult.getPos();
        updateIfSemantic(firstArgResult.getErrorStatus(), parsedQuery);

        if (pos > tokens.size()) {
            throw ParserError(ErrorStatus::SYNTAX);
        }

        pos += consumeEquals(tokens[pos]);

        ArgumentResult secondArgResult = withArgParser.parse(tokens, declarations, pos);
        std::shared_ptr<Argument> secondArg = secondArgResult.getArg();
        pos = secondArgResult.getPos();
        updateIfSemantic(secondArgResult.getErrorStatus(), parsedQuery);
        updateIfSemantic(WithArgsValidator::validate(firstArg, secondArg), parsedQuery);
        parsedQuery.addClause(WithClauseCreator().create(firstArg, secondArg));
        clauses++;
    }
    if (clauses == 0) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return {declarations, pos};
}
