add_library(curl_wrapper STATIC curl_wrapper.cpp)
target_link_libraries(curl_wrapper CURL::libcurl)
target_include_directories(curl_wrapper PUBLIC include)

add_subdirectory(test)