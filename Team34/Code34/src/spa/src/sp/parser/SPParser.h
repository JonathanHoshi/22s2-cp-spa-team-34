// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "common/tokenizer/Token.h"
#include "common/exceptions/ParserError.h"


class SPParser {
protected:
    int currPos;
    int stmtNo;
    Token currToken;
    std::vector<Token> tokens;

public:
    // Basic constructor
    explicit SPParser(std::vector<Token> tokens);

    // check the token's type
    bool checkToken(std::string type);

    // check the token's type and token's val
    bool checkToken(std::string type, std::string val);

    // verify the token's type
    void verifyToken(std::string type);

    // verify the token's type and token's val
    void verifyToken(std::string type, std::string val);

    void verifyTokenAndTraverse(std::string type);

    void verifyTokenAndTraverse(std::string type, std::string val);

    std::string verifyTokenAndGetValue(std::string type);

    // traverse to the next token
    void traverse();

    // set curr pos
    void setPos(int pos);

    // get curr pos
    int getPos();

    // increment stmt no
    void setStmtNo(int i);

    // get stmt no
    int getStmtNo();
};
