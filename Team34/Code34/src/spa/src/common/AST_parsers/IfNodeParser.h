// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "OperatorNodeParser.h"
#include "StmtLstNodeParser.h"
#include "sp/node/IfNode.h"

class IfNodeParser {
private:
    int count;
    std::string filePath;
    std::shared_ptr<OperatorNodeParser> operatorNodeParser;
    std::shared_ptr<StmtLstNodeParser> stmtLstNodeParser;

public:
    explicit IfNodeParser(std::string filePath);
    std::string parse(IfNode* node);
    void addStmtLstNodeParser(std::shared_ptr<StmtLstNodeParser> parser);
    void addOperatorNodeParser(std::shared_ptr<OperatorNodeParser> parser);
};
