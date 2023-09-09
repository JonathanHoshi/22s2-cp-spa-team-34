// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include "qps/argument/Argument.h"

class InputArgument : public Argument {
protected:
    explicit InputArgument(std::string input);
public:
    static bool checkInstance(const Argument* ptr);
    static InputArgument* cast(Argument* ptr);
};
