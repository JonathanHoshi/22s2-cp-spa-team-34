#include "catch.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "FileReader.h"
#include "sp/SourceProcessor.h"
#include "qps/QPS.h"
#include "pkb/PKB.h"
#include "di/DI.h"

using namespace std;

inline void TEST_SOURCE_QUERY() {
    DI di;
    PKB pkb(di);

    di.getService<IUsesGetter>().getStmtVarEntries();
    di.getService<IUsesGetter>().getProcVarEntries();

    REQUIRE(1 == 1);
}

TEST_CASE("SP and PKB Integration Test") {
    SourceProcessor sp;
    string filePath = filesystem::current_path().parent_path().string()
        + "/integration_testing/tests";

    SECTION("Follows and Follows*") {
        DI di;
        PKB pkb(di);
        string fileContents = FileReader::readFile(filePath + "/Follows_spa_source.txt");
        sp.parse(fileContents, di);

        unordered_map<int, int> expectedFollows = {
            {24, 28}, {22, 24}, {30, 34},
            {37, 38}, {21, 41}, {34, 37},
            {20, 21}, {9, 10}, {8, 9},
            {12, 13}, {11, 12}, {15, 16},
            {14, 15}, {7, 14}, {6, 7},
            {5, 6}, {18, 19}, {17, 18},
            {4, 17}, {3, 4}, {2, 3},
            {1, 2}
        };
        unordered_map<int, unordered_set<int>> expectedFollowsT = {
            {24, {28}}, {22, {28, 24}}, {30, {38, 37, 34}},
            {37, {38}}, {21, {41}}, {34, {38, 37}}, {20, {41, 21}},
            {9, {10}}, {8, {10, 9}}, {12, {13}}, {11, {13, 12}},
            {15, {16}}, {14, {16, 15}}, {7, {16, 15, 14}},
            {6, {16, 7, 15, 14}}, {5, {16, 7, 15, 6, 14}}, {18, {19}},
            {17, {19, 18}}, {4, {19, 18, 17}}, {3, {19, 18, 17, 4}},
            {2, {3, 19, 18, 17, 4}}, {1, {3, 19, 2, 18, 17, 4}}
        };

        auto follows = di.getService<IFollowsGetter>().getFollowsEntries();
        auto followsT = di.getService<IFollowsGetter>().getTEntries();
        REQUIRE(expectedFollows == follows);
        REQUIRE(expectedFollowsT == followsT);
    }
    SECTION("Calls and Calls*") {
        DI di;
        PKB pkb(di);
        string fileContents = FileReader::readFile(filePath + "/Calls_spa_source.txt");
        sp.parse(fileContents, di);

        unordered_map<string, unordered_set<string>> expectedCalls = {
            {"p3", {"p6"}}, {"p2", {"p5"}}, {"p1", {"p4", "p3", "p2"}}
        };
        unordered_map<string, unordered_set<string>> expectedCallsT = {
            {"p3", {"p6"}}, {"p2", {"p5"}}, {"p1", {"p6", "p5", "p4", "p3", "p2"}}
        };

        auto calls = di.getService<ICallsGetter>().getCallsEntries();
        auto callsT = di.getService<ICallsGetter>().getCallsTEntries();
        REQUIRE(expectedCalls == calls);
        REQUIRE(expectedCallsT == callsT);
    }
    SECTION("Uses") {
        DI di;
        PKB pkb(di);
        string fileContents = FileReader::readFile(filePath + "/Uses_spa_source.txt");
        sp.parse(fileContents, di);

        unordered_map<string, unordered_set<string>> expectedUsesProc = {
            {"Banana", {"x", "w", "y"}}, {"Potato", {"y", "w"}},
            {"Ditto", {"x", "y"}}
        };
        unordered_map<int, unordered_set<string>> expectedUsesStmt = {
            {10, {"y"}}, {11, {"y"}}, {3, {"x", "w"}}, {5, {"w"}},
            {8, {"y"}}, {7, {"y"}}, {6, {"y"}}, {4, {"y", "w"}},
            {13, {"w"}}, {12, {"w"}}, {15, {"x"}}, {17, {"y"}},
            {16, {"y"}}, {19, {"y"}}, {20, {"y"}}, {18, {"y"}}
        };

        auto usesProc = di.getService<IUsesGetter>().getProcVarEntries();
        auto usesStmt = di.getService<IUsesGetter>().getStmtVarEntries();

        REQUIRE(expectedUsesProc == usesProc);
        REQUIRE(expectedUsesStmt == usesStmt);
    }
    SECTION("UsesP") {
        DI di;
        PKB pkb(di);
        string fileContents = FileReader::readFile(filePath + "/UsesP_spa_source.txt");
        sp.parse(fileContents, di);

        unordered_map<string, unordered_set<string>> expectedUsesProc = {
            {"p5", {"a"}}, {"p4", {"o", "n", "r", "q", "a", "s"}},
            {"p3", {"l", "k", "m", "o", "n", "r", "a", "q", "s"}},
            {"p2", {"p5", "o", "p4", "n", "p3", "i", "j", "r", "a", "q", "s"}},
            {"p1", {"b", "c", "d", "p5", "o", "p4", "n", "p3", "i", "j", "r",
            "a", "q", "s", "e", "h", "g", "l", "k", "m"}}
        };
        unordered_map<int, unordered_set<string>> expectedUsesStmt = {
            {24, {"a"}}, {16, {"l", "k"}}, {20, {"r", "q"}}, {19, {"o", "n", "r", "q"}},
            {21, {"s"}}, {23, {"a"}}, {17, {"m", "l"}}, {18, {"o", "n", "r", "a", "q", "s"}},
            {12, {"i"}}, {13, {"j"}}, {11, {"p4", "i", "p3", "j"}}, {10, {"p5", "p4", "p3", "i", "j"}},
            {15, {"o", "n", "r", "a", "q", "s"}}, {1, {"b"}}, {4, {"d"}},
            {6, {"o", "p5", "n", "p4", "i", "p3", "r", "j", "a", "q", "s"}},
            {7, {"e"}}, {5, {"d", "o", "p5", "n", "p4", "i", "p3", "j", "r", "a", "q", "s", "e"}},
            {8, {"h", "g"}}, {9, {"l", "k", "m", "o", "n", "r", "q", "a", "s"}},
            {2, {"c", "d", "o", "p5", "n", "p4", "i", "p3", "j", "r", "a", "q", "s", "e", "h",
            "g", "l", "k", "m"}}
        };

        auto usesProc = di.getService<IUsesGetter>().getProcVarEntries();
        auto usesStmt = di.getService<IUsesGetter>().getStmtVarEntries();

        REQUIRE(expectedUsesProc == usesProc);
        REQUIRE(expectedUsesStmt == usesStmt);
    }
    SECTION("Next") {
        DI di;
        PKB pkb(di);
        string fileContents = FileReader::readFile(filePath + "/Next_spa_source.txt");
        sp.parse(fileContents, di);

        unordered_map<int, unordered_set<int>> expectedNext = {
            {1, {2}}, {2, {3}}, {3, {4, 6}}, {4, {5}}, {6, {7}},
            {5, {7}}, {7, {8, 11}}, {8, {9, 10}}, {10, {7}}, {9, {7}},
            {11, {12, 14}}, {12, {13, 11}}, {13, {12}}, {14, {15, 19}},
            {15, {16}}, {16, {17}}, {17, {18}}, {18, {17}}, {19, {20}}
        };

        auto next = di.getService<INextGetter>().getNextEntries();

        REQUIRE(expectedNext == next);
    }
    SECTION("Modifies") {
        DI di;
        PKB pkb(di);
        string fileContents = FileReader::readFile(filePath + "/Modifies_spa_source.txt");
        sp.parse(fileContents, di);

        unordered_map<string, unordered_set<string>> expectedModifiesProc = {
            {"main", {"fizz", "buzz", "fizzbuzz", "error", "x"}},
            {"fakefizzbuzz", {"fizzbuzz", "fizz", "buzz", "error"}},
            {"foo", {"y", "z", "xplusy"}}
        };

        unordered_map<int, unordered_set<string>> expectedModifiesStmt = {
            {1, {"fizz"}}, {2, {"buzz"}}, {3, {"fizzbuzz"}}, {11, {"fizz"}},
            {4, {"error"}}, {6, {"x"}}, {5, {"x"}}, {8, {"fizzbuzz"}},
            {14, {"buzz"}}, {16, {"error"}}, {13, {"buzz", "error"}},
            {10, {"fizz", "buzz", "error"}}, {7, {"fizzbuzz", "fizz", "buzz", "error"}},
            {18, {"y"}}, {19, {"z"}}, {20, {"xplusy"}}
        };

        auto modifiesProc = di.getService<IModifiesGetter>().getProcVarEntries();
        auto modifiesStmt = di.getService<IModifiesGetter>().getStmtVarEntries();

        REQUIRE(expectedModifiesProc == modifiesProc);
        REQUIRE(expectedModifiesStmt == modifiesStmt);
    }
    SECTION("ModifiesP") {
        DI di;
        PKB pkb(di);
        string fileContents = FileReader::readFile(filePath + "/ModifiesP_spa_source.txt");
        sp.parse(fileContents, di);

        unordered_map<string, unordered_set<string>> expectedModifiesProc = {
            {"p5", {"a"}}, {"p4", {"p", "q", "a"}}, {"p3", {"k", "l", "p", "a", "q"}},
            {"p2", {"i", "a", "q", "j", "k", "p"}},
            {"p1", {"a", "i", "q", "k", "c", "j", "p", "e", "f", "l"}}
        };

        unordered_map<int, unordered_set<string>> expectedModifiesStmt = {
            {24, {"a"}}, {16, {"k"}}, {20, {"p"}}, {19, {"p"}}, {22, {"q"}},
            {23, {"a"}}, {17, {"l"}}, {18, {"p", "a", "q"}}, {12, {"i"}},
            {13, {"j"}}, {11, {"i", "j"}}, {10, {"i", "j"}}, {14, {"k"}},
            {15, {"p", "a", "q"}}, {1, {"a"}}, {3, {"c"}}, {6, {"q", "a", "i", "j", "k", "p"}},
            {7, {"e"}}, {5, {"q", "a", "i", "j", "k", "p", "e"}}, {8, {"f"}},
            {9, {"k", "l", "p", "q", "a"}}, {2, {"c", "k", "q", "a", "i", "j", "p", "e", "f", "l"}}
        };

        auto modifiesProc = di.getService<IModifiesGetter>().getProcVarEntries();
        auto modifiesStmt = di.getService<IModifiesGetter>().getStmtVarEntries();

        REQUIRE(expectedModifiesProc == modifiesProc);
        REQUIRE(expectedModifiesStmt == modifiesStmt);
    }
}
