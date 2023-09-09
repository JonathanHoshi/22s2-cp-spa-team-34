// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "VariableNodeParser.h"
#include "ConstantNodeParser.h"
#include "sp/node/OperatorNode.h"

class OperatorNodeParser {
private:
    int count;
    std::string filePath;
    std::shared_ptr<VariableNodeParser> variableNodeParser;
    std::shared_ptr<ConstantNodeParser> constantNodeParser;

public:
    explicit OperatorNodeParser(std::string filePath);
    std::string parse(OperatorNode* node);
    std::string checkType(ExpressionNode* node);
    void addVariableNodeParser(std::shared_ptr<VariableNodeParser> parser);
    void addConstantNodeParser(std::shared_ptr<ConstantNodeParser> parser);
};
