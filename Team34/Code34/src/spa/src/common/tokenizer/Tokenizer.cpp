// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "Tokenizer.h"

Tokenizer::Tokenizer() {
    this->input = "";
    this->error = false;
    this->pos = 0;
}

bool Tokenizer::hasError() {
    return error;
}

std::vector<Token> Tokenizer::getTokens() {
    return tokens;
}

void Tokenizer::advance() {
    if (reachedEOF()) {
        currString = EOF;
    } else {
        currString += input[pos];
        pos++;
    }
}

void Tokenizer::skip() {
    if (reachedEOF()) {
        currString += EOF;
    } else {
        pos++;
    }
}

bool Tokenizer::reachedEOF() {
    if (pos == input.length()) {
        return true;
    }
    return false;
}

char Tokenizer::peek() {
    if (reachedEOF()) {
        return false;
    }
    return input[pos];
}

char Tokenizer::peekNext() {
    if (reachedEOF()) {
        return false;
    }
    return input[pos + 1];
}

void Tokenizer::clearString() {
    currString = "";
}

void Tokenizer::readToken() {
    char c = peek();

    if (static_cast<unsigned char>(c) > 127) {
        // checking for non-ASCII characters
        error = true;
        return;
    }

    if (isdigit(c)) {
        readNumber();
    } else if (isalnum(c)) {
        readIdentity();
    } else if (ispunct(c)) {
        readPunctuation();
    } else if (isspace(c)) {
        skip();
    } else {
        error = true;
    }
}

void Tokenizer::readNumber() {
    while (isdigit(peek())) {
        advance();
    }

    if (currString.length() > 1 && currString.at(0) == '0') {
        error = true;
        return;
    }
    addToken(NumberToken(currString));
}


void Tokenizer::readIdentity() {
    while (isalnum(peek())) {
        advance();
    }
    addToken(IdentityToken(currString));
}


void Tokenizer::readPunctuation() {
    std::string curr = std::string(1, peek()) + peekNext();
    advance();

    if (EQUALITY_SET.find(curr) != EQUALITY_SET.end()) {
        advance();
    }

    addToken(PunctuationToken(currString));
}

void Tokenizer::addToken(Token token) {
    tokens.push_back(token);
}

std::vector<Token> Tokenizer::tokenize(std::string input) {
    this->input = input;

    while (!reachedEOF() && !error) {
        readToken();
        clearString();
    }
    return tokens;
}
