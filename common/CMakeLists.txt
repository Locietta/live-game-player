
# every common libs compiled to one

add_subdirectory(notification)
add_library(common common.cpp)
target_link_libraries(common Notification)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
