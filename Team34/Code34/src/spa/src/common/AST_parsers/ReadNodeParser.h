// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "VariableNodeParser.h"
#include "sp/node/ReadNode.h"

class ReadNodeParser {
private:
    int count;
    std::string filePath;
    std::shared_ptr<VariableNodeParser> variableNodeParser;

public:
    explicit ReadNodeParser(std::string filePath);
    std::string parse(ReadNode* node);
    void addVariableNodeParser(std::shared_ptr<VariableNodeParser> parser);
};
