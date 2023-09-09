// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ExpressionInput.h"

ExpressionInput::ExpressionInput(std::string input,
    std::shared_ptr<ExpressionNode> ast, bool isPartial) : InputArgument(input) {
    this->ast = ast;
    this->isPartial = isPartial;
}

bool ExpressionInput::checkInstance(const Argument* ptr) {
    return dynamic_cast<const ExpressionInput*>(ptr) != nullptr;
}

bool ExpressionInput::getIsPartial() {
    return isPartial;
}

std::shared_ptr<ExpressionNode> ExpressionInput::getAst() {
    return ast;
}
