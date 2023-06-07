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
    testGetMatchingSizeForSecurityScenario4();
    testGetMatchingSizeForSecurityScenario5();
    testGetMatchingSizeForSecurityScenario6();
    testGetMatchingSizeForSecurityScenario7();
    testGetMatchingSizeForSecurityScenario8();
    testGetMatchingSizeForSecurityScenario9();
    testGetMatchingSizeForSecurityScenario10();
    testGetMatchingSizeForSecurityScenario11();
    testGetMatchingSizeForSecurityScenario12();
    testGetMatchingSizeForSecurityScenario13();
    testGetMatchingSizeForSecurityScenario14();
    testGetMatchingSizeForSecurityScenario15();
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario1()
{
    QtyByCompanyBySecIdManager manager;
    int qtyCompanyBuy0 = 0;
    int qtyCompanyBuy1 = 0;
    int qtyCompanyBuy2 = 0;
    int qtyCompanySell0 = 0;
    int qtyCompanySell1 = 0;
    int qtyCompanySell2 = 0;

    // Scenario 1: Multiple matching orders with varying quantities
    for (int i = 1; i <= 150; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 5);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 4);
        std::string company = "company" + std::to_string(i % 3);

        Order order(orderId, secId, side, qty, user, company);
        if (secId == "secId1") {
            if (company == "company0") {
                if (side == "Sell") {
                    qtyCompanySell0 += qty;
                } else {
                    qtyCompanyBuy0 += qty;
                }
            }
            if (company == "company1") {
                if (side == "Sell") {
                    qtyCompanySell1 += qty;
                } else {
                    qtyCompanyBuy1 += qty;
                }
            }
            if (company == "company2") {
                if (side == "Sell") {
                    qtyCompanySell2 += qty;
                } else {
                    qtyCompanyBuy2 += qty;
                }
            }
        }
        manager.addOrder(order);
    }

    std:: cout << "qtyCompanyBuy0:" << qtyCompanyBuy0 << std::endl;
    std:: cout << "qtyCompanyBuy1:" << qtyCompanyBuy1 << std::endl;
    std:: cout << "qtyCompanyBuy2:" << qtyCompanyBuy2 << std::endl;
    std:: cout << "qtyCompanySell0:" << qtyCompanySell0 << std::endl;
    std:: cout << "qtyCompanySell1:" << qtyCompanySell1 << std::endl;
    std:: cout << "qtyCompanySell2:" << qtyCompanySell2 << std::endl;

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId1");
    assert(matchingSize == 30);

    std::cout << "testGetMatchingSizeForSecurityScenario1: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario2()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 2: No matching orders
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

    // Scenario 3: Multiple matching orders with varying quantities and users
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
    assert(matchingSize == 60);

    std::cout << "testGetMatchingSizeForSecurityScenario3: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario4()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 4: Multiple matching orders with varying quantities and companies
    for (int i = 1; i <= 180; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 4);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 4);
        std::string company = "company" + std::to_string(i % 4);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId2");
    assert(matchingSize == 90);

    std::cout << "testGetMatchingSizeForSecurityScenario4: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario5()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 5: Multiple matching orders with varying quantities, users, and companies
    for (int i = 1; i <= 160; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 4);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 5);
        std::string company = "company" + std::to_string(i % 4);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId3");
    assert(matchingSize == 120);

    std::cout << "testGetMatchingSizeForSecurityScenario5: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario6()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 6: No matching orders for a specific security ID
    for (int i = 1; i <= 130; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 3);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 4);
        std::string company = "company" + std::to_string(i % 3);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId4");
    assert(matchingSize == 0);

    std::cout << "testGetMatchingSizeForSecurityScenario6: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario7()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 7: Multiple matching orders with varying quantities and sides
    for (int i = 1; i <= 170; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 4);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 4);
        std::string company = "company" + std::to_string(i % 3);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId1");
    assert(matchingSize == 90);

    std::cout << "testGetMatchingSizeForSecurityScenario7: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario8()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 8: Multiple matching orders with varying quantities, sides, and users
    for (int i = 1; i <= 190; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 4);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 5);
        std::string company = "company" + std::to_string(i % 3);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId2");
    assert(matchingSize == 130);

    std::cout << "testGetMatchingSizeForSecurityScenario8: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario9()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 9: Multiple matching orders with varying quantities, sides, and companies
    for (int i = 1; i <= 180; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 4);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 4);
        std::string company = "company" + std::to_string(i % 4);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId3");
    assert(matchingSize == 150);

    std::cout << "testGetMatchingSizeForSecurityScenario9: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario10()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 10: Multiple matching orders with varying quantities, sides, users, and companies
    for (int i = 1; i <= 200; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 4);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 5);
        std::string company = "company" + std::to_string(i % 4);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId4");
    assert(matchingSize == 170);

    std::cout << "testGetMatchingSizeForSecurityScenario10: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario11()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 11: No matching orders for a specific user
    for (int i = 1; i <= 150; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 5);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 3);
        std::string company = "company" + std::to_string(i % 3);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId1");
    assert(matchingSize == 0);

    std::cout << "testGetMatchingSizeForSecurityScenario11: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario12()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 12: No matching orders for a specific company
    for (int i = 1; i <= 140; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string(i % 5);
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 4);
        std::string company = "company" + std::to_string(i % 2);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId2");
    assert(matchingSize == 0);

    std::cout << "testGetMatchingSizeForSecurityScenario12: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario13()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 13: Multiple matching orders with varying quantities and sides, but no matching security ID
    for (int i = 1; i <= 160; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string((i + 1) % 4); // No matching secId1
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 4);
        std::string company = "company" + std::to_string(i % 3);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId1");
    assert(matchingSize == 0);

    std::cout << "testGetMatchingSizeForSecurityScenario13: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario14()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 14: Multiple matching orders with varying quantities and users, but no matching security ID
    for (int i = 1; i <= 170; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string((i + 1) % 4); // No matching secId2
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string((i + 1) % 5); // No matching user0
        std::string company = "company" + std::to_string(i % 3);

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId2");
    assert(matchingSize == 0);

    std::cout << "testGetMatchingSizeForSecurityScenario14: passed" << std::endl;
}

void QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenario15()
{
    QtyByCompanyBySecIdManager manager;

    // Scenario 15: Multiple matching orders with varying quantities and companies, but no matching security ID
    for (int i = 1; i <= 180; ++i) {
        std::string orderId = "order" + std::to_string(i);
        std::string secId = "secId" + std::to_string((i + 1) % 4); // No matching secId3
        std::string side = (i % 2 == 0) ? "Buy" : "Sell";
        int qty = (i % 3 + 1) * 10;
        std::string user = "user" + std::to_string(i % 4);
        std::string company = "company" + std::to_string((i + 1) % 3); // No matching company0

        Order order(orderId, secId, side, qty, user, company);
        manager.addOrder(order);
    }

    unsigned int matchingSize = manager.getMatchingSizeForSecurity("secId3");
    assert(matchingSize == 0);

    std::cout << "testGetMatchingSizeForSecurityScenario15: passed" << std::endl;
}

bool QtyByCompanyBySecIdManagerTest::contains(const std::vector<std::string>& vec, const std::string& value)
{
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}
