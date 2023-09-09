// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "sp/node/CallNode.h"

class CallNodeParser {
private:
    int count;
    std::string filePath;

public:
    explicit CallNodeParser(std::string filePath);
    std::string parse(CallNode* node);
};
