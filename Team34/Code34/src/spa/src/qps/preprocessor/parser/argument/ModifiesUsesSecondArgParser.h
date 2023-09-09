// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include "ArgumentParser.h"
#include "qps/argument/input/StringInput.h"
#include "qps/argument/input/IntInput.h"
#include "qps/argument/validator/ModifiesUsesSecondArg.h"
#include "qps/argument/entity/WildcardEntity.h"
#include "common/exceptions/ErrorStatus.h"
#include "common/exceptions/ParserError.h"
#include "ElementParser.h"
#include "EntRefParser.h"

class ModifiesUsesSecondArgParser : public ArgumentParser {
public:
    ModifiesUsesSecondArgParser();
    ArgumentResult parse(std::vector<Token> tokens,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
