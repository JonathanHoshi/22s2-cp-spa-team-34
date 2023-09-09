// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#pragma once

#include <memory>
#include "qps/argument/Argument.h"
#include "common/exceptions/ErrorStatus.h"

class WithArgsValidator {
private:
    static bool isName(std::shared_ptr<Argument> arg);
    static bool isNumber(std::shared_ptr<Argument> arg);
public:
    WithArgsValidator();
    static ErrorStatus validate(std::shared_ptr<Argument> firstArg,
                                std::shared_ptr<Argument> secondArg);
};
