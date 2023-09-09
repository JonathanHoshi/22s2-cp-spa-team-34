// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <vector>
#include <memory>
#include "SPStmtParser.h"

class ReadParser : public SPStmtParser {
public:
    explicit ReadParser(std::vector<Token> tokens);

    std::shared_ptr<StmtNode> parse() override;
};
