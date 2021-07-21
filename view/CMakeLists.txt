
# view lib
add_library(view GameGUI.cpp ViewCells.cpp)
target_link_libraries(view common fltk fltk_images)
add_link_options(-static)
target_include_directories(view INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(view
    PUBLIC
    <FL/Fl.H> <FL/Fl_Box.H> <FL/Fl_Window.H> <FL/fl_draw.H> <FL/Fl_Button.H>
    <FL/fl_draw.H>
)
