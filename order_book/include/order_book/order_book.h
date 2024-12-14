#pragma once
#include <nlohmann/json.hpp>
#include <optional>
#include <vector>

/**
 * @brief Order structure representing a single order in the order book
 */
struct Order {
    double price;    ///< Order price
    double quantity; ///< Order quantity
};

/**
 * @brief Class implementing order book functionality
 */
class OrderBook {
public:
    /**
     * @brief Get the best ask price
     * @return Optional price value. Returns std::nullopt if no asks available
     */
    std::optional<double> GetBestAskPrice() const;

    /**
     * @brief Get the best bid price
     * @return Optional price value. Returns std::nullopt if no bids available
     */
    std::optional<double> GetBestBidPrice() const;

    /**
     * @brief Get the mid price between best bid and ask
     * @return Optional mid price value. Returns std::nullopt if either bid or ask is missing
     */
    std::optional<double> GetMidPrice() const;

    /**
     * @brief Get the spread between best ask and bid prices
     * @return Optional spread value. Returns std::nullopt if either bid or ask is missing
     */
    std::optional<double> GetSpread() const;

    /**
     * @brief Get total ask depth
     * @return Sum of all ask quantities
     */
    double GetAskDepth() const;

    /**
     * @brief Get total bid depth
     * @return Sum of all bid quantities
     */
    double GetBidDepth() const;

    /**
     * @brief Calculate order book imbalance
     * @return Imbalance value in range [-1, 1]
     */
    double GetImbalance() const;

    /**
     * @brief Check if order book is empty
     * @return true if no orders present, false otherwise
     */
    bool Empty() const;
};

/**
 * @brief Parse JSON string into OrderBook object
 * @param response JSON string containing order book data
 * @return OrderBook object populated with data from JSON
 * @throw nlohmann::json::exception on JSON parsing error
 */
OrderBook ParseOrderBook(const std::string &response);