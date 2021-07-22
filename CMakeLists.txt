cmake_minimum_required(VERSION 3.18.0)
project(live_game VERSION 0.1.0)

SET(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

configure_file(config.h.in config.h)
include_directories("${PROJECT_BINARY_DIR}")

if (MSVC)
add_subdirectory(fltk)
endif()

add_subdirectory(common)
add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(viewmodel)
add_subdirectory(app)

add_executable(live_game main.cpp)
target_link_libraries(live_game PUBLIC app)
target_include_directories(live_game PUBLIC "${PROJECT_BINARY_DIR}")

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "Live-Game-Player")
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DIRECTORY ${PROJECT_SOURCE_DIR}/pack)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Live Game Player - Our simple life game simulator based on fltk")
set(CPACK_PACKAGE_VENDOR "https://gitee.com/Locietta/live-game-player")
include(CPack)
