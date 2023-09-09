// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <vector>
#include <memory>
#include "SPParser.h"
#include "ProcedureParser.h"
#include "sp/node/RootNode.h"
#include "sp/node/ProcedureNode.h"

class ProgramParser : public SPParser {
private:
    std::shared_ptr<ProcedureParser> procedureParser;

public:
    explicit ProgramParser(std::vector<Token> tokens);

    std::shared_ptr<ProcedureNode> consumeProcedure();

    void addProcedureParser(std::shared_ptr<ProcedureParser> parser);

    std::shared_ptr<RootNode> parse();
};
