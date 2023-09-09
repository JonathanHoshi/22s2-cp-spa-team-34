// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include "ArgumentParser.h"
#include "qps/argument/input/StringInput.h"
#include "qps/argument/input/IntInput.h"
#include "qps/preprocessor/parser/argument/ElementParser.h"
#include "common/exceptions/ErrorStatus.h"
#include "common/exceptions/ParserError.h"
#include "common/tokenizer/NumberToken.h"
#include "common/tokenizer/IdentityToken.h"

class WithArgParser : public ArgumentParser {
public:
    WithArgParser();
    ArgumentResult parse(std::vector<Token> tokens,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
