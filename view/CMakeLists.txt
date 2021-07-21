
# view lib

add_library(view GameGUI.cpp ViewCells.cpp)
find_package(FLTK REQUIRED)
target_link_libraries(view common ${FLTK_LIBRARIES})
target_include_directories(view 
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} 
PRIVATE ${FLTK_INCLUDE_DIR})

target_precompile_headers(view
    PRIVATE
    <FL/Fl.H> <FL/Fl_Box.H> <FL/Fl_Window.H> <FL/fl_draw.H> <FL/Fl_Button.H>
    <FL/fl_draw.H> <FL/Fl_Float_Input.H> <Fl/Fl_PNG_Image.H>
)
