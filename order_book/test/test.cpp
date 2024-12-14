#include <gtest/gtest.h>
#include <order_book/order_book.h>

TEST(OrderBook, Base) {
    auto OrderBook = ParseOrderBook("{\"asks\": [[\"1\", \"1\"], [\"2\", \"3\"]], \"bids\": [[\"3\", \"3\"], [\"4\", \"5\"]]}");
}
