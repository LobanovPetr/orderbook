#include <exception>
#include <iostream>
#include <numeric>
#include <string>
#include <memory>
#include <stdexcept>
#include <unistd.h>
#include <vector>
#include <optional>
#include <chrono>
#include <thread>

#include <order_book/order_book.h>
#include <curl_wrapper/curl_wrapper.h>

void PrintUsage() {
    std::cout << "./orderbook <pair> <limit>" << std::endl;
    std::cout << "Example: ./orderbook BTCUSDT 5" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        PrintUsage();
        return 0;
    }

    std::string pair;
    std::string limit;

    pair = argv[1];
    limit = argv[2];

    const std::string url = "https://api.binance.com/api/v3/depth?"
                            "symbol=" + pair + "&"
                            "limit=" + limit;

    std::chrono::milliseconds timespan(500); // or whatever

    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(4);

    Curl curl;

    while (true) {
        std::this_thread::sleep_for(timespan);
        try {
            auto response = curl.Get(url);

            if (auto code = response.GetResponseCode(); code != 200) {
                std::cout << "Bad response code: " << code << std::endl;
                return 0;
            }

            auto orderBook = ParseOrderBook(response.GetResponseBody());
            if (orderBook.Empty()) {
                std::cout << "Empty orderbook." << std::endl;
                return 0;
            }

            if (auto bestAsk = orderBook.GetBestAskPrice()) {
                std::cout << "BestAsk: " << *bestAsk << std::endl;
            }
            if (auto bestBid = orderBook.GetBestBidPrice()) {
                std::cout << "BestBid: " << *bestBid << std::endl;
            }
            if (auto midPrice = orderBook.GetMidPrice()) {
                std::cout << "MidPrice: " << *midPrice << std::endl;
            }
            if (auto spread = orderBook.GetSpread()) {
                std::cout << "Spread: " << *spread << std::endl;
            }
            std::cout << "Ask depth: " << orderBook.GetAskDepth() << std::endl;
            std::cout << "Bid depth: " << orderBook.GetBidDepth() << std::endl;
            std::cout << "Order Book Imbalance: " << orderBook.GetImbalance() << std::endl;

            std::cout << std::endl << std::endl;
        } catch (const CurlException& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}