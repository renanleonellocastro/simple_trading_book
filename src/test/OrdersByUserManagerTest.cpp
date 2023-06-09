#include <algorithm>

#include "OrdersByUserManagerTest.h"

void OrdersByUserManagerTest::testAddOrder()
{
    OrdersByUserManager ordersByUserManager;

    Order order1("order1", "security1", "Buy", 100, "user1", "company1");
    ordersByUserManager.addOrder(order1);

    Order order2("order2", "security1", "Buy", 200, "user1", "company1");
    ordersByUserManager.addOrder(order2);

    Order order3("order3", "security2", "Sell", 150, "user2", "company2");
    ordersByUserManager.addOrder(order3);

    std::vector<std::string> user1Orders = ordersByUserManager.getAllUserOrders("user1");
    assert(user1Orders.size() == 2);
    assert(std::find(user1Orders.begin(), user1Orders.end(), std::string("order1")) != user1Orders.end());
    assert(std::find(user1Orders.begin(), user1Orders.end(), std::string("order2")) != user1Orders.end());

    std::vector<std::string> user2Orders = ordersByUserManager.getAllUserOrders("user2");
    std::unordered_set<std::string> user2OrderSet(user2Orders.begin(), user2Orders.end());
    assert(user2OrderSet.find("order3") != user2OrderSet.end());
    assert(user2OrderSet.size() == 1);

    std::vector<std::string> user3Orders = ordersByUserManager.getAllUserOrders("user3");
    assert(user3Orders.empty());

    std::cout << "testAddOrder: passed" << std::endl;
}

void OrdersByUserManagerTest::testCancelOrder()
{
    OrdersByUserManager ordersByUserManager;

    Order order1("order1", "security1", "Buy", 100, "user1", "company1");
    ordersByUserManager.addOrder(order1);

    Order order2("order2", "security1", "Buy", 200, "user1", "company1");
    ordersByUserManager.addOrder(order2);

    Order order3("order3", "security2", "Sell", 150, "user2", "company2");
    ordersByUserManager.addOrder(order3);

    ordersByUserManager.cancelOrder(order1);

    std::vector<std::string> user1Orders = ordersByUserManager.getAllUserOrders("user1");
    std::unordered_set<std::string> user1OrderSet(user1Orders.begin(), user1Orders.end());
    assert(user1OrderSet.find("order1") == user1OrderSet.end());
    assert(user1OrderSet.find("order2") != user1OrderSet.end());
    assert(user1OrderSet.size() == 1);

    std::vector<std::string> user2Orders = ordersByUserManager.getAllUserOrders("user2");
    std::unordered_set<std::string> user2OrderSet(user2Orders.begin(), user2Orders.end());
    assert(user2OrderSet.find("order3") != user2OrderSet.end());
    assert(user2OrderSet.size() == 1);

    std::cout << "testCancelOrder: passed" << std::endl;
}

void OrdersByUserManagerTest::testGetAllUserOrders()
{
    OrdersByUserManager ordersByUserManager;

    Order order1("order1", "security1", "Buy", 100, "user1", "company1");
    ordersByUserManager.addOrder(order1);

    Order order2("order2", "security1", "Buy", 200, "user1", "company1");
    ordersByUserManager.addOrder(order2);

    Order order3("order3", "security2", "Sell", 150, "user2", "company2");
    ordersByUserManager.addOrder(order3);

    std::vector<std::string> user1Orders = ordersByUserManager.getAllUserOrders("user1");
    std::unordered_set<std::string> user1OrderSet(user1Orders.begin(), user1Orders.end());
    assert(user1OrderSet.find("order1") != user1OrderSet.end());
    assert(user1OrderSet.find("order2") != user1OrderSet.end());
    assert(user1OrderSet.size() == 2);

    std::vector<std::string> user2Orders = ordersByUserManager.getAllUserOrders("user2");
    std::unordered_set<std::string> user2OrderSet(user2Orders.begin(), user2Orders.end());
    assert(user2OrderSet.find("order3") != user2OrderSet.end());
    assert(user2OrderSet.size() == 1);

    std::vector<std::string> user3Orders = ordersByUserManager.getAllUserOrders("user3");
    assert(user3Orders.empty());

    std::cout << "testGetAllUserOrders: passed" << std::endl;
}

void OrdersByUserManagerTest::testCancelOrderThrowsIfUserNotFound()
{
    OrdersByUserManager ordersByUserManager;

    Order order1("order1", "security1", "Buy", 100, "user1", "company1");
    ordersByUserManager.addOrder(order1);

    Order order2("order2", "security1", "Buy", 200, "user2", "company1");
    ordersByUserManager.addOrder(order2);

    Order order3("order3", "security2", "Sell", 150, "user3", "company2");
    try {
        ordersByUserManager.cancelOrder(order3);
        assert(false);
    } catch (const std::runtime_error& error) {
        assert(std::string(error.what()) == "User: user3 does not exist in the book.");
    }

    std::vector<std::string> user1Orders = ordersByUserManager.getAllUserOrders("user1");
    std::unordered_set<std::string> user1OrderSet(user1Orders.begin(), user1Orders.end());
    assert(user1OrderSet.find("order1") != user1OrderSet.end());
    assert(user1OrderSet.size() == 1);

    std::vector<std::string> user2Orders = ordersByUserManager.getAllUserOrders("user2");
    std::unordered_set<std::string> user2OrderSet(user2Orders.begin(), user2Orders.end());
    assert(user2OrderSet.find("order2") != user2OrderSet.end());
    assert(user2OrderSet.size() == 1);

    std::cout << "testCancelOrderThrowsIfUserNotFound: passed" << std::endl;
}

void OrdersByUserManagerTest::testCancelOrderThrowsIfOrderNotFound()
{
    OrdersByUserManager ordersByUserManager;

    Order order1("order1", "security1", "Buy", 100, "user1", "company1");
    ordersByUserManager.addOrder(order1);

    Order order2("order2", "security1", "Buy", 200, "user1", "company1");
    ordersByUserManager.addOrder(order2);

    Order order3("order3", "security2", "Sell", 150, "user1", "company2");
    try {
        ordersByUserManager.cancelOrder(order3);
        assert(false);
    } catch (const std::runtime_error& error) {
        assert(std::string(error.what()) == "Order: order3 does not exist in the book.");
    }

    std::vector<std::string> user1Orders = ordersByUserManager.getAllUserOrders("user1");
    std::unordered_set<std::string> user1OrderSet(user1Orders.begin(), user1Orders.end());
    assert(user1OrderSet.find("order1") != user1OrderSet.end());
    assert(user1OrderSet.find("order2") != user1OrderSet.end());
    assert(user1OrderSet.size() == 2);

    std::cout << "testCancelOrderThrowsIfOrderNotFound: passed" << std::endl;
}
