#include "OrderCacheImp.h"

OrderCacheImp::OrderCacheImp() : m_orderCacheManager(), m_ordersByUserManager(),
    m_qtyByCompanyBySecIdManager(), m_orderQtyByOrderIdBySecIdManager()
{
}

OrderCacheImp::~OrderCacheImp()
{
}

void OrderCacheImp::addOrder(Order order)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_orderCacheManager.addOrder(order);
    m_ordersByUserManager.addOrder(order);
    m_orderQtyByOrderIdBySecIdManager.addOrder(order);

    try {
        m_qtyByCompanyBySecIdManager.addOrder(order);
    } catch (std::runtime_error e) {
        m_orderCacheManager.cancelOrder(order.orderId());
        m_ordersByUserManager.cancelOrder(order);
        m_orderQtyByOrderIdBySecIdManager.cancelOrder(order);
        throw e;
    }
}

void OrderCacheImp::cancelOrder(const std::string& orderId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    Order order = m_orderCacheManager.cancelOrder(orderId);
    m_ordersByUserManager.cancelOrder(order);
    m_orderQtyByOrderIdBySecIdManager.cancelOrder(order);
    m_qtyByCompanyBySecIdManager.cancelOrder(order);
}

void OrderCacheImp::cancelOrdersForUser(const std::string& user)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (const auto& orderId : m_ordersByUserManager.getAllUserOrders(user)) {
        cancelOrder(orderId);
    }
}

void OrderCacheImp::cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (const auto& orderId : m_orderQtyByOrderIdBySecIdManager.
        getOrdersForSecIdWithMinimumQty(securityId, minQty)) {
        cancelOrder(orderId);
    }
}

unsigned int OrderCacheImp::getMatchingSizeForSecurity(const std::string& securityId)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_qtyByCompanyBySecIdManager.getMatchingSizeForSecurity(securityId);
}

std::vector<Order> OrderCacheImp::getAllOrders() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_orderCacheManager.getAllOrders();
}
