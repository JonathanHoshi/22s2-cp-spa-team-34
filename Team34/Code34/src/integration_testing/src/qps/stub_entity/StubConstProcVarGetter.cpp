#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/IConstGetter.h"
#include "pkb/interfaces/IProcGetter.h"
#include "pkb/interfaces/IVarGetter.h"



class StubConstProcVarGetter : public IConstGetter, public IProcGetter, public IVarGetter
{
private:
    std::unordered_set<int> constEntries;
    std::unordered_set<std::string> procEntries;
    std::unordered_set<std::string> varEntries;

public:
    void setConstEntries(std::unordered_set<int>& constEntries)
    {
        this->constEntries = constEntries;
    }

    void setProcEntries(std::unordered_set<std::string>& procEntries)
    {
        this->procEntries = procEntries;
    }

    void setVarEntries(std::unordered_set<std::string>& varEntries)
    {
        this->varEntries = varEntries;
    }

    // Const
    virtual std::unordered_set<int> getConsts() { return this->constEntries; }
    virtual bool isConst(const int& constVal) { return CollectionUtils::find(constEntries, constVal); }

    // Proc
    virtual std::unordered_set<std::string> getProcs() { return this->procEntries; }
    virtual bool isProc(const std::string& procStr) { return CollectionUtils::find(procEntries, procStr); }

    // Var
    virtual std::unordered_set<std::string> getVars() { return this->varEntries; }
    virtual bool isVar(const std::string& varStr) { return CollectionUtils::find(varEntries, varStr); }


    virtual size_t getSize() { throw "method not used"; }
};