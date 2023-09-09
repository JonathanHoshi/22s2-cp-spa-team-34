// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "InputArgument.h"

InputArgument::InputArgument(std::string input) : Argument(input) {}

bool InputArgument::checkInstance(const Argument* ptr) {
    return dynamic_cast<const InputArgument*>(ptr) != nullptr;
}

InputArgument* InputArgument::cast(Argument* ptr) {
    return dynamic_cast<InputArgument*>(ptr);
}
