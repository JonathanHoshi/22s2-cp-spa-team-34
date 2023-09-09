// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "WithArgParser.h"

WithArgParser::WithArgParser() : ArgumentParser() {}

ArgumentResult WithArgParser::parse(std::vector<Token> tokens,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    std::shared_ptr<Argument> arg;
    ErrorStatus errorStatus = ErrorStatus::OK;
    if (isQuotation(tokens[pos])) {
        pos++;
        checkName(tokens[pos]);
        arg = std::make_shared<StringInput>(tokens[pos].getValue());
        pos++;
        pos += consumeQuote(tokens[pos]);
    } else if (tokens[pos].getType() == NumberToken::TYPE_NAME) {
        arg = std::make_shared<IntInput>(tokens[pos].getValue());
        pos++;
    } else if (tokens[pos].getType() == IdentityToken::TYPE_NAME) {
        ElementParser ep = ElementParser(true);
        ep.mustBeAttrRef();
        ArgumentResult ar = ep.parse(tokens, declarations, pos);
        arg = ar.getArg();
        pos = ar.getPos();
        errorStatus = ar.getErrorStatus();
    } else {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return {arg, pos, errorStatus};
}
