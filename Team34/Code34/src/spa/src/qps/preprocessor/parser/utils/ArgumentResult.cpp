// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ArgumentResult.h"

ArgumentResult::ArgumentResult(std::shared_ptr<Argument> arg, int pos, ErrorStatus errorStatus) :
    arg(arg), pos(pos), errorStatus(errorStatus) {}

std::shared_ptr<Argument> ArgumentResult::getArg() {
    return arg;
}

int ArgumentResult::getPos() {
    return pos;
}

ErrorStatus ArgumentResult::getErrorStatus() {
    return errorStatus;
}
