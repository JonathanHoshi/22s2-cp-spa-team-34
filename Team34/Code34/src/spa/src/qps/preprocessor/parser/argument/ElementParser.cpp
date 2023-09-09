// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ElementParser.h"
#include "common/exceptions/ParserError.h"


ElementParser::ElementParser(bool canBeAttrRef) : ArgumentParser() {
    this->validAttrRefs = std::unordered_set<std::string>({"procName",
        "varName", "value", "stmt"});
    this->canBeAttrRef = canBeAttrRef;
    this->isAttrRef = false;
    this->dummyElement = std::make_shared<DummyArgument>();
}

bool ElementParser::isDot(Token token) {
    return token.getValue() == ".";
}

void ElementParser::mustBeAttrRef() {
    isAttrRef = true;
}

void ElementParser::canBeSynonym() {
    if (isAttrRef) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
}

void ElementParser::cannotBeAttrRef() {
    if (!canBeAttrRef) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
}

std::string ElementParser::findAttrRef(std::vector<Token> tokens, int pos) {
    if (validAttrRefs.find(tokens[pos].getValue()) == validAttrRefs.end()) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    Token firstToken = tokens[pos];
    if (firstToken.getValue() != "stmt") {
        return firstToken.getValue();
    }
    pos++;
    if (pos >= tokens.size() || tokens[pos].getValue() != "#") {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return firstToken.getValue() + tokens[pos].getValue();
}

ArgumentResult ElementParser::parse(std::vector<Token> tokens,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    Token elementNameToken = tokens[pos];
    ErrorStatus errorStatus = ErrorStatus::OK;
    pos++;
    auto declaredIter = declarations.find(elementNameToken.getValue());
    std::shared_ptr<EntityArgument> element;
    if (declaredIter == declarations.end()) {
        errorStatus = ErrorStatus::SEMANTIC;
        element = dummyElement;
    } else {
        element = declaredIter->second;
    }

    if (pos >= tokens.size() || !isDot(tokens[pos])) {
        canBeSynonym();
        return {element, pos, errorStatus};
    }
    cannotBeAttrRef();
    pos += consumeDot(tokens[pos]);
    std::string attrRef = findAttrRef(tokens, pos);
    pos = attrRef == EntityCreator::STMT_ATTR ? pos + 2 : pos + 1;
    if (element->getType() == DummyArgument::DUMMY) {
        return {dummyElement, pos, errorStatus};
    }
    std::shared_ptr<EntityCreator> creator =
        CreatorMap::entityCreators.find(element->getType())->second;
    std::shared_ptr<EntityArgument> elemAttrRef;
    try {
        elemAttrRef = creator->create(element->getValue(), attrRef);
    } catch (ParserError pe) {
        elemAttrRef = std::make_shared<DummyArgument>();
        errorStatus = pe.status();
    }
    return {elemAttrRef, pos, errorStatus};
}
