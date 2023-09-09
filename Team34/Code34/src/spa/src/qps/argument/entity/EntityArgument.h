// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_set>
#include "di/DI.h"
#include "qps/argument/Argument.h"

class EntityArgument : public Argument {
protected:
    std::string attrRef;

    EntityArgument(std::string input, std::string attrRef);

public:
    static bool checkInstance(const Argument* ptr);
    static EntityArgument* cast(Argument* ptr);
    std::string getAttrRef();
    virtual std::unordered_set<std::string> getPKBValueList() = 0;
    virtual void setPKBInterface(DI& di) = 0;
    virtual std::string getAttrFromPKB(std::string id) = 0;
    virtual std::string getType() = 0;
};
