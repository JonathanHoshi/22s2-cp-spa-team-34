// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <vector>

#include "sp/node/RootNode.h"
#include "ExtractorVisitor.h"
#include "di/DI.h"

class DesignExtractor {
private:
    std::vector<ExtractorVisitor*> extractors;
    void registerExtractors(DI& di);
    void clearExtractors();

public:
    DesignExtractor();
    void extract(RootNode& root, DI& di);
};
