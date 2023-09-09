// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <fstream>

#include "FileReader.h"

std::string FileReader::readFile(std::string path) {
    std::string output;
    std::ifstream inputFile;

    // opening new file
    inputFile.open(path, std::ios::in);

    if (inputFile.is_open()) {
        while (inputFile) {
            std::string temp;
            getline(inputFile, temp);
            output += temp + " ";
        }
        inputFile.close();
        return output;
    }
    throw  std::runtime_error("Cannot open file: " + path);
}
