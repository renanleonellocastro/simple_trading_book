#include <string>
#include <sstream>

#include "OrderCacheManager.h"

OrderCacheManager::OrderCacheManager() : m_orderCacheMap()
{
}

OrderCacheManager::~OrderCacheManager()
{
}

void OrderCacheManager::addOrder(const Order& order)
{
    if (m_orderCacheMap.count(order.orderId())) {
        std::stringstream ss;
        ss << "Order with orderId: " << order.orderId() << " already exists in the book.";
        throw std::runtime_error(ss.str());
    }

    m_orderCacheMap[order.orderId()] = order;
}

Order OrderCacheManager::cancelOrder(const std::string& orderId)
{
    if (m_orderCacheMap.count(orderId) == 0) {
        std::stringstream ss;
        ss << "Order with orderId: " << orderId << " does not exist in the book.";
        throw std::runtime_error(ss.str());
    }

    Order order = m_orderCacheMap[orderId];
    m_orderCacheMap.erase(orderId);
    return order;
}

std::vector<Order> OrderCacheManager::getAllOrders() const
{
    std::vector<Order> allOrders;
    allOrders.reserve(m_orderCacheMap.size());

    for (const auto& orderEntry : m_orderCacheMap) {
        allOrders.push_back(orderEntry.second);
    }

    return allOrders;
}
