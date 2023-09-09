#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/IStmtGetter.h"



class StubStmtGetter : public IStmtGetter
{
private:
    std::unordered_set<int> assignStmtsEntries;
    std::unordered_set<int> whileStmtsEntries;
    std::unordered_set<int> ifStmtsEntries;

    std::unordered_map<int, std::string> callProcsEntries;
    std::unordered_map<int, std::string> printVarsEntries;
    std::unordered_map<int, std::string> readVarsEntries;

public:
    void setAssignStmtEntries(std::unordered_set<int>& assignStmtsEntries) {
        this->assignStmtsEntries = assignStmtsEntries;
    }

    void setWhileStmtEntries(std::unordered_set<int>& whileStmtsEntries) {
        this->whileStmtsEntries = whileStmtsEntries;
    }

    void setIfStmtEntries(std::unordered_set<int>& ifStmtsEntries) {
        this->ifStmtsEntries = ifStmtsEntries;
    }

    void setCallStmtEntries(std::unordered_map<int, std::string>& callProcsEntries) {
        this->callProcsEntries = callProcsEntries;
    }

    void setPrintStmtEntries(std::unordered_map<int, std::string>& printVarsEntries) {
        this->printVarsEntries = printVarsEntries;
    }

    void setReadStmtEntries(std::unordered_map<int, std::string>& readVarsEntries) {
        this->readVarsEntries = readVarsEntries;
    }

    virtual std::unordered_set<int> getAllStmts() override 
    { 
        std::unordered_set<int> result;

        CollectionUtils::merge(result, assignStmtsEntries);
        CollectionUtils::merge(result, whileStmtsEntries);
        CollectionUtils::merge(result, ifStmtsEntries);
        CollectionUtils::collapseKey(callProcsEntries, result);
        CollectionUtils::collapseKey(printVarsEntries, result);
        CollectionUtils::collapseKey(readVarsEntries, result);

        return result;
    }

    virtual std::unordered_set<int> getAssignStmts() override { return this->assignStmtsEntries; }
    virtual std::unordered_set<int> getWhileStmts() override { return this->whileStmtsEntries; }
    virtual std::unordered_set<int> getIfStmts() override { return this->ifStmtsEntries; }


    virtual std::unordered_set<int> getCallStmts() override
    {
        std::unordered_set<int> result;
        CollectionUtils::collapseKey(callProcsEntries, result);
        return result;
    }

    virtual std::unordered_set<int> getPrintStmts() override
    {
        std::unordered_set<int> result;
        CollectionUtils::collapseKey(printVarsEntries, result);
        return result;
    }

    virtual std::unordered_set<int> getReadStmts() override
    {
        std::unordered_set<int> result;
        CollectionUtils::collapseKey(readVarsEntries, result);
        return result;
    }

    virtual bool isAssignStmt(const int& stmtNum) override { return CollectionUtils::find(assignStmtsEntries, stmtNum); }
    virtual bool isWhileStmt(const int& stmtNum) override { return CollectionUtils::find(whileStmtsEntries, stmtNum); }
    virtual bool isIfStmt(const int& stmtNum) override { return CollectionUtils::find(ifStmtsEntries, stmtNum); }
    virtual bool isCallStmt(const int& stmtNum) override { return CollectionUtils::find(callProcsEntries, stmtNum); }
    virtual bool isPrintStmt(const int& stmtNum) override { return CollectionUtils::find(printVarsEntries, stmtNum); }
    virtual bool isReadStmt(const int& stmtNum) override { return CollectionUtils::find(readVarsEntries, stmtNum); }

    virtual std::unordered_map<int, std::string> getCallProcEntries() override { return this->callProcsEntries; }
    virtual std::unordered_map<int, std::string> getPrintVarEntries() override { return this->printVarsEntries; }
    virtual std::unordered_map<int, std::string> getReadVarEntries() override { return this->readVarsEntries; }
    
    virtual std::string getCallProc(const int& stmtNum) override 
    { 
        return CollectionUtils::find(callProcsEntries, stmtNum) ? callProcsEntries[stmtNum] : "";
    }

    virtual std::string getPrintVar(const int& stmtNum) override
    {
        return CollectionUtils::find(printVarsEntries, stmtNum) ? printVarsEntries[stmtNum] : "";
    }

    virtual std::string getReadVar(const int& stmtNum) override
    {
        return CollectionUtils::find(readVarsEntries, stmtNum) ? readVarsEntries[stmtNum] : "";
    }

};