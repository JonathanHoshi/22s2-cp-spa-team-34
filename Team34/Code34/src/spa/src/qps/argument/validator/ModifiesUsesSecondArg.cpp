// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ModifiesUsesSecondArg.h"

ModifiesUsesSecondArg::ModifiesUsesSecondArg() {}

bool ModifiesUsesSecondArg::checkInstance(const Argument* ptr) {
    return dynamic_cast<const ModifiesUsesSecondArg*>(ptr) != nullptr;
}
