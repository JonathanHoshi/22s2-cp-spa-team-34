// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "ArgumentParser.h"
#include "qps/argument/input/IntInput.h"
#include "qps/argument/entity/WildcardEntity.h"
#include "common/exceptions/ErrorStatus.h"
#include "common/exceptions/ParserError.h"
#include "qps/argument/validator/ParentFollowsNextArg.h"
#include "ElementParser.h"
#include "StmtRefParser.h"

class ParentFollowsNextAffectsArgParser : public ArgumentParser {
public:
    ParentFollowsNextAffectsArgParser();
    ArgumentResult parse(std::vector<Token> tokens,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
