#include <cassert>
#include <iostream>
#include <stdexcept>

#include "OrderCacheImp.h"

#pragma once

class OrderCacheImpTest
{
public:
    static void testAddOrder();
    static void testCancelOrder();
    static void testCancelOrdersForUser();
    static void testCancelOrdersForSecIdWithMinimumQty();
    static void testGetMatchingSizeForSecurity();
    static void testGetAllOrders();
};
