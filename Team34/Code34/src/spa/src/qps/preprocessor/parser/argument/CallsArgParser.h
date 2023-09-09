// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include "ArgumentParser.h"
#include "ElementParser.h"
#include "qps/argument/entity/WildcardEntity.h"
#include "qps/argument/input/StringInput.h"
#include "common/exceptions/ParserError.h"
#include "EntRefParser.h"


class CallsArgParser : public ArgumentParser {
public:
    CallsArgParser();
    ArgumentResult parse(std::vector<Token> tokens,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
