// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_set>
#include "EntityArgument.h"
#include "qps/argument/validator/PatternSynonym.h"
#include "qps/argument/validator/ParentFollowsNextArg.h"
#include "qps/argument/validator/ModifiesUsesSecondArg.h"
#include "qps/argument/validator/ModifiesUsesFirstArg.h"
#include "qps/argument/validator/CallsArg.h"
#include "qps/argument/validator/PatternFirstArg.h"
#include "qps/argument/validator/AffectsArg.h"

class DummyArgument: public EntityArgument, public PatternFirstArg,
        public CallsArg, public ModifiesUsesFirstArg, public ModifiesUsesSecondArg,
        public ParentFollowsNextArg, public PatternSynonym, public AffectsArg {
public:
    DummyArgument();
    inline static const std::string DUMMY = "DUMMY";

    std::string getAttrFromPKB(std::string id) override;
    std::string getType() override;
    void setPKBInterface(DI &di) override;
    std::unordered_set<std::string> getPKBValueList() override;
};
