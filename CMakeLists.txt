cmake_minimum_required(VERSION 3.0.0)
project(live-game VERSION 0.1.0)

SET(CXX_STANDARD 17)

include(CTest)
enable_testing()

add_executable(live-game main.cpp Notification.cpp refPtr.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
