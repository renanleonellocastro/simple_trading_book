#include <thread>
#include <algorithm>

#include "OrderCacheImpTest.h"

void OrderCacheImpTest::testAddOrder()
{
    OrderCacheImp orderCache;

    orderCache.addOrder(Order("Order1", "secId1", "Buy", 10, "user1", "company1"));
    orderCache.addOrder(Order("Order2", "secId1", "Sell", 5, "user2", "company2"));


    assert(orderCache.getAllOrders().size() == 2);
    assert(orderCache.getMatchingSizeForSecurity("secId1") == 5);

    std::cout << "testAddOrder: passed" << std::endl;
}

void OrderCacheImpTest::testCancelOrder()
{
    OrderCacheImp orderCache;

    orderCache.addOrder(Order("Order1", "secId1", "Buy", 10, "user1", "company1"));
    orderCache.addOrder(Order("Order2", "secId1", "Sell", 5, "user2", "company2"));


    orderCache.cancelOrder("Order1");

    assert(orderCache.getAllOrders().size() == 1);
    assert(orderCache.getMatchingSizeForSecurity("secId1") == 0);

    std::cout << "testCancelOrder: passed" << std::endl;
}

void OrderCacheImpTest::testCancelOrdersForUser()
{
    OrderCacheImp orderCache;

    orderCache.addOrder(Order("Order1", "secId1", "Buy", 10, "user1", "company1"));
    orderCache.addOrder(Order("Order2", "secId1", "Sell", 5, "user1", "company2"));
    orderCache.addOrder(Order("Order3", "secId2", "Buy", 10, "user2", "company3"));

    orderCache.cancelOrdersForUser("user1");

    assert(orderCache.getAllOrders().size() == 1);
    assert(orderCache.getMatchingSizeForSecurity("secId2") == 0);

    std::cout << "testCancelOrdersForUser: passed" << std::endl;
}

