// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include "qps/argument/Argument.h"

class ModifiesUsesFirstArg {
public:
    ModifiesUsesFirstArg();
    static bool checkInstance(const Argument* ptr);
};
