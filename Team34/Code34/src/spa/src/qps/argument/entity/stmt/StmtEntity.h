// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_set>
#include "qps/argument/entity/EntityArgument.h"
#include "qps/argument/validator/ModifiesUsesFirstArg.h"
#include "qps/argument/validator/ParentFollowsNextArg.h"
#include "pkb/interfaces/IStmtGetter.h"
#include "qps/argument/validator/AffectsArg.h"

class StmtEntity : public EntityArgument, public ModifiesUsesFirstArg,
    public ParentFollowsNextArg, public AffectsArg {
protected:
    IStmtGetter* pkbInterface;

    StmtEntity(std::string name, std::string attrRef);
    StmtEntity(IStmtGetter* pkbInterface, std::string name, std::string attrRef);
    void setPKBInterface(IStmtGetter* pkbInterface);

public:
    inline static const std::string TYPE_NAME = "stmt";

    static bool checkInstance(const Argument* ptr);

    std::unordered_set<std::string> getPKBValueList() override;
    void setPKBInterface(DI& di) override;
    std::string getAttrFromPKB(std::string id) override;
    std::string getType() override;
};
