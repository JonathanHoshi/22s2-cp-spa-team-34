// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <stdexcept>
#include "SPParser.h"
#include "common/tokenizer/EofToken.h"

SPParser::SPParser(std::vector<Token> tokens) {
    this->currPos = 0;
    this->tokens = tokens;
    this->currToken = tokens[0];
    this->stmtNo = 0;
}

bool SPParser::checkToken(std::string type) {
    return currToken.getType() == type;
}

bool SPParser::checkToken(std::string type, std::string val) {
    return currToken.getType() == type && currToken.getValue() == val;
}

void SPParser::verifyToken(std::string type) {
    if (currToken.getType() != type) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
}

void SPParser::verifyToken(std::string type, std::string val) {
    if (currToken.getType() != type || currToken.getValue() != val) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
}

void SPParser::traverse() {
    currPos++;

    if (currPos >= tokens.size()) {
        currToken = EofToken();
    } else {
        currToken = tokens[currPos];
    }
}

void SPParser::verifyTokenAndTraverse(std::string type) {
    verifyToken(type);
    traverse();
}

void SPParser::verifyTokenAndTraverse(std::string type, std::string val) {
    verifyToken(type, val);
    traverse();
}

std::string SPParser::verifyTokenAndGetValue(std::string type) {
    verifyToken(type);
    return currToken.getValue();
}

int SPParser::getPos() {
    return this->currPos;
}

void SPParser::setPos(int i) {
    this->currPos = i;

    if (i >= this->tokens.size()) {
        this->currToken = EofToken();
    } else {
        this->currToken = this->tokens[i];
    }
}

int SPParser::getStmtNo() {
    return this->stmtNo;
}

void SPParser::setStmtNo(int i) {
    this->stmtNo = i;
}
