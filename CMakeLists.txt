cmake_minimum_required(VERSION 3.10)

# Название проекта
project(orderbook)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    curl
    URL https://curl.se/download/curl-8.5.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP true
    OVERRIDE_FIND_PACKAGE # this one
)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.0
)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(curl json googletest)


add_executable(orderbook main.cpp)
add_subdirectory(curl_wrapper)
add_subdirectory(order_book)

target_link_libraries(orderbook
    PRIVATE
        curl_wrapper
        order_book
)



set(CMAKE_EXPORT_COMPILE_COMMANDS ON)