#include "catch.hpp"
#include "pkb/base/BasePairMap.h"
#include "sp/node/AssignNode.h"




TEST_CASE("PKB: BasePairMap") {
    SECTION("Test basic adding") {
        BasePairMap<int, std::string, std::shared_ptr<EntityNode>> testMap;
        std::shared_ptr<AssignNode> ptr1 = std::make_shared<AssignNode>(1);
        std::shared_ptr<AssignNode> ptr2 = std::make_shared<AssignNode>(2);
        std::shared_ptr<AssignNode> ptr3 = std::make_shared<AssignNode>(3);
        testMap.addEntry(1, {"value1", ptr1});
        testMap.addEntry(2, {"value2", ptr2});
        testMap.addEntry(3, "value3", ptr3);

        REQUIRE(testMap.getValByKey(1).first == "value1");
        REQUIRE(testMap.getValByKey(1).second == ptr1);
        REQUIRE(testMap.getValByKey(2).first == "value2");
        REQUIRE(testMap.getValByKey(2).second == ptr2);
        REQUIRE(testMap.getValByKey(3).first == "value3");
        REQUIRE(testMap.getValByKey(3).second == ptr3);
    };
    SECTION("Test get size") {
        BasePairMap<int, std::string, std::shared_ptr<EntityNode>> testMap;
        std::shared_ptr<AssignNode> ptr1 = std::make_shared<AssignNode>(1);
        std::shared_ptr<AssignNode> ptr2 = std::make_shared<AssignNode>(2);
        std::shared_ptr<AssignNode> ptr3 = std::make_shared<AssignNode>(3);
        testMap.addEntry(1, {"value1", ptr1});
        testMap.addEntry(2, {"value2", ptr2});
        testMap.addEntry(3, "value3", ptr3);

        REQUIRE(testMap.getSize() == 3);
    };
    SECTION("Test adding duplicate entries with same key") {
        BasePairMap<int, std::string, std::shared_ptr<EntityNode>> testMap;
        std::shared_ptr<AssignNode> ptr1 = std::make_shared<AssignNode>(1);
        std::shared_ptr<AssignNode> ptr2 = std::make_shared<AssignNode>(2);
        std::shared_ptr<AssignNode> ptr3 = std::make_shared<AssignNode>(3);
        std::shared_ptr<AssignNode> ptr4 = std::make_shared<AssignNode>(4);
        testMap.addEntry(1, {"value1", ptr1});
        testMap.addEntry(2, {"value2", ptr2});
        testMap.addEntry(3, "value3", ptr3);
        testMap.addEntry(1, {"value4", ptr4});

        REQUIRE(testMap.getSize() == 3);
        REQUIRE(testMap.getValByKey(1).first == "value1");
        REQUIRE(testMap.getValByKey(1).second.get() == ptr1.get());
    };
    SECTION("Test contain key") {
        BasePairMap<int, std::string, std::shared_ptr<EntityNode>> testMap;
        testMap.addEntry(1, {"value1", std::make_shared<AssignNode>(1)});


        REQUIRE(testMap.containKey(1) == true);
        REQUIRE(testMap.containKey(2) == false);
    }
}
