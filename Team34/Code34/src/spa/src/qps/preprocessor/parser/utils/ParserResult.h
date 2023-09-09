// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "qps/query/AbstractQuery.h"

class ParserResult {
private:
    AbstractQuery parsedQuery;
    int pos;
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations;
public:
    ParserResult(std::unordered_map<std::string,
        std::shared_ptr<EntityArgument>> declarations, int pos);
    int getPos();
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> getDeclarations();
};
