// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "VariableNodeParser.h"
#include "OperatorNodeParser.h"
#include "sp/node/AssignNode.h"

class AssignNodeParser {
private:
    int count;
    std::string filePath;
    std::shared_ptr<VariableNodeParser> variableNodeParser;
    std::shared_ptr<OperatorNodeParser> operatorNodeParser;

public:
    explicit AssignNodeParser(std::string filePath);
    std::string parse(AssignNode* node);
    void addVariableNodeParser(std::shared_ptr<VariableNodeParser> parser);
    void addOperatorNodeParser(std::shared_ptr<OperatorNodeParser> parser);
};
