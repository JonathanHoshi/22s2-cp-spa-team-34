// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "PatternSyntaxChecker.h"

PatternSyntaxChecker::PatternSyntaxChecker(bool isSyntaxCheck):
    isSyntaxCheck(isSyntaxCheck) {}

void PatternSyntaxChecker::checkForSyntax() {
    isSyntaxCheck = true;
}
