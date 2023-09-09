// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <string>
#include "WithArgsValidator.h"
#include "qps/argument/input/StringInput.h"
#include "qps/argument/input/IntInput.h"
#include "qps/argument/entity/EntityArgument.h"
#include "common/exceptions/ErrorStatus.h"
#include "common/exceptions/ParserError.h"

WithArgsValidator::WithArgsValidator() {}

bool WithArgsValidator::isName(std::shared_ptr<Argument> arg) {
    if (StringInput::checkInstance(arg.get())) {
        return true;
    }
    if (EntityArgument::checkInstance(arg.get())) {
        EntityArgument* ea = dynamic_cast<EntityArgument*>(arg.get());
        std::string attrRef = ea->getAttrRef();
        return attrRef == "varName" || attrRef == "procName";
    }
    return false;
}

bool WithArgsValidator::isNumber(std::shared_ptr<Argument> arg) {
    if (IntInput::checkInstance(arg.get())) {
        return true;
    }
    if (EntityArgument::checkInstance(arg.get())) {
        EntityArgument* ea = dynamic_cast<EntityArgument*>(arg.get());
        std::string attrRef = ea->getAttrRef();
        return attrRef == "value" || attrRef == "stmt#";
    }
    return false;
}

ErrorStatus WithArgsValidator::validate(std::shared_ptr<Argument> firstArg,
    std::shared_ptr<Argument> secondArg) {
    bool bothNumber = isNumber(firstArg) && isNumber(secondArg);
    bool bothName = isName(firstArg) && isName(secondArg);
    if (!bothName && !bothNumber) {
        return ErrorStatus::SEMANTIC;
    }
    return ErrorStatus::OK;
}
