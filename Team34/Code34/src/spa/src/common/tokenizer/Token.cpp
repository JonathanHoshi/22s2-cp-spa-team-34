// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "Token.h"

Token::Token() {
    this->type = "null";
    this->val = "null";
}

Token::Token(std::string val) {
    this->type = "null";
    this->val = val;
}

Token::Token(std::string type, std::string val) {
    this->type = type;
    this->val = val;
}

std::string Token::getType() const {
    return this->type;
}

std::string Token::getValue() const {
    return this->val;
}

bool Token::operator==(const Token& other) const {
    return this->type == other.type && this->val == other.val;
}

bool Token::operator!=(const Token& other) const {
    return this->type != other.type || this->val != other.val;
}
