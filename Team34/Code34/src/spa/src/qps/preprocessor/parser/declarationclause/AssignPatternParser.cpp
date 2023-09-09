// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "AssignPatternParser.h"

AssignPatternParser::AssignPatternParser(std::shared_ptr<Argument> synonym) :
    DeclarationClauseParser(), PatternSyntaxChecker(false) {
    this->synonym = synonym;
}

void AssignPatternParser::addPatternClause(std::shared_ptr<Argument> firstArg,
    std::shared_ptr<Argument> secondArg,
    AbstractQuery& parsedQuery) {
    if (ExpressionInput::checkInstance(secondArg.get())) {
        ExpressionInput expressionInput = *dynamic_cast<const ExpressionInput*>(secondArg.get());
        parsedQuery.addClause(std::make_shared<Clause>(
            std::make_shared<AssignStrategy>(expressionInput.getIsPartial()), synonym,
            firstArg, secondArg));
    } else {
        parsedQuery.addClause(std::make_shared<Clause>(std::make_shared<AssignStrategy>(false),
            synonym, firstArg, secondArg));
    }
}

ParserResult AssignPatternParser::parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
    int pos) {
    pos += consumeOpenBracket(tokens[pos]);

    ArgumentResult firstArgResult = PatternFirstArgParser().parse(tokens, declarations, pos);
    pos = firstArgResult.getPos();
    updateIfSemantic(firstArgResult.getErrorStatus(), parsedQuery);

    pos += consumeComma(tokens[pos]);

    ArgumentResult secondArgResult =
        AssignPatternSecondArgParser().parse(tokens, declarations, pos);
    pos = secondArgResult.getPos();
    updateIfSemantic(secondArgResult.getErrorStatus(), parsedQuery);

    pos += consumeCloseBracket(tokens[pos]);

    if (!isSyntaxCheck) {
        addPatternClause(firstArgResult.getArg(), secondArgResult.getArg(), parsedQuery);
    }

    return {declarations, pos};
}
