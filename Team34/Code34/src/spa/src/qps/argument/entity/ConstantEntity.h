// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_set>
#include "EntityArgument.h"
#include "pkb/interfaces/IConstGetter.h"

class ConstantEntity : public EntityArgument {
private:
    IConstGetter* pkbInterface;

    void setPKBInterface(IConstGetter* pkbInterface);

public:
    inline static const std::string TYPE_NAME = "constant";

    ConstantEntity(std::string value, std::string attrRef);
    ConstantEntity(IConstGetter* pkbInterface, std::string value, std::string attrRef);
    static bool checkInstance(const Argument* ptr);

    std::unordered_set<std::string> getPKBValueList() override;
    void setPKBInterface(DI& di) override;
    std::string getAttrFromPKB(std::string id) override;
    std::string getType() override;
};
