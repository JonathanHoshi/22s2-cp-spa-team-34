// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include "InputArgument.h"
#include "qps/argument/validator/CallsArg.h"
#include "qps/argument/validator/ModifiesUsesSecondArg.h"
#include "qps/argument/validator/ModifiesUsesFirstArg.h"
#include "qps/argument/validator/PatternFirstArg.h"

class StringInput : public InputArgument, public CallsArg,
                    public ModifiesUsesFirstArg, public ModifiesUsesSecondArg,
                    public PatternFirstArg {
public:
    explicit StringInput(std::string input);
    static bool checkInstance(const Argument* ptr);
};
