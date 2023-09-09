// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "ProcedureNodeParser.h"
#include "sp/node/RootNode.h"

class RootNodeParser {
private:
    int count;
    std::string filePath;
    std::shared_ptr<ProcedureNodeParser> procedureNodeParser;

public:
    explicit RootNodeParser(std::string filePath);
    std::string parse(RootNode* node);
    void addProcedureNodeParser(std::shared_ptr<ProcedureNodeParser> parser);
};
