// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "AssignNodeParser.h"
#include "CallNodeParser.h"
#include "ReadNodeParser.h"
#include "PrintNodeParser.h"
#include "sp/node/StmtLstNode.h"

class WhileNodeParser;
class IfNodeParser;

class StmtLstNodeParser {
private:
    int count;
    std::string filePath;
    std::shared_ptr<AssignNodeParser> assignNodeParser;
    std::shared_ptr<CallNodeParser> callNodeParser;
    std::shared_ptr<ReadNodeParser> readNodeParser;
    std::shared_ptr<PrintNodeParser> printNodeParser;
    std::shared_ptr<IfNodeParser> ifNodeParser;
    std::shared_ptr<WhileNodeParser> whileNodeParser;

public:
    explicit StmtLstNodeParser(std::string filePath);
    std::string parse(StmtLstNode* node);
    std::string checkType(EntityNode* node);
    void addAssignNodeParser(std::shared_ptr<AssignNodeParser> parser);
    void addCallNodeParser(std::shared_ptr<CallNodeParser> parser);
    void addReadNodeParser(std::shared_ptr<ReadNodeParser> parser);
    void addPrintNodeParser(std::shared_ptr<PrintNodeParser> parser);
    void addIfNodeParser(std::shared_ptr<IfNodeParser> parser);
    void addWhileNodeParser(std::shared_ptr<WhileNodeParser> parser);
};
