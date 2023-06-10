#include "OrderCacheImpTest.h"
#include "OrderCacheManagerTest.h"
#include "OrdersByUserManagerTest.h"
#include "QtyByCompanyBySecIdManagerTest.h"
#include "OrderQtyByOrderIdBySecIdManagerTest.h"

void testOrderCacheManager()
{
    OrderCacheManagerTest::testAddOrder();
    OrderCacheManagerTest::testCancelOrder();
    OrderCacheManagerTest::testGetAllOrders();
    OrderCacheManagerTest::testCancelNonexistentOrder();
    OrderCacheManagerTest::testAddDuplicateOrder();
}

void testOrdersByUserManager()
{
    OrdersByUserManagerTest::testAddOrder();
    OrdersByUserManagerTest::testCancelOrder();
    OrdersByUserManagerTest::testGetAllUserOrders();
    OrdersByUserManagerTest::testCancelOrderThrowsIfUserNotFound();
    OrdersByUserManagerTest::testCancelOrderThrowsIfOrderNotFound();
}

void testOrderQtyByOrderIdBySecIdManager()
{
    OrderQtyByOrderIdBySecIdManagerTest::testAddOrder();
    OrderQtyByOrderIdBySecIdManagerTest::testGetOrdersForSecIdWithMinimumQty();
    OrderQtyByOrderIdBySecIdManagerTest::testCancelOrder();
    OrderQtyByOrderIdBySecIdManagerTest::testExceptionCaseSecIdNotExistOnBook();
    OrderQtyByOrderIdBySecIdManagerTest::testExceptionCaseOrderIdNotExistOnBook();
}

void testQtyByCompanyBySecIdManager()
{
    QtyByCompanyBySecIdManagerTest::testAddOrder();
    QtyByCompanyBySecIdManagerTest::testCancelOrder();
    QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurity1();
    QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurity2();
    QtyByCompanyBySecIdManagerTest::testExceptionCaseInvalidOrderSideOnAddOrder();
    QtyByCompanyBySecIdManagerTest::testExceptionCaseInvalidOrderSideOnCancelOrder();
    QtyByCompanyBySecIdManagerTest::testExceptionCaseSecIdNotExistOnBook();
    QtyByCompanyBySecIdManagerTest::testExceptionCaseCompanyNotExistOnBook();
    QtyByCompanyBySecIdManagerTest::testGetMatchingSizeForSecurityScenarios();
}

void testOrderCacheImp()
{
    OrderCacheImpTest::testAddOrder();
    OrderCacheImpTest::testCancelOrder();
    OrderCacheImpTest::testCancelOrdersForUser();
    OrderCacheImpTest::testCancelOrdersForSecIdWithMinimumQty();
    OrderCacheImpTest::testGetMatchingSizeForSecurity();
    OrderCacheImpTest::testGetAllOrders();
    OrderCacheImpTest::testMultiThreadScenario();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample1();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample2();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample3();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample4();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample5();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample6();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample7();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample8();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample9();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample10();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample11();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample12();
    OrderCacheImpTest::testGetMatchingSizeForSecurityExample13();
}

int main()
{
    testOrderCacheManager();
    testOrdersByUserManager();
    testOrderQtyByOrderIdBySecIdManager();
    testQtyByCompanyBySecIdManager();
    testOrderCacheImp();
    std::cout << "ALL TESTS HAVE PASSED!" << std::endl;
    return 0;
}
