#include <cassert>
#include <iostream>

#include "OrderCacheManager.h"

void testAddOrder()
{
    OrderCacheManager manager;
    Order order1("order1", "sec1", "Buy", 10, "user1", "comp1");
    Order order2("order2", "sec2", "Sell", 5, "user2", "comp2");

    manager.addOrder(order1);
    manager.addOrder(order2);

    std::vector<Order> allOrders = manager.getAllOrders();

    assert(allOrders.size() == 2);
    assert(allOrders[0].orderId() == "order1");
    assert(allOrders[1].orderId() == "order2");

    std::cout << "testAddOrder: passed" << std::endl;
}

void testCancelOrder()
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

void testGetAllOrders()
{
    OrderCacheManager manager;
    Order order1("order1", "sec1", "Buy", 10, "user1", "comp1");
    Order order2("order2", "sec2", "Sell", 5, "user2", "comp2");

    manager.addOrder(order1);
    manager.addOrder(order2);

    std::vector<Order> allOrders = manager.getAllOrders();

    assert(allOrders.size() == 2);
    assert(allOrders[0].orderId() == "order1");
    assert(allOrders[1].orderId() == "order2");

    std::cout << "testGetAllOrders: passed" << std::endl;
}

int main()
{
    testAddOrder();
    testCancelOrder();
    testGetAllOrders();

    return 0;
}
