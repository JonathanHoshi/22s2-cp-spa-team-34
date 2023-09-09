// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "StmtLstNodeParser.h"
#include "sp/node/ProcedureNode.h"

class ProcedureNodeParser {
private:
    int count;
    std::string filePath;
    std::shared_ptr<StmtLstNodeParser> stmtLstNodeParser;

public:
    explicit ProcedureNodeParser(std::string filePath);
    std::string parse(ProcedureNode* node);
    void addStmtLstNodeParser(std::shared_ptr<StmtLstNodeParser> parser);
};
