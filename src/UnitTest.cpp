#include "OrderCacheManagerTest.h"
#include "OrdersByUserManagerTest.h"

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

int main()
{
    testOrderCacheManager();
    testOrdersByUserManager();
    return 0;
}
