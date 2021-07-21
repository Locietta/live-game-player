cmake_minimum_required(VERSION 3.18.0)
project(live-game VERSION 0.1.0)

SET(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

if (MSVC)
add_subdirectory(fltk)
endif()

add_subdirectory(common)
add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(viewmodel)
add_subdirectory(app)

add_executable(live-game main.cpp)
target_link_libraries(live-game PUBLIC app)
target_include_directories(live-game PUBLIC "${PROJECT_BINARY_DIR}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
