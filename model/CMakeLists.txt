
# model lib
add_library(model model.cpp)
target_link_libraries(model PUBLIC common)
target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
