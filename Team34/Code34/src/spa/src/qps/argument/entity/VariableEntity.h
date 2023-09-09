// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_set>
#include "EntityArgument.h"
#include "pkb/interfaces/IVarGetter.h"
#include "qps/argument/validator/PatternFirstArg.h"
#include "qps/argument/validator/ModifiesUsesSecondArg.h"

class VariableEntity : public EntityArgument,
    public ModifiesUsesSecondArg, public PatternFirstArg {
private:
    IVarGetter* pkbInterface;

    void setPKBInterface(IVarGetter* pkbInterface);

public:
    inline static const std::string TYPE_NAME = "variable";

    VariableEntity(std::string name, std::string attrRef);
    VariableEntity(IVarGetter* pkbInterface, std::string name, std::string attrRef);
    static bool checkInstance(const Argument* ptr);

    std::unordered_set<std::string> getPKBValueList() override;
    void setPKBInterface(DI& di) override;
    std::string getAttrFromPKB(std::string id) override;
    std::string getType() override;
};
