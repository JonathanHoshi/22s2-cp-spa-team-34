// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include "qps/argument/Argument.h"
#include "common/exceptions/ErrorStatus.h"

class ArgumentResult {
private:
    std::shared_ptr<Argument> arg;
    int pos;
    ErrorStatus errorStatus;
public:
    ArgumentResult(std::shared_ptr<Argument> arg, int pos, ErrorStatus errorStatus);
    std::shared_ptr<Argument> getArg();
    int getPos();
    ErrorStatus getErrorStatus();
};
