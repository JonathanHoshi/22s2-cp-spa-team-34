#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "common/CollectionUtils.h"
#include "pkb/interfaces/ICallsAdder.h"



class StubCallAdder : public ICallsAdder {
public:
	std::unordered_map<std::string, std::unordered_set<std::string>> callsMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> callsTMap;

	void addCalls(const std::string& callerProc, const std::string& calleeProc) override {
		CollectionUtils::insert(callsMap, callerProc, calleeProc);
	}
	void addCallsT(const std::string& callerProc, const std::string& calleeProc) override {
		CollectionUtils::insert(callsTMap, callerProc, calleeProc);
	}

	bool containsCall(const std::string& callerProc, const std::string& calleeProc) {
		return CollectionUtils::find(callsMap, callerProc, calleeProc);
	}

	bool containsCallT(const std::string& callerProc, const std::string& calleeProc) {
		return CollectionUtils::find(callsTMap, callerProc, calleeProc);
	}
};