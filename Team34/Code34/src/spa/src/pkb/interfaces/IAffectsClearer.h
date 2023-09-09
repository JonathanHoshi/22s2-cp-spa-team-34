// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include "di/IService.h"

class IAffectsClearer : public virtual IService {
public:
    ~IAffectsClearer() override = default;

    virtual void clearAffectsAndT() = 0;
};
