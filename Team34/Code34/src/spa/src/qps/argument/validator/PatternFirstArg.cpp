// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "PatternFirstArg.h"

PatternFirstArg::PatternFirstArg() {}

bool PatternFirstArg::checkInstance(const Argument* ptr) {
    return dynamic_cast<const PatternFirstArg*>(ptr) != nullptr;
}
