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
