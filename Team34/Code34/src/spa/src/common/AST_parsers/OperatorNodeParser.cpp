// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "OperatorNodeParser.h"

OperatorNodeParser::OperatorNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

void OperatorNodeParser::addVariableNodeParser(std::shared_ptr<VariableNodeParser> parser) {
    variableNodeParser = parser;
}

void OperatorNodeParser::addConstantNodeParser(std::shared_ptr<ConstantNodeParser> parser) {
    constantNodeParser = parser;
}

std::string OperatorNodeParser::checkType(ExpressionNode* node) {
    std::string output = "";

    if (dynamic_cast<VariableNode*>(node) != nullptr) {
        output = variableNodeParser->parse(dynamic_cast<VariableNode*>(node));
    } else if (dynamic_cast<ConstantNode*>(node) != nullptr) {
        output = constantNodeParser->parse(dynamic_cast<ConstantNode*>(node));
    } else if (dynamic_cast<OperatorNode*>(node) != nullptr) {
        output = parse(dynamic_cast<OperatorNode*>(node));
    } else {}

    return output;
}

std::string OperatorNodeParser::parse(OperatorNode* node) {
    std::string curr = "operatorNode" + std::to_string(count);
    count++;
    std::string op = node->getValue();
    std::string lhs = checkType(node->getNeighbor(0));
    std::string rhs = "";
    if (node->getNeighborCount() > 1) {
        rhs = checkType(node->getNeighbor(1));
    }


    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);
    outputFile << "std::shared_ptr<OperatorNode> " + curr
        + " = std::make_shared<OperatorNode>(\"" + op + "\");";
    outputFile << std::endl;
    outputFile << curr + "->addLHS(" + lhs + ");";
    outputFile << std::endl;

    if (!rhs.empty()) {
        outputFile << curr + "->addRHS(" + rhs + ");";
        outputFile << std::endl;
    }

    outputFile.close();

    return curr;
}
