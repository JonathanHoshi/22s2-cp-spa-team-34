// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "qps/argument/Argument.h"
#include "qps/clause/Clause.h"
#include "qps/query/AbstractQuery.h"
#include "common/exceptions/ErrorStatus.h"

class Formatter {
private:
    const std::string SYNTAX_ERROR_MSG = "SyntaxError";
    const std::string SEMENTIC_ERROR_MSG = "SemanticError";
    const std::string SELECT_BOOL_TRUE_MSG = "TRUE";
    const std::string SELECT_BOOL_FALSE_MSG = "FALSE";
    const std::string delimeter = " ";

    std::string collapseString(std::vector<std::string>& entryList, std::string delimiter);
    void formatAttrSelection(std::vector<std::shared_ptr<EntityArgument>>& selectionList,
        std::vector<std::string>& entryList);
    std::vector<std::string> getSelectionEntryList(int index,
        std::vector<std::shared_ptr<EntityArgument>>& selectionList,
        std::unordered_map<std::string, std::vector<std::string>>& resultTable);
    std::list<std::string> formatSelection(
        std::vector<std::shared_ptr<EntityArgument>>& selectionList,
        std::unordered_map<std::string, std::vector<std::string>>& resultTable);

public:
    std::list<std::string> formatResult(AbstractQuery& query);
};
