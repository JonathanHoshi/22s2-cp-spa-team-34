// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "StringInput.h"

StringInput::StringInput(std::string input) :
    InputArgument(input), CallsArg() {}

bool StringInput::checkInstance(const Argument* ptr) {
    return dynamic_cast<const StringInput*>(ptr) != nullptr;
}
