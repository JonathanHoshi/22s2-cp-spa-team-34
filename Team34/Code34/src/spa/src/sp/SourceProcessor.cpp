// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <vector>
#include <memory>
#include "SourceProcessor.h"
#include "sp/node/RootNode.h"

SourceProcessor::SourceProcessor() {
    tokenizer = new Tokenizer();
    parserManager = new SPParserManager();
    designExtractor = new DesignExtractor();
}

SourceProcessor::~SourceProcessor() {
    delete(tokenizer);
    delete(parserManager);
    delete(designExtractor);
}

void SourceProcessor::parse(std::string src, DI& di) {
    std::vector<Token> tokens = tokenizer->tokenize(src);
    if (tokenizer->hasError()) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    std::shared_ptr<RootNode> node = parserManager->parse(tokens);
    designExtractor->extract(*node, di);
}
