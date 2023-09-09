// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "Element.h"

Element::Element(std::string attrRef) : attrRef(attrRef) {}

std::string Element::getAttrRef() {
    return attrRef;
}
