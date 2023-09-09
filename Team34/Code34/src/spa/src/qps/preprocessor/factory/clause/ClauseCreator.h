// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include "qps/clause/Clause.h"

class ClauseCreator {
public:
    virtual std::shared_ptr<Clause>
        create(std::shared_ptr<Argument> firstArg, std::shared_ptr<Argument> secondArg) = 0;
};
