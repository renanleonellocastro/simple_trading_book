#include "OrderCacheManagerTest.h"

void OrderCacheManagerTest::testAddOrder()
{
    OrderCacheManager manager;
    Order order1("order1", "sec1", "Buy", 10, "user1", "comp1");
    Order order2("order2", "sec2", "Sell", 5, "user2", "comp2");

    manager.addOrder(order1);
    manager.addOrder(order2);

    std::vector<Order> allOrders = manager.getAllOrders();

    assert(allOrders.size() == 2);
    assert(allOrders[0].orderId() == "order1" || allOrders[0].orderId() == "order2");
    assert(allOrders[1].orderId() == "order1" || allOrders[1].orderId() == "order2");

    std::cout << "testAddOrder: passed" << std::endl;
}

void OrderCacheManagerTest::testCancelOrder()
{
    OrderCacheManager manager;
    Order order1("order1", "sec1", "Buy", 10, "user1", "comp1");
    Order order2("order2", "sec2", "Sell", 5, "user2", "comp2");

    manager.addOrder(order1);
    manager.addOrder(order2);

    Order canceledOrder = manager.cancelOrder("order1");

    std::vector<Order> allOrders = manager.getAllOrders();

    assert(canceledOrder.orderId() == "order1");
    assert(allOrders.size() == 1);
    assert(allOrders[0].orderId() == "order2");

    std::cout << "testCancelOrder: passed" << std::endl;
}

void OrderCacheManagerTest::testGetAllOrders()
{
    OrderCacheManager manager;
    Order order1("order1", "sec1", "Buy", 10, "user1", "comp1");
    Order order2("order2", "sec2", "Sell", 5, "user2", "comp2");
    Order order3("order3", "sec3", "Buy", 12, "user3", "comp3");

    manager.addOrder(order1);
    manager.addOrder(order2);
    manager.addOrder(order3);

    std::vector<Order> allOrders = manager.getAllOrders();

    assert(allOrders.size() == 3);

    for (const Order& order : allOrders) {
        assert(order.orderId() == "order1" || order.orderId() == "order2" || order.orderId() == "order3");
    }

    std::cout << "testGetAllOrders: passed" << std::endl;
}

void OrderCacheManagerTest::testCancelNonexistentOrder()
{
    OrderCacheManager manager;
    Order order("order1", "sec1", "Buy", 10, "user1", "comp1");

    try {
        manager.cancelOrder("nonexistent_order");
        assert(false);
    } catch (const std::runtime_error& e) {
        std::cout << "testCancelNonexistentOrder: passed" << std::endl;
    }
}

void OrderCacheManagerTest::testAddDuplicateOrder()
{
    OrderCacheManager manager;
    Order order("order1", "sec1", "Buy", 10, "user1", "comp1");

    manager.addOrder(order);

    try {
        manager.addOrder(order);
        assert(false);
    } catch (const std::runtime_error& e) {
        std::cout << "testAddDuplicateOrder: passed" << std::endl;
    }
}
