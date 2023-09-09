// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include "Token.h"

class NumberToken : public Token {
public:
    inline static const std::string TYPE_NAME = "NUMBER";
    explicit NumberToken(std::string val);
};
