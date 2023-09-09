// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ArgumentParser.h"

ArgumentParser::ArgumentParser() {
    errorStatus = ErrorStatus::OK;
}

bool ArgumentParser::isQuotation(Token token) {
    return token.getValue() == "\"";
}

bool ArgumentParser::isWildcard(Token token) {
    return token.getValue() == "_";
}

void ArgumentParser::checkName(Token token) {
    if (token.getType() != IdentityToken::TYPE_NAME) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
}

int ArgumentParser::consumeWildcard(Token token) {
    if (isWildcard(token)) {
        return 1;
    }
    throw ParserError(ErrorStatus::SYNTAX);
}

int ArgumentParser::consumeDot(Token token) {
    if (token.getValue() == ".") {
        return 1;
    }
    throw ParserError(ErrorStatus::SYNTAX);
}

int ArgumentParser::consumeQuote(Token token) {
    if (token.getValue() == "\"") {
        return 1;
    }
    throw ParserError(ErrorStatus::SYNTAX);
}
