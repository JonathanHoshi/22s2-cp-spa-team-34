#include "catch.hpp"
#include "pkb/tables/AssignPatternTable.h"
#include "sp/node/VariableNode.h"



TEST_CASE("PKB: AssignPatternTable") {
    SECTION("Test addAssignPattern") {
        AssignPatternTable testTable;
        testTable.addAssignPattern(1, "value1", std::make_shared<VariableNode>("value10"));
        testTable.addAssignPattern(2, "value2", std::make_shared<VariableNode>("value20"));
        testTable.addAssignPattern(3, "value3", std::make_shared<VariableNode>("value30"));
        REQUIRE(testTable.isExisted(1));
        REQUIRE(testTable.isExisted(2));
        REQUIRE(testTable.isExisted(3));
    };

    SECTION("Test getAssignPatterns") {
        AssignPatternTable testTable;
        std::shared_ptr<VariableNode> ptr1 = std::make_shared<VariableNode>("value10");
        std::shared_ptr<VariableNode> ptr2 = std::make_shared<VariableNode>("value20");
        std::shared_ptr<VariableNode> ptr3 = std::make_shared<VariableNode>("value30");
        testTable.addAssignPattern(1, "value1", ptr1);
        testTable.addAssignPattern(2, "value2", ptr2);
        testTable.addAssignPattern(3, "value3", ptr3);
        std::unordered_map<int, std::pair<std::string, std::shared_ptr<ExpressionNode>>> expected = {
            {1, {"value1", ptr1}},
            {2, {"value2", ptr2}},
            {3, {"value3", ptr3}},
        };
        REQUIRE(testTable.getAssignPatterns() == expected);
    }

    SECTION("Test getAssignPatternByStmtNum") {
        AssignPatternTable testTable;
        std::shared_ptr<VariableNode> ptr1 = std::make_shared<VariableNode>("value10");
        std::shared_ptr<VariableNode> ptr2 = std::make_shared<VariableNode>("value20");
        std::shared_ptr<VariableNode> ptr3 = std::make_shared<VariableNode>("value30");
        testTable.addAssignPattern(1, "value1", ptr1);
        testTable.addAssignPattern(2, "value2", ptr2);
        testTable.addAssignPattern(3, "value3", ptr3);

        REQUIRE(testTable.getAssignPatternByStmtNum(1).first == "value1");
        REQUIRE(testTable.getAssignPatternByStmtNum(1).second == ptr1);
        REQUIRE(testTable.getAssignPatternByStmtNum(2).first == "value2");
        REQUIRE(testTable.getAssignPatternByStmtNum(2).second == ptr2);
        REQUIRE(testTable.getAssignPatternByStmtNum(3).first == "value3");
        REQUIRE(testTable.getAssignPatternByStmtNum(3).second == ptr3);
        REQUIRE(testTable.getAssignPatternByStmtNum(4).first == "");
        REQUIRE(testTable.getAssignPatternByStmtNum(4).second == nullptr);
    }

    SECTION("Test isExisted") {
        AssignPatternTable testTable;
        std::shared_ptr<VariableNode> ptr1 = std::make_shared<VariableNode>("value10");
        std::shared_ptr<VariableNode> ptr2 = std::make_shared<VariableNode>("value20");
        std::shared_ptr<VariableNode> ptr3 = std::make_shared<VariableNode>("value30");
        testTable.addAssignPattern(1, "value1", ptr1);
        testTable.addAssignPattern(2, "value2", ptr2);
        testTable.addAssignPattern(3, "value3", ptr3);
        REQUIRE(testTable.isExisted(1));
        REQUIRE(testTable.isExisted(2));
        REQUIRE(testTable.isExisted(3));
        REQUIRE_FALSE(testTable.isExisted(4));
    }
}

