cmake_minimum_required(VERSION 3.0.0)
project(live-game VERSION 0.1.0)

SET(CXX_STANDARD 17)

include(CTest)
enable_testing()

add_subdirectory(common)
add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(viewmodel)

add_executable(live-game main.cpp)
target_link_libraries(live-game PUBLIC Notification view viewmodel model)
target_include_directories(live-game PUBLIC "${PROJECT_BINARY_DIR}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
