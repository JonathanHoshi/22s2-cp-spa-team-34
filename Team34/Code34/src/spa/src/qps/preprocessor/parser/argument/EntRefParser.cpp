// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "EntRefParser.h"

EntRefParser::EntRefParser(): ArgumentParser() {}

ArgumentResult EntRefParser::parse(std::vector<Token> tokens,
                                   std::unordered_map<std::string,
                                   std::shared_ptr<EntityArgument>> declarations,
                                   int pos) {
    Token entToken = tokens.at(pos);
    std::shared_ptr<Argument> arg;
    pos++;
    if (isQuotation(entToken)) {
        Token nameToken = tokens[pos];
        checkName(nameToken);
        arg = std::make_shared<StringInput>(nameToken.getValue());
        pos++;
        pos += consumeQuote(tokens[pos]);
    } else if (isWildcard(entToken)) {
        arg = std::make_shared<WildcardEntity>();
    } else if (entToken.getType() == IdentityToken::TYPE_NAME) {
        ElementParser ep = ElementParser(false);
        ArgumentResult ar = ep.parse(tokens, declarations, pos - 1);
        arg = ar.getArg();
        pos = ar.getPos();
        errorStatus = ar.getErrorStatus();
    } else {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return {arg, pos, errorStatus};
}
