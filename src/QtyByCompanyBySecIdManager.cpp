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
    } else {
        std::stringstream ss;
        ss << "Order side: " << order.side() << " invalid.";
        throw std::runtime_error(ss.str());
    }
}

unsigned int QtyByCompanyBySecIdManager::getMatchingSizeForSecurity(const std::string& securityId)
{
    unsigned int totalMatchingSize = 0;
    std::multiset<QtyByCompany> buyQtyByCompanyMultiset = getMultisetFromMap(m_buyQtyByCompanyBySecIdMap[securityId]);
    std::multiset<QtyByCompany> sellQtyByCompanyMultiset = getMultisetFromMap(m_sellQtyByCompanyBySecIdMap[securityId]);

    greedyRecursiveAlgorithmToGetMaximumMatches(buyQtyByCompanyMultiset, sellQtyByCompanyMultiset, totalMatchingSize);

    return totalMatchingSize;
}

std::multiset<QtyByCompany> QtyByCompanyBySecIdManager::getMultisetFromMap(const std::unordered_map<
    std::string, std::uint32_t>& map)
{
    std::multiset<QtyByCompany> qtyByCompanyMultiset;

    for (const auto& qtyByCompanyPair : map) {
        qtyByCompanyMultiset.insert(QtyByCompany(qtyByCompanyPair.first, qtyByCompanyPair.second));
    }

    return qtyByCompanyMultiset;
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

void QtyByCompanyBySecIdManager::greedyRecursiveAlgorithmToGetMaximumMatches(std::multiset<
    QtyByCompany>& buyQtyByCompanyMultiset, std::multiset<QtyByCompany>& sellQtyByCompanyMultiset,
    unsigned int& matches)
{
    // stop recursion criteria
    if ((buyQtyByCompanyMultiset.size() <= 1) && (sellQtyByCompanyMultiset.size() <= 1)) {
        if ((buyQtyByCompanyMultiset.size() == 1) && (sellQtyByCompanyMultiset.size() == 1)) {
            auto sellIterator = sellQtyByCompanyMultiset.begin();
            auto buyIterator = buyQtyByCompanyMultiset.begin();

            if (buyIterator->company == sellIterator->company) {
                return;
            }
        } else {
            return; 
        }
    }

    if ((buyQtyByCompanyMultiset.size() == 0) || (sellQtyByCompanyMultiset.size() == 0)) {
        return; 
    }

    // the last, in std::multiset, means the highest qty
    auto lastMatchableSellElementIterator = sellQtyByCompanyMultiset.rbegin();
    auto lastMatchableBuyElementIterator = buyQtyByCompanyMultiset.rbegin();

    if (lastMatchableSellElementIterator->company == lastMatchableBuyElementIterator->company) {
        if (buyQtyByCompanyMultiset.size() >= 2) {
            lastMatchableBuyElementIterator = std::next(lastMatchableBuyElementIterator);
        } else {
            if (sellQtyByCompanyMultiset.size() >= 2) {
                lastMatchableSellElementIterator = std::next(lastMatchableSellElementIterator);
            }
        }
    }

    QtyByCompany lastMatchableSellElement(lastMatchableSellElementIterator->company,
        lastMatchableSellElementIterator->quantity);
    QtyByCompany lastMatchableBuyElement(lastMatchableBuyElementIterator->company,
        lastMatchableBuyElementIterator->quantity);
    sellQtyByCompanyMultiset.erase(--lastMatchableSellElementIterator.base());
    buyQtyByCompanyMultiset.erase(--lastMatchableBuyElementIterator.base());

    unsigned int match = std::min(lastMatchableSellElement.quantity, lastMatchableBuyElement.quantity);
    matches += match;
    std::cout << "Match: Qty: " << match << std::endl;
    std::cout << "Sell:" << lastMatchableSellElement.company << ":" << lastMatchableSellElement.quantity << std::endl;
    std::cout << "Buy:" << lastMatchableBuyElement.company << ":" << lastMatchableBuyElement.quantity << std::endl;

    lastMatchableSellElement.quantity -= match;
    lastMatchableBuyElement.quantity -= match;

    if (lastMatchableSellElement.quantity != 0) {
        sellQtyByCompanyMultiset.insert(lastMatchableSellElement);
    }

    if (lastMatchableBuyElement.quantity != 0) {
        buyQtyByCompanyMultiset.insert(lastMatchableBuyElement);
    }

    return greedyRecursiveAlgorithmToGetMaximumMatches(buyQtyByCompanyMultiset, sellQtyByCompanyMultiset, matches);
}