TEST_CASE("PKB: testTable") {
    SECTION("Test addAssignPattern and getAssignPattern") {
        AssignPatternTable testTable;
        const std::shared_ptr<VariableNode> ptr1 = std::make_shared<VariableNode>("1");
        const std::shared_ptr<VariableNode> ptr2 = std::make_shared<VariableNode>("2");
        const std::shared_ptr<VariableNode> ptr3 = std::make_shared<VariableNode>("3");
        testTable.addAssignPattern(1, "left1", ptr1);
        testTable.addAssignPattern(2, "left2", ptr2);
        testTable.addAssignPattern(3, "left3", ptr3);
        REQUIRE(testTable.getAssignPatternByStmtNum(1).first == "left1");
        REQUIRE(testTable.getAssignPatternByStmtNum(2).first == "left2");
        REQUIRE(testTable.getAssignPatternByStmtNum(3).first == "left3");
        REQUIRE(testTable.getAssignPatternByStmtNum(1).second.get() == ptr1.get());
        REQUIRE(testTable.getAssignPatternByStmtNum(2).second.get() == ptr2.get());
        REQUIRE(testTable.getAssignPatternByStmtNum(3).second.get() == ptr3.get());
    };
    SECTION("Test getAssignPatterns") {
        AssignPatternTable testTable;
        std::shared_ptr<VariableNode> ptr1 = std::make_shared<VariableNode>("1");
        std::shared_ptr<VariableNode> ptr2 = std::make_shared<VariableNode>("2");
        std::shared_ptr<VariableNode> ptr3 = std::make_shared<VariableNode>("3");
        testTable.addAssignPattern(1, "left1", ptr1);
        testTable.addAssignPattern(2, "left2", ptr2);
        testTable.addAssignPattern(3, "left3", ptr3);
        std::unordered_map<int, std::pair<std::string, std::shared_ptr<ExpressionNode>>> expected = {
            {1, {"left1", ptr1}},
            {2, {"left2", ptr2}},
            {3, {"left3", ptr3}}
        };
        REQUIRE(testTable.getAssignPatterns() == expected);
    };
    SECTION("Test isValidPartialPattern") {
        AssignPatternTable testTable;
        std::shared_ptr<VariableNode> ptr1 = std::make_shared<VariableNode>("1 + 10");
        std::shared_ptr<VariableNode> ptr1_partial1 = std::make_shared<VariableNode>("1");
        std::shared_ptr<VariableNode> ptr1_partial2 = std::make_shared<VariableNode>("10");
        std::shared_ptr<VariableNode> ptr1_partial3 = std::make_shared<VariableNode>("11");
        std::shared_ptr<VariableNode> ptr2 = std::make_shared<VariableNode>("2 - 20");
        std::shared_ptr<VariableNode> ptr3 = std::make_shared<VariableNode>("3 * 30");
        testTable.addAssignPattern(1, "left1", ptr1);
        testTable.addAssignPattern(2, "left2", ptr2);
        testTable.addAssignPattern(3, "left3", ptr3);
        REQUIRE(testTable.isValidPartialPattern(1, "left1", ptr1));
        REQUIRE(testTable.isValidPartialPattern(2, "left2", ptr2));
        REQUIRE(testTable.isValidPartialPattern(3, "left3", ptr3));
    }
    SECTION("Test isValidFullPattern") {
        AssignPatternTable testTable;
        std::shared_ptr<VariableNode> ptr1 = std::make_shared<VariableNode>("1 + 10");
        std::shared_ptr<VariableNode> ptr2 = std::make_shared<VariableNode>("2 - 20");
        std::shared_ptr<VariableNode> ptr3 = std::make_shared<VariableNode>("3 * 30");
        std::shared_ptr<VariableNode> ptr4 = std::make_shared<VariableNode>("1");
        std::shared_ptr<VariableNode> ptr5 = std::make_shared<VariableNode>("1 + 10");
        std::shared_ptr<VariableNode> ptr6 = std::make_shared<VariableNode>("");
        std::shared_ptr<VariableNode> ptr7 = std::make_shared<VariableNode>("_");
        std::shared_ptr<VariableNode> ptr8 = std::make_shared<VariableNode>("_3_");
        testTable.addAssignPattern(1, "left1", ptr1);
        testTable.addAssignPattern(2, "left2", ptr2);
        testTable.addAssignPattern(3, "left3", ptr3);
        REQUIRE(testTable.isValidFullPattern(1, "left1", ptr1));
        REQUIRE(testTable.isValidFullPattern(2, "left2", ptr2));
        REQUIRE(testTable.isValidFullPattern(3, "left3", ptr3));
        REQUIRE_FALSE(testTable.isValidFullPattern(1, "left2", ptr1));
        REQUIRE_FALSE(testTable.isValidFullPattern(1, "left1", ptr6));
        REQUIRE_FALSE(testTable.isValidFullPattern(1, "left1", ptr7));
    };
    SECTION("Test isValidPattern") {
        AssignPatternTable testTable;
        std::shared_ptr<VariableNode> ptr1 = std::make_shared<VariableNode>("1 + 10");
        std::shared_ptr<VariableNode> ptr2 = std::make_shared<VariableNode>("2 - 20");
        std::shared_ptr<VariableNode> ptr3 = std::make_shared<VariableNode>("3 * 30");
        testTable.addAssignPattern(1, "left1", ptr1);
        testTable.addAssignPattern(2, "left2", ptr2);
        testTable.addAssignPattern(3, "left3", ptr3);
        REQUIRE(testTable.isValidPattern(1, "left1"));
        REQUIRE(testTable.isValidPattern(2, "left2"));
        REQUIRE(testTable.isValidPattern(3, "left3"));
        REQUIRE_FALSE(testTable.isValidPattern(1, "left2"));
        REQUIRE_FALSE(testTable.isValidPattern(2, "left1"));
        REQUIRE_FALSE(testTable.isValidPattern(1, "_"));
        REQUIRE_FALSE(testTable.isValidPattern(1, ""));
    }

}
