#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "pkb/interfaces/IStmtAdder.h"



class StubStmtAdder : public IStmtAdder {

private:
	std::unordered_map<int, std::string> readLst;
	std::unordered_map<int, std::string> printLst;
	std::unordered_map<int, std::string> callLst;
	std::unordered_set<int> assignLst;
	std::unordered_set<int> whileLst;
	std::unordered_set<int> ifLst;

public:
	void addReadStmt(const int& stmtNum, const std::string& varName) override {
		readLst.insert({ stmtNum, varName });
	}

	virtual void addPrintStmt(const int& stmtNum, const std::string& varName) override {
		printLst.insert({ stmtNum, varName });
	}

	virtual void addAssignStmt(const int& stmtNum) override {
		assignLst.insert(stmtNum);
	}

	virtual void addCallStmt(const int& stmtNum, const std::string& procName) override {
		callLst.insert({ stmtNum, procName });
	}
	virtual void addWhileStmt(const int& stmtNum) override {
		whileLst.insert(stmtNum);
	}

	virtual void addIfStmt(const int& stmtNum) override {
		ifLst.insert(stmtNum);
	}

	void addReadStmts(const std::unordered_map<int, std::string>& stmtSet) override {
		for (const auto& [stmt, var] : stmtSet) {
			addReadStmt(stmt, var);
		}
	}

	void addPrintStmts(const std::unordered_map<int, std::string>& stmtSet) override {
		for (const auto& [stmt, var] : stmtSet) {
			addPrintStmt(stmt, var);
		}
	}

	void addAssignStmts(const std::unordered_set<int>& stmtSet) override {
		for (const auto& stmt : stmtSet) {
			addAssignStmt(stmt);
		}
	}

	void addCallStmts(const std::unordered_map<int, std::string>& stmtSet) override {
		for (const auto& [stmt, var] : stmtSet) {
			addCallStmt(stmt, var);
		}
	}

	void addWhileStmts(const std::unordered_set<int>& stmtSet) override {
		for (const auto& stmt : stmtSet) {
			addWhileStmt(stmt);
		}
	}

	void addIfStmts(const std::unordered_set<int>& stmtSet) override {
		for (const auto& stmt : stmtSet) {
			addIfStmt(stmt);
		}
	}

	int getReadCount() {
		return readLst.size();
	}

	int getPrintCount() {
		return printLst.size();
	}

	int getCallCount() {
		return callLst.size();
	}

	int getAssignCount() {
		return assignLst.size();
	}

	int getIfCount() {
		return ifLst.size();
	}

	int getWhileCount() {
		return whileLst.size();
	}
};