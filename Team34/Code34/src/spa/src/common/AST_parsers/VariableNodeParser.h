// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "sp/node/VariableNode.h"

class VariableNodeParser {
private:
    int count;
    std::string filePath;

public:
    explicit VariableNodeParser(std::string filePath);
    std::string parse(VariableNode* node);
};
