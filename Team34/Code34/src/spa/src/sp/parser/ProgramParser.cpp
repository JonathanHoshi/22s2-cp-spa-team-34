// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <utility>
#include <stdexcept>
#include "ProgramParser.h"

ProgramParser::ProgramParser(std::vector<Token> tokens)
    : SPParser(tokens) {}

void ProgramParser::addProcedureParser(std::shared_ptr<ProcedureParser> parser) {
    procedureParser = parser;
}


std::shared_ptr<ProcedureNode> ProgramParser::consumeProcedure() {
    procedureParser->setPos(getPos());
    return procedureParser->parse();
}

std::shared_ptr<RootNode> ProgramParser::parse() {
    std::shared_ptr<ProcedureNode> procedureNode;
    std::shared_ptr<RootNode> rootNode = std::make_shared<RootNode>();

    while (currToken.getType() != "EOF") {
        if (!checkToken("IDENTITY", "procedure")) {
            throw ParserError(ErrorStatus::SYNTAX);
        }

        procedureNode = consumeProcedure();
        rootNode->addProcedure(move(procedureNode));
        setPos(procedureParser->getPos());
    }

    return rootNode;
}
