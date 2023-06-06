#include <string>
#include <sstream>

#include "QtyByCompanyBySecIdManager.h"

QtyByCompanyBySecIdManager::QtyByCompanyBySecIdManager() : m_buyQtyByCompanyBySecIdMap(),
    m_sellQtyByCompanyBySecIdMap()
{
}

QtyByCompanyBySecIdManager::~QtyByCompanyBySecIdManager()
{
}

void QtyByCompanyBySecIdManager::addOrder(const Order& order)
{
    if (order.side() == "Buy") {
        m_buyQtyByCompanyBySecIdMap[order.securityId()][order.company()] += order.qty();
    } else if (order.side() == "Sell") {
        m_sellQtyByCompanyBySecIdMap[order.securityId()][order.company()] += order.qty();
    } else {
        std::stringstream ss;
        ss << "Order side: " << order.side() << " invalid.";
        throw std::runtime_error(ss.str());
    }
}

void QtyByCompanyBySecIdManager::cancelOrder(const Order& order)
{
    if (order.side() == "Buy") {
        eraseOrderFromMap(m_buyQtyByCompanyBySecIdMap, order);
    } else if (order.side() == "Sell") {
        eraseOrderFromMap(m_sellQtyByCompanyBySecIdMap, order);
    }
}

unsigned int QtyByCompanyBySecIdManager::getMatchingSizeForSecurity(const std::string& securityId)
{
    unsigned int totalMatchingSize = 0;
    std::unordered_map<std::string, std::uint32_t> buyQtyByCompanyMap = m_buyQtyByCompanyBySecIdMap[securityId];
    std::unordered_map<std::string, std::uint32_t> sellQtyByCompanyMap = m_sellQtyByCompanyBySecIdMap[securityId];

    for (auto buyQtyByCompany : buyQtyByCompanyMap) {
        for (auto sellQtyByCompany : sellQtyByCompanyMap) {
            if (buyQtyByCompany.first != sellQtyByCompany.first) {
                std::uint32_t matchSize = std::min(buyQtyByCompany.second, sellQtyByCompany.second); 
                totalMatchingSize += matchSize;
                buyQtyByCompany.second -= matchSize;
                sellQtyByCompany.second -= matchSize;
            }
        }
    }

    return totalMatchingSize;
}

void QtyByCompanyBySecIdManager::eraseOrderFromMap(std::unordered_map<std::string, std::unordered_map<std::string,
    unsigned int>>& map, const Order& order)
{
    if (map.count(order.securityId()) == 0) {
        std::stringstream ss;
        ss << "Security ID: " << order.securityId() << " does not exist in the book.";
        throw std::runtime_error(ss.str());
    }

    if (map[order.securityId()].count(order.company()) == 0) {
        std::stringstream ss;
        ss << "Company: " << order.company() <<
            " does not exist in the book for security ID " << order.securityId() << ".";
        throw std::runtime_error(ss.str());
    }

    map[order.securityId()][order.company()] -= order.qty();

    if (map[order.securityId()][order.company()] == 0) {
        map[order.securityId()].erase(order.company());
    }
    
    if (map[order.securityId()].size() == 0) {
        map.erase(order.securityId());
    }
}
