#include <curl_wrapper/curl_wrapper.h>

// Функция для записи полученных данных в строку
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Curl::Curl() {
    if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
        throw CurlException("Failed to initialize CURL");
    }
    Curl_ = curl_easy_init();
    if (!Curl_) {
        curl_global_cleanup();
        throw CurlException("Failed to create CURL handle");
    }
}

CurlResponse Curl::Get(const std::string &url) const {
    std::string buffer;
    curl_easy_setopt(Curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(Curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(Curl_, CURLOPT_WRITEDATA, &buffer);
    CURLcode res = curl_easy_perform(Curl_);

    if (res != CURLE_OK) {
        throw CurlException("Error libcurl: " +
                            std::string(curl_easy_strerror(res)));
    }

    int responseCode = 0;
    curl_easy_getinfo(Curl_, CURLINFO_RESPONSE_CODE, &responseCode);

    return {responseCode, buffer};
}

Curl::~Curl() {
    if (Curl_) {
      curl_easy_cleanup(Curl_);
    }
    curl_global_cleanup();
}
