// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "sp/node/ConstantNode.h"

class ConstantNodeParser {
private:
    int count;
    std::string filePath;

public:
    explicit ConstantNodeParser(std::string filePath);
    std::string parse(ConstantNode* node);
};
