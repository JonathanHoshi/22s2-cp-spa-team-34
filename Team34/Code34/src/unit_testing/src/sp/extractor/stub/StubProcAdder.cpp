#pragma once
#include <string>
#include <unordered_set>

#include "pkb/interfaces/IProcAdder.h"



class StubProcAdder : public IProcAdder {

private:
	std::unordered_set<std::string> procedureLst;

public:
	void addProc(const std::string& procStr) override {
		procedureLst.insert(procStr);
	}

	void addProcs(const std::unordered_set<std::string>& procSet) override {
		for (const auto& variable : procSet) {
			addProc(variable);
		}
	}

	int getProcedureCount() {
		return procedureLst.size();
	}

	bool find(const std::string& procStr) {
		return procedureLst.find(procStr) != procedureLst.end();
	}
};