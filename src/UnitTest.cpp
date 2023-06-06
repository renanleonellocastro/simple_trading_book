#include "OrderCacheManagerTest.h"
#include "OrdersByUserManagerTest.h"
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

int main()
{
    testOrderCacheManager();
    testOrdersByUserManager();
    testOrderQtyByOrderIdBySecIdManager();
    return 0;
}
