// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ModifiesUsesParser.h"

ModifiesUsesParser::ModifiesUsesParser() : DeclarationClauseParser() {
    clauseCreators = std::unordered_map<std::string, std::shared_ptr<ClauseCreator>>({
        {"Modifies", std::make_shared<ModifiesClauseCreator>()},
        {"Uses", std::make_shared<UsesClauseCreator>()}
        });
}

ParserResult ModifiesUsesParser::parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    std::string type = tokens[pos].getValue();
    pos++;  // consume "Modifies" / "Uses"

    pos += consumeOpenBracket(tokens[pos]);

    // start first argument parse
    ArgumentResult firstArgResult = ModifiesUsesFirstArgParser().parse(tokens, declarations, pos);
    pos = firstArgResult.getPos();
    updateIfSemantic(firstArgResult.getErrorStatus(), parsedQuery);

    pos += consumeComma(tokens[pos]);

    // start second argument parse
    ArgumentResult secondArgResult = ModifiesUsesSecondArgParser().parse(tokens, declarations, pos);
    pos = secondArgResult.getPos();
    updateIfSemantic(secondArgResult.getErrorStatus(), parsedQuery);

    pos += consumeCloseBracket(tokens[pos]);

    // create clause
    // will always be found so no need check if is clauseCreator.end()
    auto creatorIter = clauseCreators.find(type);
    parsedQuery.addClause(creatorIter->second.get()->create(firstArgResult.getArg(),
        secondArgResult.getArg()));

    return {declarations, pos};
}
