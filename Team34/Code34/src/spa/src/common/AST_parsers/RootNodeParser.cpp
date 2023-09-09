// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "RootNodeParser.h"

RootNodeParser::RootNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

void RootNodeParser::addProcedureNodeParser(std::shared_ptr<ProcedureNodeParser> parser) {
    procedureNodeParser = parser;
}

std::string RootNodeParser::parse(RootNode* node) {
    std::string curr = "rootNode" + std::to_string(count);
    count++;
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);

    outputFile << "std::shared_ptr<RootNode> " + curr
        + " = std::make_shared<RootNode>();";
    outputFile << std::endl;
    outputFile.close();

    for (int i = 0; i < node->getProcedureCount(); i++) {
        std::string procedure = procedureNodeParser->parse(node->getProcedure(i));
        outputFile.open(filePath, std::ios::app);
        outputFile << curr + "->addProcedure(" + procedure + ");";
        outputFile << std::endl;
        outputFile.close();
    }

    return curr;
}
