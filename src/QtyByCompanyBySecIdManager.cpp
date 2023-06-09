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
    if (shouldStopRecursion(buyQtyByCompanyMultiset, sellQtyByCompanyMultiset)) {
        return;
    }

    auto lastMatchableIteratorTuple = getLastMatchableIterator(buyQtyByCompanyMultiset,
        sellQtyByCompanyMultiset);

    unsigned int match = getMatchSizeAndUpdateTotalMatches(lastMatchableIteratorTuple, matches);

    auto updatedQuantitiesElementTuple = getUpdatedQuantityElements(lastMatchableIteratorTuple, match);

    updateQtyByCompanyMultiset(sellQtyByCompanyMultiset, std::get<0>(lastMatchableIteratorTuple),
        std::get<0>(updatedQuantitiesElementTuple));
    
    updateQtyByCompanyMultiset(buyQtyByCompanyMultiset, std::get<1>(lastMatchableIteratorTuple),
        std::get<1>(updatedQuantitiesElementTuple));

    return greedyRecursiveAlgorithmToGetMaximumMatches(buyQtyByCompanyMultiset, sellQtyByCompanyMultiset, matches);
}

bool QtyByCompanyBySecIdManager::shouldStopRecursion(std::multiset<QtyByCompany>& buyQtyByCompanyMultiset,
    std::multiset<QtyByCompany>& sellQtyByCompanyMultiset)
{
    if ((buyQtyByCompanyMultiset.size() == 1) && (sellQtyByCompanyMultiset.size() == 1)) {
        if (buyQtyByCompanyMultiset.begin()->company == sellQtyByCompanyMultiset.begin()->company) {
            return true;
        }
    }

    if ((buyQtyByCompanyMultiset.size() == 0) || (sellQtyByCompanyMultiset.size() == 0)) {
        return true; 
    }

    return false;
}

std::tuple<std::multiset<QtyByCompany>::reverse_iterator, std::multiset<QtyByCompany>::reverse_iterator> 
    QtyByCompanyBySecIdManager::getLastMatchableIterator(std::multiset<QtyByCompany>& buyQtyByCompanyMultiset,
    std::multiset<QtyByCompany>& sellQtyByCompanyMultiset)
{
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
    return std::tuple(lastMatchableSellElementIterator, lastMatchableBuyElementIterator);
}

unsigned int QtyByCompanyBySecIdManager::getMatchSizeAndUpdateTotalMatches(std::tuple<
    std::multiset<QtyByCompany>::reverse_iterator, std::multiset<QtyByCompany>::
    reverse_iterator>& lastMatchableTuple, unsigned int& matches)
{
    auto lastMatchableSellElementIterator = std::get<0>(lastMatchableTuple);
    auto lastMatchableBuyElementIterator = std::get<1>(lastMatchableTuple);

    unsigned int match = std::min(lastMatchableSellElementIterator->quantity,
        lastMatchableBuyElementIterator->quantity);
    matches += match;

    return match;
}

std::tuple<QtyByCompany, QtyByCompany> QtyByCompanyBySecIdManager::getUpdatedQuantityElements(
    std::tuple<std::multiset<QtyByCompany>::reverse_iterator, std::multiset<QtyByCompany>::
    reverse_iterator>& lastMatchableTuple, unsigned int matchSize)
{
    QtyByCompany lastMatchableSellElement(std::get<0>(lastMatchableTuple)->company,
        std::get<0>(lastMatchableTuple)->quantity);

    QtyByCompany lastMatchableBuyElement(std::get<1>(lastMatchableTuple)->company,
        std::get<1>(lastMatchableTuple)->quantity);

    lastMatchableSellElement.quantity -= matchSize;
    lastMatchableBuyElement.quantity -= matchSize;

    return std::make_tuple(lastMatchableSellElement, lastMatchableBuyElement);
}

void QtyByCompanyBySecIdManager::updateQtyByCompanyMultiset(std::multiset<QtyByCompany>&
    qtyByCompanyMultiset, std::multiset<QtyByCompany>::reverse_iterator&
    lastMatchableIterator, QtyByCompany& updatedQuantityElement)
{
    qtyByCompanyMultiset.erase(--lastMatchableIterator.base());

    if (updatedQuantityElement.quantity != 0) {
        qtyByCompanyMultiset.insert(updatedQuantityElement);
    }
}
