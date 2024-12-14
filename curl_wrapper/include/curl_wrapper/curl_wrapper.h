#pragma once
#include <curl/curl.h>
#include <string>
#include <exception>
#include <stdexcept>

/**
 * @brief Class for storing HTTP response data
 */
class CurlResponse {
public:
    /**
     * @brief Constructor
     * @param responseCode HTTP response code
     * @param responseBody Response body content
     */
    CurlResponse(int responseCode, std::string responseBody) 
        : responseCode_(responseCode)
        , responseBody_(std::move(responseBody))
    {}

    /**
     * @brief Get response code
     * @return HTTP response code
     */
    int GetResponseCode() const {
        return responseCode_;
    };

    /**
     * @brief Get response body
     * @return String containing response body
     */
    const std::string& GetResponseBody() const {
        return responseBody_;
    };
private:
    int responseCode_;
    std::string responseBody_;
};

/**
 * @brief Exception class for curl-related errors
 */
class CurlException : public std::runtime_error {
public:
    /**
     * @brief Constructor
     * @param message Error message
     */
    CurlException(const std::string& message) : std::runtime_error(message) {};
};

/**
 * @brief Wrapper class for libcurl functionality
 */
class Curl {
public:
    /**
     * @brief Constructor that initializes curl library
     * @throw CurlException on initialization failure
     */
    Curl();

    /**
     * @brief Destructor that cleans up curl resources
     */
    ~Curl();

    /**
     * @brief Perform GET request to specified URL
     * @param url Target URL for the request
     * @return CurlResponse object containing response code and body
     * @throw CurlException on request failure
     */
    CurlResponse Get(const std::string &url) const;
private:
    CURL* Curl_;
};