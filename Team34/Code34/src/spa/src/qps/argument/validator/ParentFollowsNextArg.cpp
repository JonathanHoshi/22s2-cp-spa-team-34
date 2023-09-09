// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ParentFollowsNextArg.h"

ParentFollowsNextArg::ParentFollowsNextArg() {}

bool ParentFollowsNextArg::checkInstance(const Argument* ptr) {
    return dynamic_cast<const ParentFollowsNextArg*>(ptr) != nullptr;
}
