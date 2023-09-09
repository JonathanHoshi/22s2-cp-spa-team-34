// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ProcedureEntity.h"

void ProcedureEntity::setPKBInterface(IProcGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

ProcedureEntity::ProcedureEntity(std::string name,
    std::string attrRef) : ProcedureEntity(nullptr, name, attrRef) {}

ProcedureEntity::ProcedureEntity(IProcGetter* pkbInterface,
    std::string name, std::string attrRef) : EntityArgument(name, attrRef) {
    setPKBInterface(pkbInterface);
}

bool ProcedureEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const ProcedureEntity*>(ptr) != nullptr;
}

std::unordered_set<std::string> ProcedureEntity::getPKBValueList() {
    return pkbInterface->getProcs();
}

void ProcedureEntity::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IProcGetter>());
}

std::string ProcedureEntity::getAttrFromPKB(std::string id) {
    return id;
}

std::string ProcedureEntity::getType() {
    return TYPE_NAME;
}
