// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "VariableNodeParser.h"

VariableNodeParser::VariableNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

std::string VariableNodeParser::parse(VariableNode* node) {
    std::string curr = "variableNode" + std::to_string(count);
    count++;
    std::string name = node->getName();
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);
    outputFile << "std::shared_ptr<VariableNode> " + curr
        + " = std::make_shared<VariableNode>(\"" + name + "\");";
    outputFile << std::endl;
    outputFile.close();

    return curr;
}
