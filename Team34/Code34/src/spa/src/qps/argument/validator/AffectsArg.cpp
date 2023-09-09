// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "AffectsArg.h"

AffectsArg::AffectsArg() {}

bool AffectsArg::checkInstance(const Argument* ptr) {
    return dynamic_cast<const AffectsArg*>(ptr) != nullptr;
}
