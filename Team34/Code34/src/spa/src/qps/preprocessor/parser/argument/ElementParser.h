// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "ArgumentParser.h"
#include "qps/preprocessor/factory/utils/CreatorMap.h"
#include "qps/argument/input/StringInput.h"
#include "qps/argument/entity/DummyArgument.h"

class ElementParser : public ArgumentParser {
private:
    bool canBeAttrRef;
    bool isAttrRef;
    bool isDot(Token token);
    void canBeSynonym();
    void cannotBeAttrRef();
    std::string findAttrRef(std::vector<Token> tokens, int pos);
    std::unordered_set<std::string> validAttrRefs;
    std::shared_ptr<EntityArgument> dummyElement;
public:
    explicit ElementParser(bool canBeAttrRef);
    void mustBeAttrRef();
    ArgumentResult parse(std::vector<Token> tokens,
        std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
        int pos) override;
};
