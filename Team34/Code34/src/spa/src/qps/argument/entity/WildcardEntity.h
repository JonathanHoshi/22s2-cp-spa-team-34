// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_set>
#include <memory>
#include <utility>
#include "EntityArgument.h"
#include "qps/argument/validator/ModifiesUsesSecondArg.h"
#include "qps/argument/validator/ParentFollowsNextArg.h"
#include "qps/argument/validator/PatternFirstArg.h"
#include "qps/argument/validator/CallsArg.h"
#include "qps/argument/validator/AffectsArg.h"

class WildcardEntity : public EntityArgument, public CallsArg,
        public ModifiesUsesSecondArg, public ParentFollowsNextArg,
        public PatternFirstArg, public AffectsArg {
private:
    std::shared_ptr<EntityArgument> wildEntityType;

public:
    WildcardEntity();

    inline static const std::string TYPE_NAME = "wildcard";
    static bool checkInstance(const Argument* ptr);
    static WildcardEntity* cast(Argument* ptr);

    void assignEntityType(std::shared_ptr<EntityArgument> entity);

    std::unordered_set<std::string> getPKBValueList() override;
    void setPKBInterface(DI& di) override;
    std::string getAttrFromPKB(std::string id) override;
    std::string getType() override;

    bool operator==(const Argument& other) const override;
};
