add_library(curl_wrapper STATIC curl_wrapper.cpp)
target_link_libraries(curl_wrapper CURL::libcurl)
target_include_directories(curl_wrapper PUBLIC include)

set_target_properties(curl_wrapper
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_subdirectory(test)