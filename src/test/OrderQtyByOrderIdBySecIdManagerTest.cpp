#include <algorithm>

#include "OrderQtyByOrderIdBySecIdManagerTest.h"

void OrderQtyByOrderIdBySecIdManagerTest::testAddOrder()
{
    OrderQtyByOrderIdBySecIdManager manager;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user2", "company2");

    manager.addOrder(order1);
    manager.addOrder(order2);

    std::vector<std::string> orders = manager.getOrdersForSecIdWithMinimumQty("secId1", 5);
    assert(orders.size() == 2);
    assert(contains(orders, "order1"));
    assert(contains(orders, "order2"));

    std::cout << "testAddOrder: passed" << std::endl;
}

void OrderQtyByOrderIdBySecIdManagerTest::testGetOrdersForSecIdWithMinimumQty()
{
    OrderQtyByOrderIdBySecIdManager manager;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user2", "company2");
    Order order3("order3", "secId1", "Buy", 20, "user1", "company1");
    Order order4("order4", "secId2", "Buy", 20, "user1", "company1");

    manager.addOrder(order1);
    manager.addOrder(order2);
    manager.addOrder(order3);
    manager.addOrder(order4);

    std::vector<std::string> orders = manager.getOrdersForSecIdWithMinimumQty("secId1", 5);
    assert(orders.size() == 3);
    assert(contains(orders, "order1"));
    assert(contains(orders, "order2"));
    assert(contains(orders, "order3"));

    orders = manager.getOrdersForSecIdWithMinimumQty("secId1", 15);
    assert(orders.size() == 1);
    assert(contains(orders, "order3"));

    orders = manager.getOrdersForSecIdWithMinimumQty("secId1", 10);
    assert(contains(orders, "order1"));
    assert(contains(orders, "order3"));

    orders = manager.getOrdersForSecIdWithMinimumQty("secId2", 1);
    assert(contains(orders, "order4"));

    orders = manager.getOrdersForSecIdWithMinimumQty("secId3", 1);
    assert(orders.empty());

    std::cout << "testGetOrdersForSecIdWithMinimumQty: passed" << std::endl;
}

void OrderQtyByOrderIdBySecIdManagerTest::testCancelOrder()
{
    OrderQtyByOrderIdBySecIdManager manager;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user2", "company2");

    manager.addOrder(order1);
    manager.addOrder(order2);

    manager.cancelOrder(order1);

    std::vector<std::string> orders = manager.getOrdersForSecIdWithMinimumQty("secId1", 5);
    assert(orders.size() == 1);
    assert(contains(orders, "order2"));

    manager.cancelOrder(order2);

    orders = manager.getOrdersForSecIdWithMinimumQty("secId1", 5);
    assert(orders.empty());

    std::cout << "testCancelOrder: passed" << std::endl;
}

void OrderQtyByOrderIdBySecIdManagerTest::testExceptionCaseSecIdNotExistOnBook()
{
    OrderQtyByOrderIdBySecIdManager manager;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId2", "Sell", 5, "user2", "company1");
    Order order3("order3", "secId1", "Sell", 5, "user1", "company1");

    try {
        manager.addOrder(order1);
        manager.cancelOrder(order2);
        assert(false);
    } catch (const std::runtime_error& error) {
        assert(std::string(error.what()) == "SecurityID: secId2 does not exist in the book.");
    }

    std::cout << "testExceptionCaseSecIdNotExistOnBook: passed" << std::endl;
}

void OrderQtyByOrderIdBySecIdManagerTest::testExceptionCaseOrderIdNotExistOnBook()
{
    OrderQtyByOrderIdBySecIdManager manager;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId2", "Sell", 5, "user2", "company1");
    Order order3("order3", "secId1", "Sell", 5, "user1", "company1");

    try {
        manager.addOrder(order1);
        manager.cancelOrder(order3);
        assert(false);
    } catch (const std::runtime_error& error) {
        assert(std::string(error.what()) == "Order ID: order3 does not exist in the book for security ID secId1.");
    }

    std::cout << "testExceptionCaseOrderIdNotExistOnBook: passed" << std::endl;
}

bool OrderQtyByOrderIdBySecIdManagerTest::contains(const std::vector<std::string>& vec,
    const std::string& value)
{
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}
