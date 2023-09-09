// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include "SPParser.h"
#include "sp/node/StmtNode.h"

class SPStmtParser : public SPParser {
public:
    explicit SPStmtParser(std::vector<Token> tokens);

    virtual std::shared_ptr<StmtNode> parse() = 0;
};
