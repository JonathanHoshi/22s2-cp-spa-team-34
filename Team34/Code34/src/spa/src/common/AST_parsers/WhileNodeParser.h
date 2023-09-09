// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "OperatorNodeParser.h"
#include "StmtLstNodeParser.h"
#include "sp/node/WhileNode.h"

class WhileNodeParser {
private:
    int count;
    std::string filePath;
    std::shared_ptr<OperatorNodeParser> operatorNodeParser;
    std::shared_ptr<StmtLstNodeParser> stmtLstNodeParser;

public:
    explicit WhileNodeParser(std::string filePath);
    std::string parse(WhileNode* node);
    void addStmtLstNodeParser(std::shared_ptr<StmtLstNodeParser> parser);
    void addOperatorNodeParser(std::shared_ptr<OperatorNodeParser> parser);
};
