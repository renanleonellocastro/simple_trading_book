#include <algorithm>

#include "QtyByCompanyBySecIdManagerTest.h"

void QtyByCompanyBySecIdManagerTest::testAddOrder()
{
    QtyByCompanyBySecIdManager manager;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user2", "company2");

    manager.addOrder(order1);
    manager.addOrder(order2);

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId1");
    assert(matchingSize == 5);

    std::cout << "testAddOrder: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testCancelOrder()
{
    QtyByCompanyBySecIdManager manager;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user2", "company2");

    manager.addOrder(order1);
    manager.addOrder(order2);

    manager.cancelOrder(order1);

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId1");
    assert(matchingSize == 0);

    std::cout << "testCancelOrder: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurity1()
{
    QtyByCompanyBySecIdManager manager;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 5, "user2", "company2");
    Order order3("order3", "secId1", "Buy", 20, "user1", "company1");
    Order order4("order4", "secId2", "Buy", 20, "user1", "company1");

    manager.addOrder(order1);
    manager.addOrder(order2);
    manager.addOrder(order3);
    manager.addOrder(order4);

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId1");
    assert(matchingSize == 5);

    matchingSize = manager.getMatchingSizeForSecurity("secId2");
    assert(matchingSize == 0);

    std::cout << "testGetMatchingSizeForSecurity1: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurity2()
{
    QtyByCompanyBySecIdManager manager;

    Order order1("order1", "secId1", "Buy", 100, "user1", "company1");
    Order order2("order2", "secId1", "Sell", 100, "user1", "company1");
    Order order3("order3", "secId1", "Buy", 50, "user2", "company2");
    Order order4("order4", "secId1", "Sell", 50, "user2", "company2");
    Order order5("order5", "secId1", "Buy", 150, "user3", "company3");
    Order order6("order6", "secId1", "Sell", 150, "user3", "company3");

    manager.addOrder(order1);
    manager.addOrder(order2);
    manager.addOrder(order3);
    manager.addOrder(order4);
    manager.addOrder(order5);
    manager.addOrder(order6);

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId1");
    assert(matchingSize == 300);

    std::cout << "testGetMatchingSizeForSecurity2: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testExceptionCaseInvalidOrderSideOnAddOrder()
{
    QtyByCompanyBySecIdManager manager;

    Order order("order1", "secId1", "InvalidSide", 10, "user1", "company1");

    try {
        manager.addOrder(order);
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(e.what() == std::string("Order side: InvalidSide invalid."));
    }

    std::cout << "testExceptionCaseInvalidOrderSideOnAddOrder: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testExceptionCaseInvalidOrderSideOnCancelOrder()
{
    QtyByCompanyBySecIdManager manager;

    Order order("order1", "secId1", "InvalidSide", 10, "user1", "company1");

    try {
        manager.cancelOrder(order);
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(e.what() == std::string("Order side: InvalidSide invalid."));
    }

    std::cout << "testExceptionCaseInvalidOrderSideOnCancelOrder: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testExceptionCaseSecIdNotExistOnBook()
{
    QtyByCompanyBySecIdManager manager;

    Order order("order1", "secId1", "Buy", 10, "user1", "company1");

    try {
        manager.cancelOrder(order);
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(e.what() == std::string("Security ID: secId1 does not exist in the book."));
    }

    std::cout << "testExceptionCaseSecIdNotExistOnBook: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testExceptionCaseCompanyNotExistOnBook()
{
    QtyByCompanyBySecIdManager manager;

    Order order1("order1", "secId1", "Buy", 10, "user1", "company1");
    Order order2("order2", "secId1", "Buy", 5, "user2", "company2");

    manager.addOrder(order1);

    try {
        manager.cancelOrder(order2);
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(e.what() == std::string("Company: company2 does not exist in the book for security ID secId1."));
    }

    std::cout << "testExceptionCaseCompanyNotExistOnBook: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenarios()
{
    testGetMatchingSizeForSecurityScenario1();
    testGetMatchingSizeForSecurityScenario2();
    testGetMatchingSizeForSecurityScenario3();
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario1()
{
    QtyByCompanyBySecIdManager manager;

    for (int i = 1; i <= 150; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 5);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 4);
        std::string company = "company" + std::to_string(i % 3);

        Order order(orderId, secId, side, qty, user, company);

        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId1");
    assert(matchingSize == 300);

    std::cout << "testGetMatchingSizeForSecurityScenario1: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario2()
{
    QtyByCompanyBySecIdManager manager;

    for (int i = 1; i <= 120; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 5);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 4);
        std::string company = "company" + std::to_string(i % 3);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId6");
    assert(matchingSize == 0);

    std::cout << "testGetMatchingSizeForSecurityScenario2: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario3()
{
    QtyByCompanyBySecIdManager manager;

    for (int i = 1; i <= 200; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 4);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 5);
        std::string company = "company" + std::to_string(i % 3);

        Order order(orderId, secId, side, qty, user, company);

        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId1");
    assert(matchingSize == 0);

    std::cout << "testGetMatchingSizeForSecurityScenario3: passed" << std::endl;
}

bool QtyByCompanyBySecIdManagerTest::contains(const std::vector<std::string>& vec, const std::string& value)
{
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}
