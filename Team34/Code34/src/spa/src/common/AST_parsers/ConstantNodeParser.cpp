// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "ConstantNodeParser.h"

ConstantNodeParser::ConstantNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

std::string ConstantNodeParser::parse(ConstantNode* node) {
    std::string curr = "constantNode" + std::to_string(count);
    count++;
    std::string value = std::to_string(node->getValue());
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);
    outputFile << "std::shared_ptr<ConstantNode> " + curr
        + " = std::make_shared<ConstantNode>(" + value + ");";
    outputFile << std::endl;
    outputFile.close();

    return curr;
}
