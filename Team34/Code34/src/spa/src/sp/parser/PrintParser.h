// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <vector>
#include <memory>
#include "SPStmtParser.h"

class PrintParser : public SPStmtParser {
public:
    explicit PrintParser(std::vector<Token> tokens);

    std::shared_ptr<StmtNode> parse() override;
};
