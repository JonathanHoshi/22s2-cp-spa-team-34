// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include "ClauseCreator.h"

class TransitiveClauseCreator : public ClauseCreator {
protected:
    bool isTransitive;
public:
    void setIsTransitive(bool isTransitive);
    explicit TransitiveClauseCreator(bool isTransitive);
    virtual std::shared_ptr<Clause> create(std::shared_ptr<Argument> firstArg,
        std::shared_ptr<Argument> secondArg) = 0;
};
