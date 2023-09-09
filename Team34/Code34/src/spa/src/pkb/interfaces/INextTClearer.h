// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include "di/IService.h"

class INextTClearer : public virtual IService {
public:
    ~INextTClearer() override = default;

    virtual void clearNextT() = 0;  // Adds next relation
};
