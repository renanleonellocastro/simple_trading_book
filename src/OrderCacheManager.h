#include <vector>
#include <unordered_map>

#include "OrderCache.h"

#pragma once

/**
 * @class OrderCacheManager
 * @brief Manages the OrderCache during operations.
 *
 * This class is responsible for managing the OrderCache by adding,
 * removing, and retrieving orders from the cache.
 */
class OrderCacheManager
{
public:
    /**
     * @brief Default constructor.
     */
    OrderCacheManager();

    /**
     * @brief Default destructor.
     */
    ~OrderCacheManager();

    /**
     * @brief Adds a new order to the cache.
     * This function adds a new order to the OrderCache.
     * @param order The order to add.
     * @throw std::runtime_error if an error occurs.
     */
    void addOrder(const Order& order);

    /**
     * @brief Removes an order from the cache.
     * This function removes an order with the specified orderId from the OrderCache.
     * @param orderId The ID of the order to remove.
     * @return The removed order.
     * @throw std::runtime_error if an error occurs.
     */
    Order cancelOrder(const std::string& orderId);

    /**
     * @brief Retrieves all orders in the cache.
     * This function retrieves all orders currently stored in the OrderCache.
     * @return A vector containing all orders in the cache.
     */
    std::vector<Order> getAllOrders() const;

private:
    std::unordered_map<std::string, Order> m_orderCacheMap;
};
