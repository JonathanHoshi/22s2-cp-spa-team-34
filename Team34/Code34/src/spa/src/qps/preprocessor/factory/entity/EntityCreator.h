// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <memory>
#include <unordered_set>
#include "qps/argument/Argument.h"
#include "qps/argument/entity/EntityArgument.h"

class EntityCreator {
protected:
    std::unordered_set<std::string> validAttrRefs;
public:
    inline static const std::string STMT_ATTR = "stmt#";
    inline static const std::string VARNAME_ATTR = "varName";
    inline static const std::string PROCNAME_ATTR = "procName";
    inline static const std::string VALUE_ATTR = "value";
    EntityCreator() {}
    static std::string isAttrRefValid(std::unordered_set<std::string> validAttrRefs,
        std::string attrRef);
    virtual std::shared_ptr<EntityArgument> create(std::string name) = 0;
    virtual std::shared_ptr<EntityArgument> create(std::string name, std::string attrRef) = 0;
};
