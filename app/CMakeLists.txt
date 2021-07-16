
# model lib

add_library(app app.cpp)
target_link_libraries(app PUBLIC model viewmodel view)
target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
