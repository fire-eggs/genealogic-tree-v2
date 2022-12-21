cmake_minimum_required(VERSION 3.1)
project(zdolr2)

add_compile_options( "-fexceptions" "-fopenmp" "-DFLTK_USE_SVG" "-D__CLION_IDE__" )

#set (CMAKE_CXX_STANDARD 11)
#set (CMAKE_BUILD_TYPE "Debug" CACHE STRING "blah" FORCE)
#set (CMAKE_CXX_FLAGS "-fpermissive")

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} /home/kevin/fltk-filetable-master/fltk )

add_executable( zdolr2 zdolr2.cpp )

find_library(FLTK fltk /home/kevin/fltk-filetable-master/build/lib)
#find_library(FLTK_IMG fltk_images /home/kevin/proj/fltk/fltk/lib)
# Using own [modified] PNG library to prevent output to console
#find_library(FLTK_PNG fltk_png /home/kevin/proj/fltk/fltk/lib)

set(LINK_FLAGS -no-pie -fopenmp -lX11 -lXext -lm -ldl -lXinerama -lXcursor
        -lXrender -lXfixes -lz -lXft -lfontconfig -pthread
        -lpthread 
        )

target_link_libraries(zdolr2 LINK_PUBLIC ${FLTK} ${LINK_FLAGS} )
