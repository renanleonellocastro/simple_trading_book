#include <algorithm>

#include "OrderCacheImpTest.h"

void OrderCacheImpTest::testAddOrder()
{
    OrderCacheImp orderCache;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user2", "company2");

    orderCache.addOrder(order1);
    orderCache.addOrder(order2);

    assert(orderCache.getAllOrders().size() == 2);
    assert(orderCache.getMatchingSizeForSecurity("secId1") == 5);

    std::cout << "testAddOrder: passed" << std::endl;
}

void OrderCacheImpTest::testCancelOrder()
{
    OrderCacheImp orderCache;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user2", "company2");

    orderCache.addOrder(order1);
    orderCache.addOrder(order2);

    orderCache.cancelOrder("order1");

    assert(orderCache.getAllOrders().size() == 1);
    assert(orderCache.getMatchingSizeForSecurity("secId1") == 0);

    std::cout << "testCancelOrder: passed" << std::endl;
}

void OrderCacheImpTest::testCancelOrdersForUser()
{
    OrderCacheImp orderCache;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user1", "company2");
    Order order3("order3", "secId2", "Buy", 10, "user2", "company3");

    orderCache.addOrder(order1);
    orderCache.addOrder(order2);
    orderCache.addOrder(order3);

    orderCache.cancelOrdersForUser("user1");

    assert(orderCache.getAllOrders().size() == 1);
    assert(orderCache.getMatchingSizeForSecurity("secId2") == 0);

    std::cout << "testCancelOrdersForUser: passed" << std::endl;
}

void OrderCacheImpTest::testCancelOrdersForSecIdWithMinimumQty()
{
    OrderCacheImp orderCache;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Buy", 5, "user2", "company2");
    Order order3("order3", "secId1", "Buy", 20, "user3", "company3");

    orderCache.addOrder(order1);
    orderCache.addOrder(order2);
    orderCache.addOrder(order3);

    orderCache.cancelOrdersForSecIdWithMinimumQty("secId1", 10);

    assert(orderCache.getAllOrders().size() == 1);
    assert(orderCache.getMatchingSizeForSecurity("secId1") == 0);

    std::cout << "testCancelOrdersForSecIdWith: passed" << std::endl;
}

void OrderCacheImpTest::testGetMatchingSizeForSecurity()
{
    OrderCacheImp orderCache;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user2", "company2");
    Order order3("order3", "secId2", "Buy", 20, "user3", "company3");
    Order order4("order4", "secId2", "Sell", 15, "user4", "company4");

    orderCache.addOrder(order1);
    orderCache.addOrder(order2);
    orderCache.addOrder(order3);
    orderCache.addOrder(order4);

    assert(orderCache.getMatchingSizeForSecurity("secId1") == 5);
    assert(orderCache.getMatchingSizeForSecurity("secId2") == 15);

    std::cout << "testGetMatchingSizeForSecurity: passed" << std::endl;
}

void OrderCacheImpTest::testGetAllOrders()
{
    OrderCacheImp orderCache;
    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user2", "company2");
    Order order3("order3", "secId2", "Buy", 20, "user3", "company3");

    orderCache.addOrder(order1);
    orderCache.addOrder(order2);
    orderCache.addOrder(order3);

    assert(orderCache.getAllOrders().size() == 3);

    std::cout << "testGetAllOrders: passed" << std::endl;
}
