// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <memory>
#include "InputArgument.h"
#include "sp/node/ExpressionNode.h"

class ExpressionInput : public InputArgument {
private:
    bool isPartial;
    std::shared_ptr<ExpressionNode> ast;
public:
    ExpressionInput(std::string input, std::shared_ptr<ExpressionNode> ast, bool isPartial);
    bool getIsPartial();
    std::shared_ptr<ExpressionNode> getAst();
    static bool checkInstance(const Argument* ptr);
};
