// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>

class Token {
private:
    std::string type;
    std::string val;

public:
    // Default constructor for Token
    Token();

    // Public constructor for Token on QPS side
    explicit Token(std::string val);

    // Public constructor for Token on SP side
    Token(std::string type, std::string val);

    // returns the token's  type
    std::string getType() const;

    // returns the token's value
    std::string getValue() const;

    bool operator==(const Token& other) const;

    bool operator!=(const Token& other) const;
};
