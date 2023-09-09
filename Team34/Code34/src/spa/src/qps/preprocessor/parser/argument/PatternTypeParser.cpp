// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "PatternTypeParser.h"

PatternTypeParser::PatternTypeParser() : ArgumentParser() {}

ArgumentResult PatternTypeParser::parse(std::vector<Token> tokens,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
    int pos) {
    Token patternToken = tokens[pos];
    std::shared_ptr<Argument> patternTypeSyn;

    if (patternToken.getType() != IdentityToken::TYPE_NAME) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    ElementParser elementParser = ElementParser(false);
    ArgumentResult argumentResult = elementParser.parse(tokens, declarations, pos);
    patternTypeSyn = argumentResult.getArg();
    pos = argumentResult.getPos();
    errorStatus = argumentResult.getErrorStatus();

    if (!PatternSynonym::checkInstance(patternTypeSyn.get())) {
        errorStatus = ErrorStatus::SEMANTIC;
        patternTypeSyn = std::make_shared<DummyArgument>();
    }

    return {patternTypeSyn, pos, errorStatus};
}
