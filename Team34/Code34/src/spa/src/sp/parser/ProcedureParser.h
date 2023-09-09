// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <vector>
#include <memory>
#include "SPParser.h"
#include "StmtLstParser.h"
#include "sp/node/ProcedureNode.h"

class ProcedureParser : public SPParser {
private:
    std::shared_ptr<StmtLstParser> stmtLstParser;

public:
    explicit ProcedureParser(std::vector<Token> tokens);

    void addStmtLstParser(std::shared_ptr<StmtLstParser> parser);
    std::shared_ptr<StmtLstNode> consumeStmtLst();
    std::shared_ptr<ProcedureNode> parse();
};
