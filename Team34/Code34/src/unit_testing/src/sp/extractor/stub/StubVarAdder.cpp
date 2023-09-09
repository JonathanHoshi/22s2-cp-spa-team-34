#pragma once

#include <string>
#include <unordered_set>
#include "pkb/interfaces/IVarAdder.h"



class StubVarAdder : public IVarAdder {

private:
	std::unordered_set<std::string> varLst;

public:
	void addVar(const std::string& procStr) override {
		varLst.insert(procStr);
	}

	void addVars(const std::unordered_set<std::string>& varSet) override {
		for (const auto& variable : varSet) {
			addVar(variable);
		}
	}

	int getVarCount() {
		return varLst.size();
	}

	bool find(const std::string& procStr) {
		return varLst.find(procStr) != varLst.end();
	}
};