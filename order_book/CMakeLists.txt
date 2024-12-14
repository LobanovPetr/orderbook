add_library(order_book STATIC order_book.cpp)
target_link_libraries(order_book nlohmann_json::nlohmann_json)
target_include_directories(order_book PUBLIC include)

add_subdirectory(test)