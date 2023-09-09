// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <memory>
#include "EntityCreator.h"
#include "qps/argument/entity/EntityArgument.h"

class ConstantCreator : public EntityCreator {
public:
    ConstantCreator();
    std::shared_ptr<EntityArgument> create(std::string name) override;
    std::shared_ptr<EntityArgument> create(std::string name, std::string attrRef) override;
};
