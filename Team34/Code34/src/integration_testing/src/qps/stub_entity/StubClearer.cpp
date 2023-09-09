#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/IAffectsClearer.h"
#include "pkb/interfaces/INextTClearer.h"

class StubClearer : public IAffectsClearer, public INextTClearer
{
public:
    virtual void clearAffectsAndT() override
    {
    }
    virtual void clearNextT() override
    {
    }

};