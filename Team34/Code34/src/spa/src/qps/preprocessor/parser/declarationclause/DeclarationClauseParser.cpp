// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "DeclarationClauseParser.h"

DeclarationClauseParser::DeclarationClauseParser() {}

int DeclarationClauseParser::consumeOpenBracket(Token token) {
    if (token.getValue() != "(") {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return 1;
}

int DeclarationClauseParser::consumeCloseBracket(Token token) {
    if (token.getValue() != ")") {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return 1;
}

int DeclarationClauseParser::consumeComma(Token token) {
    if (token.getValue() != ",") {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return 1;
}

int DeclarationClauseParser::consumeEquals(Token token) {
    if (token.getValue() != "=") {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return 1;
}

int DeclarationClauseParser::consumeAnd(Token token) {
    if (!isAnd(token)) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return 1;
}

bool DeclarationClauseParser::isQuotation(Token token) {
    return token.getValue() == "\"";
}

bool DeclarationClauseParser::isTransitive(Token token) {
    return token.getValue() == "*";
}

bool DeclarationClauseParser::isBoolean(Token token) {
    return token.getValue() == "BOOLEAN";
}

bool DeclarationClauseParser::isAnd(Token token) {
    return token.getValue() == "and";
}

void DeclarationClauseParser::updateIfSemantic(ErrorStatus errorStatus,
                                               AbstractQuery &parsedQuery) {
    if (parsedQuery.getQueryStatus() == ErrorStatus::OK) {
        parsedQuery.updateStatus(errorStatus);
    }
}
