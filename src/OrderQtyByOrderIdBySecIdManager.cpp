#include <string>
#include <sstream>

#include "OrderQtyByOrderIdBySecIdManager.h"

OrderQtyByOrderIdBySecIdManager::OrderQtyByOrderIdBySecIdManager() : m_ordersQtyByOrderIdBySecIdMap()
{
}

OrderQtyByOrderIdBySecIdManager::~OrderQtyByOrderIdBySecIdManager()
{
}

void OrderQtyByOrderIdBySecIdManager::addOrder(const Order& order)
{
    m_ordersQtyByOrderIdBySecIdMap[order.securityId()][order.orderId()] = order.qty();
}

void OrderQtyByOrderIdBySecIdManager::cancelOrder(const Order& order)
{
    if (m_ordersQtyByOrderIdBySecIdMap.count(order.user()) == 0) {
        std::stringstream ss;
        ss << "User: " << order.user() << " does not exist in the book.";
        throw std::runtime_error(ss.str());
    }

    if (m_ordersQtyByOrderIdBySecIdMap[order.user()].count(order.securityId()) == 0) {
        std::stringstream ss;
        ss << "Security ID: " << order.securityId() <<
            " does not exist in the book for user " << order.user() << ".";
        throw std::runtime_error(ss.str());
    }

    m_ordersQtyByOrderIdBySecIdMap[order.securityId()].erase(order.orderId());

    if (m_ordersQtyByOrderIdBySecIdMap[order.securityId()].size() == 0) {
        m_ordersQtyByOrderIdBySecIdMap.erase(order.securityId());
    }
}

std::vector<std::string>  OrderQtyByOrderIdBySecIdManager::getOrdersForSecIdWithMinimumQty
    (const std::string& securityId, unsigned int minQty)
{
    std::vector<std::string> ordersIdsForSecIdWithMinimumQty;

    if (m_ordersQtyByOrderIdBySecIdMap.count(securityId)) {
        for (const auto& orderQtyByOrderIdBySecId : m_ordersQtyByOrderIdBySecIdMap[securityId]) {
            if (orderQtyByOrderIdBySecId.second >= minQty) {
                ordersIdsForSecIdWithMinimumQty.push_back(orderQtyByOrderIdBySecId.first);
            }
        }
    }

    return ordersIdsForSecIdWithMinimumQty;
}
