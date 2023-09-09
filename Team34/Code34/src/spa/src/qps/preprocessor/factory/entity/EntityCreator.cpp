// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "EntityCreator.h"
#include "common/exceptions/ParserError.h"

std::string EntityCreator::isAttrRefValid(std::unordered_set<std::string> validAttrRefs,
    std::string attrRef) {
    if (validAttrRefs.find(attrRef) == validAttrRefs.end()) {
        throw ParserError(ErrorStatus::SEMANTIC);
    }
    return attrRef;
}
