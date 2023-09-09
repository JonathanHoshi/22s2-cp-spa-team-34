// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include "InputArgument.h"
#include "qps/argument/validator/ParentFollowsNextArg.h"
#include "qps/argument/validator/ModifiesUsesFirstArg.h"
#include "qps/argument/validator/AffectsArg.h"

class IntInput : public InputArgument, public ParentFollowsNextArg,
        public ModifiesUsesFirstArg, public AffectsArg {
public:
    explicit IntInput(std::string input);
    static bool checkInstance(const Argument* ptr);
};

