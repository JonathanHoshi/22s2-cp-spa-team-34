// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <string>
#include "EntityCreator.h"
#include "qps/argument/entity/stmt/StmtEntity.h"

class StmtCreator : public EntityCreator {
public:
    StmtCreator();
    std::shared_ptr<EntityArgument> create(std::string name);
    std::shared_ptr<EntityArgument> create(std::string name, std::string attrRef);
};
