// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "IntInput.h"

IntInput::IntInput(std::string input) : InputArgument(input) {}

bool IntInput::checkInstance(const Argument* ptr) {
    return dynamic_cast<const IntInput*>(ptr) != nullptr;
}
