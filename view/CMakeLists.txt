
# view lib
add_library(view GameGUI.cpp ViewCells.cpp)
target_link_libraries(view common fltk)
target_include_directories(view INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

