
# viewmodel lib
add_library(viewmodel viewmodel.cpp)
target_link_libraries(viewmodel PUBLIC common)
target_include_directories(viewmodel INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
