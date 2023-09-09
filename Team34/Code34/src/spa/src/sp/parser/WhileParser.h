// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <vector>
#include <memory>
#include "SPStmtParser.h"
#include "SPExpressionParser.h"
#include "StmtLstParser.h"

class WhileParser : public SPStmtParser {
private:
    std::shared_ptr<SPExpressionParser> condExprParser;
    std::shared_ptr<StmtLstParser> stmtLstParser;

public:
    explicit WhileParser(std::vector<Token> tokens);

    void addCondExprParser(std::shared_ptr<SPExpressionParser> parser);
    void addStmtLstParser(std::shared_ptr<StmtLstParser> parser);
    std::shared_ptr<StmtLstNode> consumeStmtLst();
    std::shared_ptr<ExpressionNode> consumeCondExpr();
    std::shared_ptr<StmtNode> parse() override;
};
