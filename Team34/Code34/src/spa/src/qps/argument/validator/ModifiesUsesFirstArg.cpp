// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ModifiesUsesFirstArg.h"

ModifiesUsesFirstArg::ModifiesUsesFirstArg() {}

bool ModifiesUsesFirstArg::checkInstance(const Argument* ptr) {
    return dynamic_cast<const ModifiesUsesFirstArg*>(ptr) != nullptr;
}
