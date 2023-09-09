// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <vector>
#include "SPStmtParser.h"

class CallParser : public SPStmtParser {
public:
    explicit CallParser(std::vector<Token> tokens);

    std::shared_ptr<StmtNode> parse() override;
};
