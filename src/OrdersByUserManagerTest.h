#include <vector>
#include <cassert>
#include <iostream>
#include <unordered_set>

#include "OrdersByUserManager.h"

#pragma once

class OrdersByUserManagerTest
{
public:
    static void testAddOrder();
    static void testCancelOrder();
    static void testGetAllUserOrders();
    static void testCancelOrderThrowsIfUserNotFound();
    static void testCancelOrderThrowsIfOrderNotFound();
};
