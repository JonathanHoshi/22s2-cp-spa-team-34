// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <string>
#include <unordered_set>
#include "DummyArgument.h"


DummyArgument::DummyArgument() : EntityArgument("DUMMY", "value") {}

std::string DummyArgument::getType() {
    return DUMMY;
}

std::string DummyArgument::getAttrFromPKB(std::string id) {
    return DUMMY;
}

void DummyArgument::setPKBInterface(DI &di) {
}

std::unordered_set<std::string> DummyArgument::getPKBValueList() {
    return {DUMMY};
}
