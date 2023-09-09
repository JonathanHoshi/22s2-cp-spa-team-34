// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>

class Element {
private:
    std::string attrRef;
public:
    explicit Element(std::string attrRef);
    std::string getAttrRef();
};
