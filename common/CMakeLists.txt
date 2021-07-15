
# every common libs compiled to one

add_subdirectory(Notification)
add_library(Notification ./notification/Notification.cpp)
target_include_directories(Notification INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/notification ${CMAKE_CURRENT_SOURCE_DIR})
