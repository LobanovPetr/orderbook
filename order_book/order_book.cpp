#include <order_book/order_book.h>

std::optional<double> OrderBook::GetBestAskPrice() const {
  if (!Asks.empty()) {
    return Asks[0].price;
  }
  return std::nullopt;
}
std::optional<double> OrderBook::GetBestBidPrice() const {
  if (!Bids.empty()) {
    return Bids[0].price;
  }
  return std::nullopt;
}
std::optional<double> OrderBook::GetMidPrice() const {
  auto bestBid = GetBestBidPrice();
  auto bestAsk = GetBestAskPrice();

  if (bestBid && bestAsk) {
    return (*bestAsk + *bestBid) / 2;
  }
  return std::nullopt;
}
std::optional<double> OrderBook::GetSpread() const {
  auto bestBid = GetBestBidPrice();
  auto bestAsk = GetBestAskPrice();

  if (bestBid && bestAsk) {
    return *bestAsk - *bestBid;
  }
  return std::nullopt;
}
double OrderBook::GetAskDepth() const {
  double depth{0.};
  for (const auto &ask : Asks) {
    depth += ask.quantity;
  }
  return depth;
}
double OrderBook::GetBidDepth() const {
  double depth{0.};
  for (const auto &ask : Bids) {
    depth += ask.quantity;
  }
  return depth;
}
double OrderBook::GetImbalance() const {
  double askDepth = GetAskDepth();
  double bidDepth = GetBidDepth();

  if (askDepth + bidDepth < 1e-5)
    return 0.;

  return (bidDepth - askDepth) / (bidDepth + askDepth);
}
OrderBook ParseOrderBook(const std::string &response) {
  using Json = nlohmann::json;
  Json j = Json::parse(response);
  OrderBook orderBook;

  for (const auto &bid : j["bids"]) {
    Order order;
    order.price = std::stod(bid[0].get<std::string>());
    order.quantity = std::stod(bid[1].get<std::string>());
    orderBook.Bids.push_back(order);
  }

  for (const auto &ask : j["asks"]) {
    Order order;
    order.price = std::stod(ask[0].get<std::string>());
    order.quantity = std::stod(ask[1].get<std::string>());
    orderBook.Asks.push_back(order);
  }

  return orderBook;
}
bool OrderBook::Empty() const {
    return Asks.empty() && Bids.empty(); 
}
