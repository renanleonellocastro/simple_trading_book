#include <cassert>
#include <iostream>
#include <stdexcept>

#include "OrderQtyByOrderIdBySecIdManager.h"

#pragma once

class OrderQtyByOrderIdBySecIdManagerTest
{
public:
    static void testAddOrder();
    static void testGetOrdersForSecIdWithMinimumQty();
    static void testCancelOrder();
    static void testExceptionCaseSecIdNotExistOnBook();
    static void testExceptionCaseOrderIdNotExistOnBook();

private:
    static bool contains(const std::vector<std::string>& vec, const std::string& value);
};
