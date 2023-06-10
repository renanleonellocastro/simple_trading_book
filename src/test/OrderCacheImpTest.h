#include <cassert>
#include <iostream>
#include <stdexcept>

#include "../OrderCacheImp.h"

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
    static void testGetMatchingSizeForSecurityExample1();
    static void testGetMatchingSizeForSecurityExample2();
    static void testGetMatchingSizeForSecurityExample3();
    static void testGetMatchingSizeForSecurityExample4();
    static void testGetMatchingSizeForSecurityExample5();
    static void testGetMatchingSizeForSecurityExample6();
    static void testGetMatchingSizeForSecurityExample7();
    static void testGetMatchingSizeForSecurityExample8();
    static void testGetMatchingSizeForSecurityExample9();
    static void testGetMatchingSizeForSecurityExample10();
};
