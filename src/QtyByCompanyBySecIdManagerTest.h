#include <cassert>
#include <iostream>
#include <stdexcept>

#include "QtyByCompanyBySecIdManager.h"

#pragma once

class QtyByCompanyBySecIdManagerTest
{
public:
    static void testAddOrder();
    static void testCancelOrder();
    static void testGetMatchingSizeForSecurity1();
    static void testGetMatchingSizeForSecurity2();
    static void testExceptionCaseInvalidOrderSideOnAddOrder();
    static void testExceptionCaseInvalidOrderSideOnCancelOrder();
    static void testExceptionCaseSecIdNotExistOnBook();
    static void testExceptionCaseCompanyNotExistOnBook();
    static void testGetMatchingSizeForSecurityScenarios();

private:
    static void testGetMatchingSizeForSecurityScenario1();
    static void testGetMatchingSizeForSecurityScenario2();
    static void testGetMatchingSizeForSecurityScenario3();
    static void testGetMatchingSizeForSecurityScenario4();
    static void testGetMatchingSizeForSecurityScenario5();
    static void testGetMatchingSizeForSecurityScenario6();
    static void testGetMatchingSizeForSecurityScenario7();
    static void testGetMatchingSizeForSecurityScenario8();
    static void testGetMatchingSizeForSecurityScenario9();
    static void testGetMatchingSizeForSecurityScenario10();
    static void testGetMatchingSizeForSecurityScenario11();
    static void testGetMatchingSizeForSecurityScenario12();
    static void testGetMatchingSizeForSecurityScenario13();
    static void testGetMatchingSizeForSecurityScenario14();
    static void testGetMatchingSizeForSecurityScenario15();
    static bool contains(const std::vector<std::string>& vec, const std::string& value);
};
