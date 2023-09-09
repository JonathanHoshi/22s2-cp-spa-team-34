// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "ArgumentParser.h"
#include "ElementParser.h"
#include "common/exceptions/ErrorStatus.h"
#include "common/exceptions/ParserError.h"
#include "qps/argument/validator/PatternFirstArg.h"
#include "qps/argument/entity/WildcardEntity.h"
#include "EntRefParser.h"

class PatternFirstArgParser : public ArgumentParser {
public:
    PatternFirstArgParser();
    ArgumentResult parse(std::vector<Token> tokens,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
