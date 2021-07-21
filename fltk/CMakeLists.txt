set(FLTK_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

set(FLTK_LIB_PREFIX ${CMAKE_CURRENT_LIST_DIR}/lib/windows/x64)

if(WIN32)
    if(NOT CYGWIN)
        if(BORLAND)
            set( FLTK_PLATFORM_DEPENDENT_LIBS import32 )
        else()
            set( FLTK_PLATFORM_DEPENDENT_LIBS wsock32 comctl32 )
        endif()
    endif()
endif()

set(FLTK_MSVC_NAMES "fltk" "fltk_z" "fltk_jpeg" "fltk_images" "fltk_gl" "fltk_png" "fltk_forms")
set(FLTK_MSVC_DEBUG_NAMES "fltkd" "fltk_zd" "fltk_jpegd" "fltk_imagesd" "fltk_gld" "fltk_pngd" "fltk_formsd")

if (MSVC)
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(FLTK_NAMES ${FLTK_MSVC_DEBUG_NAMES})
    else()
        set(FLTK_NAMES ${FLTK_MSVC_NAMES})
    endif()
endif()

add_library(FLTK_LIBS empty.cpp)
target_link_directories(FLTK_LIBS INTERFACE "${FLTK_LIB_PREFIX}/${CMAKE_BUILD_TYPE}")
target_link_libraries(FLTK_LIBS INTERFACE ${FLTK_NAMES} ${FLTK_PLATFORM_DEPENDENT_LIBS})
target_include_directories(FLTK_LIBS INTERFACE ${FLTK_INCLUDE_DIR})
