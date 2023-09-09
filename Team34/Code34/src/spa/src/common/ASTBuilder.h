// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <memory>
#include "sp/node/RootNode.h"

class ASTBuilder {
public:
    static void buildAST(std::shared_ptr<RootNode> AST, std::string path);
};
