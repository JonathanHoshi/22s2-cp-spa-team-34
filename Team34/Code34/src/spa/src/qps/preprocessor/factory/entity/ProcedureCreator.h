// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <memory>
#include "EntityCreator.h"

class ProcedureCreator : public EntityCreator {
public:
    ProcedureCreator();
    std::shared_ptr<EntityArgument> create(std::string name) override;
    std::shared_ptr<EntityArgument> create(std::string name, std::string attrRef) override;
};
