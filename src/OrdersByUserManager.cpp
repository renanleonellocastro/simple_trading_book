#include <string>
#include <sstream>

#include "OrdersByUserManager.h"

OrdersByUserManager::OrdersByUserManager() : m_ordersByUserMap()
{
}

OrdersByUserManager::~OrdersByUserManager()
{
}

void OrdersByUserManager::addOrder(const Order& order)
{
    m_ordersByUserMap[order.user()][order.orderId()] = true;
}

void OrdersByUserManager::cancelOrder(const Order& order)
{
    if (m_ordersByUserMap.count(order.user()) == 0) {
        std::stringstream ss;
        ss << "User: " << order.user() << " does not exist in the book.";
        throw std::runtime_error(ss.str());
    }

    if (m_ordersByUserMap[order.user()].count(order.orderId()) == 0) {
        std::stringstream ss;
        ss << "Order: " << order.orderId() << " does not exist in the book.";
        throw std::runtime_error(ss.str());
    }

    m_ordersByUserMap[order.user()].erase(order.orderId());

    if (m_ordersByUserMap[order.user()].size() == 0) {
        m_ordersByUserMap.erase(order.user());
    }
}

std::vector<std::string> OrdersByUserManager::getAllUserOrders(const std::string& user)
{
    std::vector<std::string> orderIds;

    if (m_ordersByUserMap.count(user)) {
        const auto& orderList = m_ordersByUserMap[user];
        orderIds.reserve(m_ordersByUserMap[user].size());

        for (const auto& orderId : orderList) {
            orderIds.push_back(orderId.first);
        }
    }

    return orderIds;
}
