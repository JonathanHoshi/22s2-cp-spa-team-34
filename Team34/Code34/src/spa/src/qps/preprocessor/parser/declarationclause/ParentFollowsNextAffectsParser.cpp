// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ParentFollowsNextAffectsParser.h"

ParentFollowsNextAffectsParser::ParentFollowsNextAffectsParser() : DeclarationClauseParser() {
    clauseCreators = std::unordered_map<std::string, std::shared_ptr<TransitiveClauseCreator>>{
        {"Parent", std::make_shared<ParentClauseCreator>(false)},
        {"Follows", std::make_shared<FollowsClauseCreator>(false)},
        {"Next", std::make_shared<NextClauseCreator>(false)},
        {"Affects", std::make_shared<AffectsClauseCreator>(false)}
    };
}

ParserResult ParentFollowsNextAffectsParser::parse(std::vector<Token> tokens,
    AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    std::string type = tokens[pos].getValue();
    pos++;  // consume type

    bool isTransitive = DeclarationClauseParser::isTransitive(tokens[pos]);
    pos = isTransitive ? pos + 1 : pos;

    pos += consumeOpenBracket(tokens[pos]);

    // start first argument parse
    ArgumentResult firstArgResult = ParentFollowsNextAffectsArgParser()
            .parse(tokens, declarations, pos);
    pos = firstArgResult.getPos();  // consume stmt entity name/number token
    updateIfSemantic(firstArgResult.getErrorStatus(), parsedQuery);

    pos += consumeComma(tokens[pos]);

    // start second argument parse
    ArgumentResult secondArgResult = ParentFollowsNextAffectsArgParser()
            .parse(tokens, declarations, pos);
    pos = secondArgResult.getPos();  // consume stmt entity name/number token
    updateIfSemantic(secondArgResult.getErrorStatus(), parsedQuery);

    pos += consumeCloseBracket(tokens[pos]);

    // create clause
    // will always be found so no need check if is clauseCreator.end()
    auto creatorIter = clauseCreators.find(type);
    creatorIter->second.get()->setIsTransitive(isTransitive);
    parsedQuery.addClause(creatorIter->second.get()->create(firstArgResult.getArg(),
        secondArgResult.getArg()));

    return {declarations, pos};
}
