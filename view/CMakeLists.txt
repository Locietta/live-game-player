
# view lib
add_library(view GameGUI.cpp ViewCells.cpp)
target_link_libraries(view Notification)
target_include_directories(view INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

