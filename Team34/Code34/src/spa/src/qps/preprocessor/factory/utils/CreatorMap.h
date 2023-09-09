// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "qps/preprocessor/factory/entity/EntityCreator.h"
#include "qps/preprocessor/factory/entity/VariableCreator.h"
#include "qps/preprocessor/factory/entity/ProcedureCreator.h"
#include "qps/preprocessor/factory/entity/StmtCreator.h"
#include "qps/preprocessor/factory/entity/PrintCreator.h"
#include "qps/preprocessor/factory/entity/AssignCreator.h"
#include "qps/preprocessor/factory/entity/ReadCreator.h"
#include "qps/preprocessor/factory/entity/WhileCreator.h"
#include "qps/preprocessor/factory/entity/IfCreator.h"
#include "qps/preprocessor/factory/entity/ConstantCreator.h"
#include "qps/preprocessor/factory/entity/CallCreator.h"

class CreatorMap {
public:
    inline static std::unordered_map<std::string, std::shared_ptr<EntityCreator>> entityCreators =
        std::unordered_map<std::string, std::shared_ptr<EntityCreator>>(
            {{"variable", std::make_shared<VariableCreator>()},
            {"procedure", std::make_shared<ProcedureCreator>()},
            {"stmt", std::make_shared<StmtCreator>()},
            {"constant", std::make_shared<ConstantCreator>()},
            {"if", std::make_shared<IfCreator>()},
            {"while", std::make_shared<WhileCreator>()},
            {"read", std::make_shared<ReadCreator>()},
            {"assign", std::make_shared<AssignCreator>()},
            {"print", std::make_shared<PrintCreator>()},
            {"call", std::make_shared<CallCreator>()}
            });
};
