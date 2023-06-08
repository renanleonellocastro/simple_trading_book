#include <map>
#include <set>
#include <unordered_map>

#include "OrderCache.h"
#include "QtyByCompany.h"

#pragma once

/**
 * @class QtyByCompanyBySecIdManager
 * @brief Manage quantity by company and security ID.
 *
 * This class provides an in-memory cache of order objects and supports adding orders,
 * removing orders, and calculating the total quantity that can be matched for a given security ID.
 * The reason for this class is to be faster on getting matching size for security.
 */
class QtyByCompanyBySecIdManager
{
public:
    /**
     * @brief Default constructor.
     */
    QtyByCompanyBySecIdManager();

    /**
     * @brief Default destructor.
     */
    ~QtyByCompanyBySecIdManager();

    /**
     * @brief Adds a new order to the cache.
     * This function adds a new order to the cache and updates the quantity by company and security ID.
     * @param order The order to add.
     * @throw std::runtime_error if an error occurs.
     */
    void addOrder(const Order& order);

    /**
     * @brief Removes an order from the cache.
     * This function removes an order from the cache and updates the quantity by
     * company and security ID accordingly.
     * @param order The order to remove.
     * @throw std::runtime_error if an error occurs.
     */
    void cancelOrder(const Order& order);

    /**
     * @brief Calculates the total quantity that can be matched for a given security ID.
     * This function calculates and returns the total quantity that can be matched
     * for the specified security ID.
     * @param securityId The security ID for which to calculate the matching size.
     * @return The total quantity that can be matched.
     */
    unsigned int getMatchingSizeForSecurity(const std::string& securityId);

private:
    void eraseOrderFromMap(std::unordered_map<std::string, std::unordered_map<std::string,
        unsigned int>>& map, const Order& order);

    std::multiset<QtyByCompany> getMultisetFromMap(const std::unordered_map<std::string, std::uint32_t>& map);
    
    void greedyRecursiveAlgorithmToGetMaximumMatches(std::multiset<QtyByCompany>& buyQtyByCompanyMultiset,
        std::multiset<QtyByCompany>& sellQtyByCompanyMultiset, unsigned int& matches);
    
    bool shouldStopRecursion(std::multiset<QtyByCompany>& buyQtyByCompanyMultiset,
        std::multiset<QtyByCompany>& sellQtyByCompanyMultiset);

    std::tuple<std::multiset<QtyByCompany>::reverse_iterator, std::multiset<QtyByCompany>::reverse_iterator> 
        getLastMatchableIterator(std::multiset<QtyByCompany>& buyQtyByCompanyMultiset,
        std::multiset<QtyByCompany>& sellQtyByCompanyMultiset);
    
    unsigned int getMatchSizeAndUpdateTotalMatches(std::tuple<std::multiset<QtyByCompany>::
        reverse_iterator, std::multiset<QtyByCompany>::reverse_iterator>& lastMatchableTuple,
        unsigned int& matches);

    std::tuple<QtyByCompany, QtyByCompany> getUpdatedQuantityElements(std::tuple<std::multiset<
        QtyByCompany>::reverse_iterator, std::multiset<QtyByCompany>::reverse_iterator>& lastMatchableTuple,
        unsigned int matchSize);
    
    void updateQtyByCompanyMultiset(std::multiset<QtyByCompany>& qtyByCompanyMultiset,
        std::multiset<QtyByCompany>::reverse_iterator& lastMatchableIterator,
        QtyByCompany& updatedQuantityElement);

private:
    std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>> m_buyQtyByCompanyBySecIdMap;
    std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>> m_sellQtyByCompanyBySecIdMap; 
};
