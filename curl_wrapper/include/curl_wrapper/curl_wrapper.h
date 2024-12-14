#pragma once
#include <curl/curl.h>
#include <string>
#include <exception>
#include <stdexcept>

class CurlException : public std::runtime_error {
public:
    CurlException(const std::string& message) : std::runtime_error(message) {}
};

class CurlResponse {
public:
    CurlResponse(int responseCode, std::string responseBody)
        : responseCode_(responseCode)
        , responseBody_(std::move(responseBody)) 
    {}

    int GetResponseCode() const {
        return responseCode_;
    }

    const std::string& GetResponseBody() const {
        return responseBody_; 
    }
private:
    int responseCode_;
    std::string responseBody_;
};

class Curl {
public:
    Curl();
    ~Curl();
    CurlResponse Get(const std::string &url) const;
  private:
    CURL* Curl_;
};