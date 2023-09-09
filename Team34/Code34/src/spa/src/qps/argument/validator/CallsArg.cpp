// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "CallsArg.h"

CallsArg::CallsArg() {}

bool CallsArg::checkInstance(const Argument* ptr) {
    return dynamic_cast<const CallsArg*>(ptr) != nullptr;
}
