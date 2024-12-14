#include <gtest/gtest.h>
#include <curl_wrapper/curl_wrapper.h>

class CurlFixture : public ::testing::Test
{
protected:
	void SetUp() {}
	void TearDown() {}
	Curl curl;
};

TEST_F(CurlFixture, Base) {

    auto response = curl.Get("https://example.com");
    EXPECT_EQ(200, response.GetResponseCode());
}
