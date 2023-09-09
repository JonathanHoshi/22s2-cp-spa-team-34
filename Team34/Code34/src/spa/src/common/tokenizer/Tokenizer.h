// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <vector>
#include "Token.h"
#include "NumberToken.h"
#include "IdentityToken.h"
#include "PunctuationToken.h"
#include <unordered_set>
#include "common/exceptions/ErrorStatus.h"
#include "common/exceptions/ParserError.h"

class Tokenizer {
private:
    int pos;
    std::string input;
    std::string currString;
    bool error;
    std::vector<Token> tokens;
    const std::unordered_set<std::string> EQUALITY_SET =
        std::unordered_set<std::string>({"&&", "||", ">=", "<=", "==", "!="});


    char peek();
    char peekNext();
    void advance();
    void skip();
    bool reachedEOF();
    void readToken();
    void readIdentity();
    void readNumber();
    void readPunctuation();
    void addToken(Token token);
    void clearString();


public:
    Tokenizer();
    std::vector<Token> tokenize(std::string input);
    bool hasError();
    std::vector<Token> getTokens();
};
