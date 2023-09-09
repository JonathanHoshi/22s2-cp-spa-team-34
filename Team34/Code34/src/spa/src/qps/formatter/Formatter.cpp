// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "Formatter.h"

std::string Formatter::collapseString(std::vector<std::string>& entryList, std::string delimiter) {
    std::string result;

    for (int i = 0; i < entryList.size(); i++) {
        result += entryList[i];

        if (i >= entryList.size() - 1) {
            break;
        }

        result += delimiter;
    }
    return result;
}

void Formatter::formatAttrSelection(std::vector<std::shared_ptr<EntityArgument>>& selectionList,
    std::vector<std::string>& entryList) {
    for (int i = 0; i < selectionList.size(); i++) {
        entryList[i] = selectionList[i]->getAttrFromPKB(entryList[i]);
    }
}

std::vector<std::string> Formatter::getSelectionEntryList(int index,
    std::vector<std::shared_ptr<EntityArgument>>& selectionList,
    std::unordered_map<std::string, std::vector<std::string>>& resultTable) {
    std::vector<std::string> entryList;

    for (auto& selection : selectionList) {
        entryList.push_back(resultTable.at(selection->getValue())[index]);
    }

    return entryList;
}

std::list<std::string> Formatter::formatSelection(
    std::vector<std::shared_ptr<EntityArgument>>& selectionList,
    std::unordered_map<std::string, std::vector<std::string>>& resultTable) {
    int resultTableSize = resultTable.begin()->second.size();
    std::unordered_set<std::string> result;

    for (int i = 0; i < resultTableSize; i++) {
        std::vector<std::string> entryList = getSelectionEntryList(i, selectionList, resultTable);
        formatAttrSelection(selectionList, entryList);
        result.emplace(collapseString(entryList, this->delimeter));
    }

    std::list resultList(result.begin(), result.end());

    return resultList;
}

std::list<std::string> Formatter::formatResult(AbstractQuery& query) {
    if (query.getQueryStatus() == ErrorStatus::SYNTAX) {
        return {SYNTAX_ERROR_MSG};
    } else if (query.getQueryStatus() == ErrorStatus::SEMANTIC) {
        return {SEMENTIC_ERROR_MSG};
    }

    QueryResult* otherResult = query.getResult();
    std::list<std::string> output;

    if (query.getSelectBoolean()) {
        std::string boolStatus = query.isClauseEmpty() || otherResult->isClauseSuccess()
            ? SELECT_BOOL_TRUE_MSG : SELECT_BOOL_FALSE_MSG;

        return {boolStatus};
    }

    if (otherResult->isClauseSuccess()) {
        std::unordered_map<std::string, std::vector<std::string>> resultTable =
            otherResult->getResultMap();
        std::vector<std::shared_ptr<EntityArgument>> selectionList = query.getSelectionList();
        output = formatSelection(selectionList, resultTable);

        output.sort();
    }

    return output;
}
