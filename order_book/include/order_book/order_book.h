#pragma once
#include <nlohmann/json.hpp>
#include <optional>
#include <vector>

struct Order {
    double price;
    double quantity;
};

class OrderBook {
private:
    std::vector<Order> Asks;
    std::vector<Order> Bids;
public:

    std::optional<double> GetBestAskPrice() const;
    std::optional<double> GetBestBidPrice() const;
    std::optional<double> GetMidPrice() const;
    std::optional<double> GetSpread() const;

    double GetAskDepth() const;
    double GetBidDepth() const;
    double GetImbalance() const;

    bool Empty() const;

    friend OrderBook ParseOrderBook(const std::string &response);
};

OrderBook ParseOrderBook(const std::string &response);