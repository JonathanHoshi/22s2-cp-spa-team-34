// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "TransitiveClauseCreator.h"

TransitiveClauseCreator::TransitiveClauseCreator(bool isTransitive) : ClauseCreator() {
    this->isTransitive = isTransitive;
}

void TransitiveClauseCreator::setIsTransitive(bool isTransitive) {
    this->isTransitive = isTransitive;
}
