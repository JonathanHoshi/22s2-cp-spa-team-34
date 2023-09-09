// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_set>
#include "EntityArgument.h"
#include "pkb/interfaces/IProcGetter.h"
#include "qps/argument/validator/CallsArg.h"
#include "qps/argument/validator/ModifiesUsesFirstArg.h"

class ProcedureEntity : public EntityArgument, public ModifiesUsesFirstArg, public CallsArg {
private:
    IProcGetter* pkbInterface;

    void setPKBInterface(IProcGetter* pkbInterface);

public:
    inline static const std::string TYPE_NAME = "procedure";

    ProcedureEntity(std::string name, std::string attrRef);
    ProcedureEntity(IProcGetter* pkbInterface, std::string name, std::string attrRef);
    static bool checkInstance(const Argument* ptr);

    std::unordered_set<std::string> getPKBValueList() override;
    void setPKBInterface(DI& di) override;
    std::string getAttrFromPKB(std::string id) override;
    std::string getType() override;
};
