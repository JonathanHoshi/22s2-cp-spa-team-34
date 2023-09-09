// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include "qps/preprocessor/parser/declarationclause/DeclarationClauseParser.h"

class PatternSyntaxChecker {
protected:
    bool isSyntaxCheck;
public:
    explicit PatternSyntaxChecker(bool isSyntaxCheck);
    void checkForSyntax();
};
