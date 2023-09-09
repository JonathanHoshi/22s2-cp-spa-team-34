// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "ArgumentParser.h"
#include "common/exceptions/ErrorStatus.h"
#include "common/exceptions/ParserError.h"
#include "qps/argument/entity/DummyArgument.h"
#include "common/tokenizer/IdentityToken.h"
#include "ElementParser.h"

class PatternTypeParser : public ArgumentParser {
public:
    PatternTypeParser();
    ArgumentResult parse(std::vector<Token> tokens,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
