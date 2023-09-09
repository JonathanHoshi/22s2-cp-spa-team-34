// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include "EntityCreator.h"
#include "qps/argument/entity/stmt/CallStmtEntity.h"

class CallCreator : public EntityCreator {
public:
    CallCreator();
    std::shared_ptr<EntityArgument> create(std::string name) override;
    std::shared_ptr<EntityArgument> create(std::string name, std::string attrRef) override;
};
