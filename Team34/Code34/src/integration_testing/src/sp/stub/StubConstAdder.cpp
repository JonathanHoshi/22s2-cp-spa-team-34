#pragma once

#include <unordered_set>
#include <string>
#include "pkb/interfaces/IConstAdder.h"



class StubConstAdder : public IConstAdder {

private:
	std::unordered_set<int> constLst;

public:
	void addConst(const int& constant) override {
		constLst.insert(constant);
	}

	void addConsts(const std::unordered_set<int>& constSet) override {
		for (const auto& constant : constSet) {
			addConst(constant);
		}
	}

	int getConstCount() {
		return constLst.size();
	}

	bool find(const int& constant) {
		return constLst.find(constant) != constLst.end();
	}
};