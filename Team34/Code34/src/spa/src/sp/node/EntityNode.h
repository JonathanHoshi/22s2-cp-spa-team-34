// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include <vector>

class ExtractorVisitor;

class EntityNode {
public:
    virtual void accept(ExtractorVisitor& e) = 0;
};
