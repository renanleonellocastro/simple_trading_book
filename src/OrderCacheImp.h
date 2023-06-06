#include <mutex>
#include <vector>
#include <unordered_map>

#include "OrderCacheManager.h"
#include "OrdersByUserManager.h"
#include "QtyByCompanyBySecIdManager.h"
#include "OrderQtyByOrderIdBySecIdManager.h"

#pragma once

/**
 * @class OrderCacheImp
 * @brief Implementation of the OrderCacheInterface.
 *
 * This class provides an in-memory cache of order objects and supports adding orders,
 * removing orders, get all orders and matching buy and sell orders.
 */
class OrderCacheImp : public OrderCacheInterface
{
public:
    /**
     * @brief Default constructor.
     */
    OrderCacheImp();

    /**
     * @brief Default destructor.
     */
    ~OrderCacheImp();

    /**
     * @brief Adds a new order to the cache.
     * @param order The order to add.
     */
    void addOrder(Order order) override;

    /**
     * @brief Removes an order from the cache.
     * @param orderId The ID of the order to remove.
     */
    void cancelOrder(const std::string& orderId) override;

    /**
     * @brief Cancel all orders placed by a specific user.
     * @param user The user whose orders should be canceled.
     */
    void cancelOrdersForUser(const std::string& user) override;

    /**
     * @brief Cancels all orders for a specific security ID with a minimum quantity.
     * @param securityId The security ID of the orders to cancel.
     * @param minQty The minimum quantity threshold.
     */
    void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty) override;

    /**
     * @brief Calculates the total quantity that can be matched for a given security ID.
     * @param securityId The security ID for which to calculate the matching size.
     * @return The total quantity that can be matched.
     */
    unsigned int getMatchingSizeForSecurity(const std::string& securityId) override;

    /**
     * @brief Retrieves all orders in the cache.
     * @return A vector containing all orders in the cache.
     */
    std::vector<Order> getAllOrders() const override;

private:
    mutable std::mutex m_mutex;
    OrderCacheManager m_orderCacheManager;
    OrdersByUserManager m_ordersByUserManager;
    QtyByCompanyBySecIdManager m_qtyByCompanyBySecIdManager;
    OrderQtyByOrderIdBySecIdManager m_orderQtyByOrderIdBySecIdManager;
};
