// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ParserResult.h"

ParserResult::ParserResult(std::unordered_map<std::string,
    std::shared_ptr<EntityArgument>> declarations,
    int pos) : declarations(declarations), pos(pos) {}

int ParserResult::getPos() {
    return pos;
}

std::unordered_map<std::string, std::shared_ptr<EntityArgument>> ParserResult::getDeclarations() {
    return declarations;
}
