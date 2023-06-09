#include <cassert>
#include <iostream>
#include <stdexcept>

#include "../OrderCacheManager.h"

#pragma once

class OrderCacheManagerTest
{
public:
    static void testAddOrder();
    static void testCancelOrder();
    static void testGetAllOrders();
    static void testCancelNonexistentOrder();
    static void testAddDuplicateOrder();
};
