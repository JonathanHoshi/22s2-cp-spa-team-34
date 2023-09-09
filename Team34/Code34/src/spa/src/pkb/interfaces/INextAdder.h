// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include "di/IService.h"

class INextAdder : public virtual IService {
public:
    ~INextAdder() override = default;

    virtual void addNext(const int& front, const int& back) = 0;  // Adds next relation
};
