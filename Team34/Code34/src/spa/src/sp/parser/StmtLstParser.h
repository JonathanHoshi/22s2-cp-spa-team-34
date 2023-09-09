// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <vector>
#include <memory>
#include "SPParser.h"
#include "SPStmtParser.h"
#include "sp/node/StmtLstNode.h"

class StmtLstParser : public SPParser {
private:
    std::vector<std::shared_ptr<SPStmtParser>> stmtParsers;

public:
    explicit StmtLstParser(std::vector<Token> tokens);

    void addStmtParser(std::shared_ptr<SPStmtParser> parser);

    std::shared_ptr<StmtNode> consumeStmt();

    std::shared_ptr<StmtLstNode> parse();
};
