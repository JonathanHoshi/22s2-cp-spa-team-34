// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <memory>
#include "di/IService.h"
#include "sp/node/ExpressionNode.h"

class IAssignPatternAdder : public virtual IService {
public:
    ~IAssignPatternAdder() override = default;

    virtual void
        addAssignPattern(const int& stmtNum, const std::string& leftVal,
            const std::shared_ptr<ExpressionNode>& expressionPtr) = 0;
};
