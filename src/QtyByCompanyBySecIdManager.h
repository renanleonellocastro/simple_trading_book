#include <map>
#include <set>
#include <unordered_map>

#include "OrderCache.h"
#include "QtyByCompany.h"

#pragma once

/**
 * @class QtyByCompanyBySecIdManager
 * @brief Manages quantity by company and security ID.
 *
 * The QtyByCompanyBySecIdManager class provides an in-memory cache of order objects
 * and supports adding orders, removing orders, and calculating the total quantity
 * that can be matched for a given security ID. This class is designed for faster
 * retrieval of matching sizes for securities.
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
     * This function adds a new order to the cache and updates the quantity by company
     * and security ID.
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
    /**
     * @brief Erases an order from the quantity map.
     * This function erases an order from the quantity map based on the order's details.
     * @param map The quantity map to update.
     * @param order The order to erase.
     */
    void eraseOrderFromMap(std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>>& map,
        const Order& order);

    /**
     * @brief Converts a quantity map to a multiset of QtyByCompany objects.
     * This function converts a quantity map to a multiset of QtyByCompany objects,
     * which is used for efficient retrieval and matching calculations.
     * @param map The quantity map to convert.
     * @return The resulting multiset of QtyByCompany objects.
     */
    std::multiset<QtyByCompany> getMultisetFromMap(const std::unordered_map<std::string, std::uint32_t>& map);

    /**
     * @brief Implements a greedy algorithm to find maximum matches.
     * This function implements a greedy algorithm to find the maximum
     * matches between buy and sell orders in the multiset representation.
     * @param buyQtyByCompanyMultiset The multiset of buy orders.
     * @param sellQtyByCompanyMultiset The multiset of sell orders.
     * @param matches The total matches found.
     */
    void greedyRecursiveAlgorithmToGetMaximumMatches(std::multiset<QtyByCompany>& buyQtyByCompanyMultiset,
        std::multiset<QtyByCompany>& sellQtyByCompanyMultiset, unsigned int& matches);
    
    /**
     * @brief Checks if the recursion should stop based on the order quantities.
     * This function checks if the recursion should stop based on the order quantities.
     * The recursion should stop if either the buyQtyByCompanyMultiset or the
     * sellQtyByCompanyMultiset is empty or if they are size 1 and same company.
     * @param buyQtyByCompanyMultiset The multiset of buy orders.
     * @param sellQtyByCompanyMultiset The multiset of sell orders.
     * @return True if the recursion should stop, false otherwise.
     */
    bool shouldStopRecursion(std::multiset<QtyByCompany>& buyQtyByCompanyMultiset,
        std::multiset<QtyByCompany>& sellQtyByCompanyMultiset);

    /**
     * @brief Retrieves the last matchable iterator from the multiset.
     * This function retrieves the last matchable iterator from the multiset,
     * which represents the highest element with different companies that can be matched.
     * @param buyQtyByCompanyMultiset The multiset of buy orders.
     * @param sellQtyByCompanyMultiset The multiset of sell orders.
     * @return A tuple containing the last matchable iterator for the buy and sell orders.
     */
    std::tuple<std::multiset<QtyByCompany>::reverse_iterator, std::multiset<QtyByCompany>::reverse_iterator> 
        getLastMatchableIterator(std::multiset<QtyByCompany>& buyQtyByCompanyMultiset,
        std::multiset<QtyByCompany>& sellQtyByCompanyMultiset);

    /**
     * @brief Gets the size of the current match and updates the total matches count.
     * This function gets the size of the match and updates the total matches count
     * by incrementing it with the match size.
     * @param lastMatchableTuple A tuple containing the last matchable iterator for the buy and sell orders.
     * @param matches The total matches found so far.
     * @return The size of the match.
     */
    unsigned int getMatchSizeAndUpdateTotalMatches(std::tuple<std::multiset<QtyByCompany>::
        reverse_iterator, std::multiset<QtyByCompany>::reverse_iterator>& lastMatchableTuple,
        unsigned int& matches);

    /**
     * @brief Gets the updated quantity elements after a match.
     * This function gets the updated quantity elements after a match by
     * decrementing the matched quantity from the corresponding orders.
     * @param lastMatchableTuple A tuple containing the last matchable iterator for the buy and sell orders.
     * @param matchSize The size of the match.
     * @return A tuple containing the updated buy and sell quantity elements.
     */
    std::tuple<QtyByCompany, QtyByCompany> getUpdatedQuantityElements(std::tuple<std::multiset<
        QtyByCompany>::reverse_iterator, std::multiset<QtyByCompany>::reverse_iterator>& lastMatchableTuple,
        unsigned int matchSize);

    /**
     * @brief Updates the quantity multiset after a match.
     * This function updates the quantity multiset after a match by erasing
     * the matched elements and inserting the updated quantity elements.
     * @param qtyByCompanyMultiset The quantity multiset to update.
     * @param lastMatchableIterator The last matchable iterator for the buy or sell orders.
     * @param updatedQuantityElement The updated quantity element after a match.
     */
    void updateQtyByCompanyMultiset(std::multiset<QtyByCompany>& qtyByCompanyMultiset,
        std::multiset<QtyByCompany>::reverse_iterator& lastMatchableIterator,
        QtyByCompany& updatedQuantityElement);

private:
    std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>> m_buyQtyByCompanyBySecIdMap;
    std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>> m_sellQtyByCompanyBySecIdMap; 
};
