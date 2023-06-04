#include <vector>
#include <unordered_map>

#include "OrderCache.h"

#pragma once

/**
 * @class OrderQtyByOrderIdBySecIdManager
 * @brief Manages order quantity by order ID and security ID.
 *
 * This class provides an in-memory cache of order quantities and supports adding orders,
 * removing orders, and retrieving orders for a specific security ID with a minimum quantity.
 * The reason for this class is to be faster on retrieving the orders for secId with minimumQty.
 */
class OrderQtyByOrderIdBySecIdManager
{
public:
    /**
     * @brief Default constructor.
     */
    OrderQtyByOrderIdBySecIdManager();

    /**
     * @brief Default destructor.
     */
    ~OrderQtyByOrderIdBySecIdManager();

    /**
     * @brief Adds a new order to the cache.
     * This function adds a new order to the cache, storing its quantity based
     * on the order ID and security ID.
     * @param order The order to add.
     */
    void addOrder(const Order& order);

    /**
     * @brief Removes an order from the cache.
     * This function removes an order from the cache based on the provided order information.
     * @param order The order to remove.
     * @throw std::runtime_error if an error occurs.
     */
    void cancelOrder(const Order& order);

    /**
     * @brief Retrieves orders for a specific security ID with a minimum quantity.
     * This function retrieves a vector of order IDs for a given security ID that have a quantity
     * greater than or equal to the specified minimum quantity.
     * @param securityId The security ID of the orders to retrieve.
     * @param minQty The minimum quantity threshold.
     * @return A vector of order IDs matching the criteria.
     */
    std::vector<std::string> getOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty);

private:
    std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>> m_ordersQtyByOrderIdBySecIdMap;
};
