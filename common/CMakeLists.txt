
# every common libs compiled to one

add_subdirectory(Notification)
add_library(Notification ./notification/Notification.cpp)
target_include_directories(Notification INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/notification ${CMAKE_CURRENT_SOURCE_DIR})

add_library(common common.cpp)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