void OrderCacheImpTest::testCancelOrdersForSecIdWithMinimumQty()
{
    OrderCacheImp orderCache;

    orderCache.addOrder(Order("Order1", "secId1", "Buy", 10, "user1", "company1"));
    orderCache.addOrder(Order("Order2", "secId1", "Buy", 5, "user2", "company2"));
    orderCache.addOrder(Order("Order3", "secId1", "Buy", 20, "user3", "company3"));

    orderCache.cancelOrdersForSecIdWithMinimumQty("secId1", 10);

    assert(orderCache.getAllOrders().size() == 1);
    assert(orderCache.getMatchingSizeForSecurity("secId1") == 0);

    std::cout << "testCancelOrdersForSecIdWith: passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurity()
{
    OrderCacheImp orderCache;

    orderCache.addOrder(Order("Order1", "secId1", "Buy", 10, "user1", "company1"));
    orderCache.addOrder(Order("Order2", "secId1", "Sell", 5, "user2", "company2"));
    orderCache.addOrder(Order("Order3", "secId2", "Buy", 20, "user3", "company3"));
    orderCache.addOrder(Order("Order4", "secId2", "Sell", 15, "user4", "company4"));

    assert(orderCache.getMatchingSizeForSecurity("secId1") == 5);
    assert(orderCache.getMatchingSizeForSecurity("secId2") == 15);

    std::cout << "testGetMatchingSizeForSecurity: passed" << std::endl;
}

void OrderCacheImpTest::testGetAllOrders()
{
    OrderCacheImp orderCache;
    orderCache.addOrder(Order("Order1", "secId1", "Buy", 10, "user1", "company1"));
    orderCache.addOrder(Order("Order2", "secId1", "Sell", 5, "user2", "company2"));
    orderCache.addOrder(Order("Order3", "secId2", "Buy", 20, "user3", "company3"));

    assert(orderCache.getAllOrders().size() == 3);

    std::cout << "testGetAllOrders: passed" << std::endl;
}

void OrderCacheImpTest::testMultiThreadScenario()
{
    OrderCacheImp orderCache;
    std::thread thread1(OrderCacheImpTest::thread1Function, std::ref(orderCache));
    std::thread thread2(OrderCacheImpTest::thread2Function, std::ref(orderCache));
    std::thread thread3(OrderCacheImpTest::thread3Function, std::ref(orderCache));

    thread1.join();
    thread2.join();
    thread3.join();

    assert(orderCache.getAllOrders().size() == 6);
    assert(orderCache.getMatchingSizeForSecurity("secId1") == 300);

    std::cout << "testMultiThreadScenario: passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample1()
{
    OrderCacheImp orderCache;
    orderCache.addOrder(Order("OrdId1", "SecId1", "Buy", 10000, "User1", "Company1"));
    orderCache.addOrder(Order("OrdId2", "SecId1", "Sell", 2000, "User2", "Company2"));
    orderCache.addOrder(Order("OrdId3", "SecId1", "Sell", 1000, "User3", "Company3"));

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 3000);

    std::cout << "testGetMatchingSizeForSecurityExample1: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample2()
{
    OrderCacheImp orderCache;
    orderCache.addOrder(Order("OrdId1", "SecId1", "Sell", 100, "User10", "Company2"));
    orderCache.addOrder(Order("OrdId3", "SecId1", "Buy", 300, "User13", "Company2"));
    orderCache.addOrder(Order("OrdId7", "SecId1", "Sell", 700, "User10", "Company2"));
    orderCache.addOrder(Order("OrdId8", "SecId1", "Sell", 800, "User2", "Company1"));
    orderCache.addOrder(Order("OrdId13", "SecId1", "Sell", 1300, "User1", "Company3"));

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 300);

    std::cout << "testGetMatchingSizeForSecurityExample2: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample3()
{
    OrderCacheImp orderCache;
    orderCache.addOrder(Order("OrdId4", "SecId2", "Sell", 400, "User12", "Company2"));
    orderCache.addOrder(Order("OrdId9", "SecId2", "Buy", 900, "User6", "Company2"));
    orderCache.addOrder(Order("OrdId10", "SecId2", "Sell", 1000, "User5", "Company1"));
    orderCache.addOrder(Order("OrdId11", "SecId2", "Sell", 1100, "User6", "Company2"));

    assert(orderCache.getMatchingSizeForSecurity("SecId2") == 900);

    std::cout << "testGetMatchingSizeForSecurityExample3: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample4()
{
    OrderCacheImp orderCache;
    orderCache.addOrder(Order("OrdId2", "SecId3", "Sell", 200, "User8", "Company2"));
    orderCache.addOrder(Order("OrdId5", "SecId3", "Sell", 500, "User7", "Company2"));
    orderCache.addOrder(Order("OrdId6", "SecId3", "Buy", 600, "User3", "Company1"));
    orderCache.addOrder(Order("OrdId12", "SecId3", "Buy", 1200, "User9", "Company2"));

    assert(orderCache.getMatchingSizeForSecurity("SecId3") == 600);

    std::cout << "testGetMatchingSizeForSecurityExample4: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample5()
{
    OrderCacheImp orderCache;
    orderCache.addOrder(Order("OrdId1", "SecId1", "Buy", 1000, "User1", "CompanyA"));
    orderCache.addOrder(Order("OrdId2", "SecId2", "Sell", 3000, "User2", "CompanyB"));
    orderCache.addOrder(Order("OrdId3", "SecId1", "Sell", 500, "User3", "CompanyA"));
    orderCache.addOrder(Order("OrdId4", "SecId2", "Buy", 600, "User4", "CompanyC"));
    orderCache.addOrder(Order("OrdId5", "SecId2", "Buy", 100, "User5", "CompanyB"));
    orderCache.addOrder(Order("OrdId6", "SecId3", "Buy", 1000, "User6", "CompanyD"));
    orderCache.addOrder(Order("OrdId7", "SecId2", "Buy", 2000, "User7", "CompanyE"));
    orderCache.addOrder(Order("OrdId8", "SecId2", "Sell", 5000, "User8", "CompanyE"));

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 0);
    assert(orderCache.getMatchingSizeForSecurity("SecId2") == 2700);
    assert(orderCache.getMatchingSizeForSecurity("SecId3") == 0);

    std::cout << "testGetMatchingSizeForSecurityExample5: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample6()
{
    OrderCacheImp orderCache;
    orderCache.addOrder(Order("OrdId1", "SecId1", "Sell", 100, "User10", "Company2"));
    orderCache.addOrder(Order("OrdId2", "SecId3", "Sell", 200, "User8", "Company2"));
    orderCache.addOrder(Order("OrdId3", "SecId1", "Buy", 300, "User13", "Company2"));
    orderCache.addOrder(Order("OrdId4", "SecId2", "Sell", 400, "User12", "Company2"));
    orderCache.addOrder(Order("OrdId5", "SecId3", "Sell", 500, "User7", "Company2"));
    orderCache.addOrder(Order("OrdId6", "SecId3", "Buy", 600, "User3", "Company1"));
    orderCache.addOrder(Order("OrdId7", "SecId1", "Sell", 700, "User10", "Company2"));
    orderCache.addOrder(Order("OrdId8", "SecId1", "Sell", 800, "User2", "Company1"));
    orderCache.addOrder(Order("OrdId9", "SecId2", "Buy", 900, "User6", "Company2"));
    orderCache.addOrder(Order("OrdId10", "SecId2", "Sell", 1000, "User5", "Company1"));
    orderCache.addOrder(Order("OrdId11", "SecId1", "Sell", 1100, "User13", "Company2"));
    orderCache.addOrder(Order("OrdId12", "SecId2", "Buy", 1200, "User9", "Company2"));
    orderCache.addOrder(Order("OrdId13", "SecId1", "Sell", 1300, "User1", "Company"));

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 300);
    assert(orderCache.getMatchingSizeForSecurity("SecId2") == 1000);
    assert(orderCache.getMatchingSizeForSecurity("SecId3") == 600);

    std::cout << "testGetMatchingSizeForSecurityExample6: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample7()
{
    OrderCacheImp orderCache;
    orderCache.addOrder(Order("OrdId1", "SecId3", "Sell", 100, "User1", "Company1"));
    orderCache.addOrder(Order("OrdId2", "SecId3", "Sell", 200, "User3", "Company2"));
    orderCache.addOrder(Order("OrdId3", "SecId1", "Buy", 300, "User2", "Company1"));
    orderCache.addOrder(Order("OrdId4", "SecId3", "Sell", 400, "User5", "Company2"));
    orderCache.addOrder(Order("OrdId5", "SecId2", "Sell", 500, "User2", "Company1"));
    orderCache.addOrder(Order("OrdId6", "SecId2", "Buy", 600, "User3", "Company2"));
    orderCache.addOrder(Order("OrdId7", "SecId2", "Sell", 700, "User1", "Company1"));
    orderCache.addOrder(Order("OrdId8", "SecId1", "Sell", 800, "User2", "Company1"));
    orderCache.addOrder(Order("OrdId9", "SecId1", "Buy", 900, "User5", "Company2"));
    orderCache.addOrder(Order("OrdId10", "SecId1", "Sell", 1000, "User1", "Company1"));
    orderCache.addOrder(Order("OrdId11", "SecId2", "Sell", 1100, "User6", "Company2"));

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 900);
    assert(orderCache.getMatchingSizeForSecurity("SecId2") == 600);
    assert(orderCache.getMatchingSizeForSecurity("SecId3") == 0);

    std::cout << "testGetMatchingSizeForSecurityExample7: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample8()
{
    OrderCacheImp orderCache;

    for (int i = 1; i <= 50000; ++i) {
        orderCache.addOrder(Order("OrdIdBuy" + std::to_string(i), "SecId1", "Buy", i, "User1",
            "Company" + std::to_string(i)));
        orderCache.addOrder(Order("OrdIdSell" + std::to_string(i), "SecId1", "Sell", i, "User1",
            "Company" + std::to_string(i)));
    }

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 1250025000);

    std::cout << "testGetMatchingSizeForSecurityExample8: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample9()
{
    OrderCacheImp orderCache;

    for (int i = 1; i <= 100000; ++i) {
        orderCache.addOrder(Order("OrdIdBuy" + std::to_string(i), "SecId1", "Buy", 1, "User1",
            "Company" + std::to_string(i)));
        orderCache.addOrder(Order("OrdIdSell" + std::to_string(i), "SecId1", "Sell", 1, "User1",
            "Company" + std::to_string(i)));
    }

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 100000);

    std::cout << "testGetMatchingSizeForSecurityExample9: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample10()
{
    OrderCacheImp orderCache;

    for (int i = 1; i <= 10000; ++i) {
        orderCache.addOrder(Order("OrdIdBuy" + std::to_string(i), "SecId1", "Buy", i, "User1",
            "Company" + std::to_string(i)));
        orderCache.addOrder(Order("OrdIdSell" + std::to_string(i), "SecId1", "Sell", i, "User1",
            "Company" + std::to_string(i)));
    }

    try {
        orderCache.addOrder(Order("OrdIdBuy5000", "SecId2", "Buy", 51, "User124712847",
            "Company12491289"));
    } catch (const std::runtime_error& error) {
        assert(std::string(error.what()) == "Order with orderId: OrdIdBuy5000 already exists in the book.");
    }

    orderCache.addOrder(Order("OrdIdBuy10001", "SecId1", "Buy", 50000, "User1",
        "Company1"));

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 50005000);

    std::cout << "testGetMatchingSizeForSecurityExample10: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample11()
{
    OrderCacheImp orderCache;

    for (int i = 1; i <= 10000; ++i) {
        orderCache.addOrder(Order("OrdIdBuy" + std::to_string(i), "SecId1", "Buy", i, "User1",
            "Company" + std::to_string(i)));
        orderCache.addOrder(Order("OrdIdSell" + std::to_string(i), "SecId1", "Sell", i, "User1",
            "Company" + std::to_string(i)));
    }

    orderCache.cancelOrdersForSecIdWithMinimumQty("SecId1", 5001);

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 12502500);

    std::cout << "testGetMatchingSizeForSecurityExample11: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample12()
{
    OrderCacheImp orderCache;

    for (int i = 1; i <= 10000; ++i) {
        orderCache.addOrder(Order("OrdIdBuy" + std::to_string(i), "SecId1", "Buy", i, "User1",
            "Company" + std::to_string(i)));
        orderCache.addOrder(Order("OrdIdSell" + std::to_string(i), "SecId1", "Sell", i, "User1",
            "Company" + std::to_string(i)));
    }

    for (int i = 1; i < 5000; ++i) {
        orderCache.cancelOrder("OrdIdBuy" + std::to_string(i));
    }

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 37507500);

    std::cout << "testGetMatchingSizeForSecurityExample12: Passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurityExample13()
{
    OrderCacheImp orderCache;

    for (int i = 1; i <= 10000; ++i) {
        orderCache.addOrder(Order("OrdIdBuy" + std::to_string(i), "SecId1", "Buy", i, "User1",
            "Company" + std::to_string(i)));
        orderCache.addOrder(Order("OrdIdSell" + std::to_string(i), "SecId1", "Sell", i, "User2",
            "Company" + std::to_string(i)));
    }

    orderCache.cancelOrdersForUser("User1");

    assert(orderCache.getMatchingSizeForSecurity("SecId1") == 0);

    std::cout << "testGetMatchingSizeForSecurityExample13: Passed" << std::endl;
}

void OrderCacheImpTest::thread1Function(OrderCacheImp& orderCache)
{
    orderCache.addOrder(Order("Order1", "secId1", "Buy", 100, "user1", "company1"));
    orderCache.addOrder(Order("Order2", "secId1", "Sell", 200, "user2", "company2"));
    orderCache.addOrder(Order("Order3", "secId1", "Sell", 300, "user3", "company3"));
    orderCache.addOrder(Order("Order4", "secId1", "Buy", 100, "user4", "company5"));
    orderCache.addOrder(Order("Order5", "secId1", "Sell", 200, "user4", "company5"));
    orderCache.addOrder(Order("Order6", "secId2", "Buy", 300, "user4", "company5"));
    orderCache.addOrder(Order("Order7", "secId1", "Buy", 1000, "user5", "company5"));
    orderCache.addOrder(Order("Order8", "secId1", "Sell", 2000, "user5", "company5"));
    orderCache.addOrder(Order("Order9", "secId1", "Buy", 3000, "user5", "company5"));

    orderCache.cancelOrder("Order2");
    orderCache.cancelOrdersForUser("user4");
    orderCache.cancelOrdersForSecIdWithMinimumQty("secId1", 1000);
}

void OrderCacheImpTest::thread2Function(OrderCacheImp& orderCache)
{
    orderCache.addOrder(Order("Order10", "secId1", "Buy", 100, "user1", "company10"));
    orderCache.addOrder(Order("Order11", "secId1", "Sell", 200, "user2", "company2"));
    orderCache.addOrder(Order("Order12", "secId1", "Sell", 300, "user3", "company20"));
    orderCache.addOrder(Order("Order13", "secId1", "Buy", 100, "user4", "company5"));
    orderCache.addOrder(Order("Order14", "secId1", "Sell", 200, "user4", "company5"));
    orderCache.addOrder(Order("Order15", "secId2", "Buy", 300, "user4", "company5"));
    orderCache.addOrder(Order("Order16", "secId1", "Buy", 1000, "user5", "company5"));
    orderCache.addOrder(Order("Order17", "secId1", "Sell", 2000, "user5", "company5"));
    orderCache.addOrder(Order("Order18", "secId1", "Buy", 3000, "user5", "company5"));

    orderCache.cancelOrder("Order11");
    orderCache.cancelOrdersForUser("user4");
    orderCache.cancelOrdersForSecIdWithMinimumQty("secId1", 1000);
}

void OrderCacheImpTest::thread3Function(OrderCacheImp& orderCache)
{
    orderCache.addOrder(Order("Order20", "secId1", "Buy", 100, "user1", "company30"));
    orderCache.addOrder(Order("Order21", "secId1", "Sell", 200, "user2", "company2"));
    orderCache.addOrder(Order("Order22", "secId1", "Sell", 300, "user3", "company40"));
    orderCache.addOrder(Order("Order23", "secId1", "Buy", 100, "user4", "company5"));
    orderCache.addOrder(Order("Order24", "secId1", "Sell", 200, "user4", "company5"));
    orderCache.addOrder(Order("Order25", "secId2", "Buy", 300, "user4", "company5"));
    orderCache.addOrder(Order("Order26", "secId1", "Buy", 1000, "user5", "company5"));
    orderCache.addOrder(Order("Order27", "secId1", "Sell", 2000, "user5", "company5"));
    orderCache.addOrder(Order("Order28", "secId1", "Buy", 3000, "user5", "company5"));

    orderCache.cancelOrder("Order21");
    orderCache.cancelOrdersForUser("user4");
    orderCache.cancelOrdersForSecIdWithMinimumQty("secId1", 1000);
}
