// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include "common/tokenizer/Tokenizer.h"
#include "parser/SPParserManager.h"
#include "extractor/DesignExtractor.h"
#include "di/DI.h"

class SourceProcessor {
public:
    SourceProcessor();
    ~SourceProcessor();

    void parse(std::string src, DI& di);

private:
    Tokenizer* tokenizer;
    SPParserManager* parserManager;
    DesignExtractor* designExtractor;
};
