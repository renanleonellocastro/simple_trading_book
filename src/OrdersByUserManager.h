#include <vector>
#include <unordered_map>

#include "OrderCache.h"

#pragma once

/**
 * @class OrdersByUserManager
 * @brief Manages orders by user.
 *
 * This class provides an in-memory cache of order objects and supports adding orders,
 * removing orders, and retrieving all orders placed by a specific user.
 * The reason for this class is to be faster on retrieving all the user orders.
 */
class OrdersByUserManager
{
public:
    /**
     * @brief Default constructor.
     */
    OrdersByUserManager();

    /**
     * @brief Default destructor.
     */
    ~OrdersByUserManager();

    /**
     * @brief Adds a new order to the cache.
     * This function adds a new order to the cache, associating it with the corresponding user.
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
     * @brief Retrieves all orders placed by a specific user.
     * This function retrieves a vector of order IDs for all orders placed by the specified user.
     * @param user The user whose orders should be retrieved.
     * @return A vector of order IDs placed by the user.
     */
    std::vector<std::string> getAllUserOrders(const std::string& user);

private:
    std::unordered_map<std::string, std::unordered_map<std::string, bool>> m_ordersByUserMap;
};
