// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "PatternSynonym.h"

PatternSynonym::PatternSynonym() {}

bool PatternSynonym::checkInstance(const Argument* ptr) {
    return dynamic_cast<const PatternSynonym*>(ptr) != nullptr;
}
