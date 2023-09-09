// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "ArgumentParser.h"
#include "common/tokenizer/NumberToken.h"
#include "qps/argument/input/IntInput.h"
#include "qps/argument/entity/WildcardEntity.h"
#include "common/tokenizer/IdentityToken.h"
#include "ElementParser.h"

class StmtRefParser: public ArgumentParser {
public:
    StmtRefParser();
    ArgumentResult parse(std::vector<Token> tokens,
                         std::unordered_map<std::string,
                         std::shared_ptr<EntityArgument>> declarations,
                         int pos) override;
};
