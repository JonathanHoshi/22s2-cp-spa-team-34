// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <queue>
#include "pkb/base/BaseMapSet.h"
#include "pkb/base/BaseMap.h"

class CyclicTTable {
protected:
    void generateT(const int& key, BaseMapSet<int, int>& direction,
        BaseMapSet<int, int>& directionT);
};
