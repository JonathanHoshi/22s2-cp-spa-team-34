// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "ArgumentParser.h"

class AssignPatternSecondArgParser : public ArgumentParser {
public:
    AssignPatternSecondArgParser();
    ArgumentResult parse(std::vector<Token> tokens,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
