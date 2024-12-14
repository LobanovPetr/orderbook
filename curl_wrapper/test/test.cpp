#include <gtest/gtest.h>
#include <curl_wrapper/curl_wrapper.h>

TEST(Curl, Base) {
    Curl curl;

    auto response = curl.Get("https://example.com");
    EXPECT_EQ(200, response.GetResponseCode());
}
