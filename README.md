# Trade Book - In-Memory Order Cache

This project is an implementation of an in-memory trade book that manages orders and provides various operations on the orders. It includes a class called `OrderCacheImp` that implements the `OrderCacheInterface`, which defines the interface for interacting with the order cache.

## OrderCacheInterface

The `OrderCacheInterface` is an abstract class that defines the following methods:

<pre><div class="bg-black rounded-md mb-4"><div class="flex items-center relative text-gray-200 bg-gray-800 px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>cpp</span><button class="flex ml-auto gap-2"><svg stroke="currentColor" fill="none" stroke-width="2" viewBox="0 0 24 24" stroke-linecap="round" stroke-linejoin="round" class="h-4 w-4" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg>Copy code</button></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-cpp">class OrderCacheInterface
{
public:
    virtual void addOrder(Order order) = 0;
    virtual void cancelOrder(const std::string& orderId) = 0;
    virtual void cancelOrdersForUser(const std::string& user) = 0;
    virtual void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty) = 0;
    virtual unsigned int getMatchingSizeForSecurity(const std::string& securityId) = 0;
    virtual std::vector<Order> getAllOrders() const = 0;
};
</code></div></div></pre>

These methods allow adding orders, cancelling orders by ID, cancelling orders by user, cancelling orders by security ID with a minimum quantity, retrieving the matching size for a security ID, and getting all orders in the cache.

## OrderCacheImp

The `OrderCacheImp` class is an implementation of the `OrderCacheInterface`. It provides an in-memory cache of order objects and supports various operations on the orders.

### Features and Highlights

* **Multi-thread Consumer Support** : The implementation supports multiple threads consuming the order cache concurrently by utilizing a mutex to ensure thread safety.
* **Platform and Compilation** : The code was developed in a Linux environment and compiled using `g++` with C++17 support. The project includes a Makefile for easy compilation.

### Compilation and Unit Tests

To compile the project and run the unit tests, follow these steps:

1. Make sure you have `g++` and `make` installed on your Linux machine.
2. Navigate to the project directory containing the Makefile and source files.
3. Run the following command in the terminal to compile the project:

   <pre><div class="bg-black rounded-md mb-4"><div class="flex items-center relative text-gray-200 bg-gray-800 px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>shell</span><button class="flex ml-auto gap-2"><svg stroke="currentColor" fill="none" stroke-width="2" viewBox="0 0 24 24" stroke-linecap="round" stroke-linejoin="round" class="h-4 w-4" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg>Copy code</button></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-shell">make
   </code></div></div></pre>
4. After successful compilation, execute the unit tests by running the following command:

   <pre><div class="bg-black rounded-md mb-4"><div class="flex items-center relative text-gray-200 bg-gray-800 px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>shell</span><button class="flex ml-auto gap-2"><svg stroke="currentColor" fill="none" stroke-width="2" viewBox="0 0 24 24" stroke-linecap="round" stroke-linejoin="round" class="h-4 w-4" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg>Copy code</button></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-shell">./unittest
   </code></div></div></pre>

   The unit tests cover various scenarios and ensure the correctness of the implemented methods.

### Solution Approach

* **Greedy Approach for getMatchingSizeForSecurity** : The `getMatchingSizeForSecurity` method is implemented using a greedy approach. It calculates and returns the total quantity that can be matched for a given security ID.
* **Performance and Memory Considerations** : The implementation prioritizes performance over memory consumption. To optimize execution speed, several buffers with different data structures are used to store the same data but in different ways. These buffers are managed and synchronized by their respective manager classes.

### Unit Testing Approach

* **Pure C++ Unit Tests** : The unit tests were implemented without using any external test framework. This approach simplifies compilation and integration with different operating systems. Moreover, it demonstrates the knowledge of pure C++ and reduces dependencies.
* **Coverage of Scenarios** : The unit tests cover both best and worst case scenarios, ensuring the correctness and robustness of the implemented methods.
