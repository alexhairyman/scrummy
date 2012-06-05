# Nothin Here yet
cmake_minimum_required(VERSION 2.8)
project(scrummy)

message("Current Version: ${M_VER}")

set(M_VER "0.0.3")
add_definitions("-I.." "-I.")
list(APPEND
  BUILTCOMPS
  "scrumcomps.cc" "scrummer2.cc" "drupalauth.cc"
)

add_library("SCRUMS" SHARED ${BUILTCOMPS})
add_library("SCRUMA" STATIC ${BUILTCOMPS})

set_target_properties("SCRUMS"
  PROPERTIES
  SUFFIX ".so"
  PREFIX "lib"
  OUTPUT_NAME "scrummy"
)

set_target_properties("SCRUMA"
  PROPERTIES
  SUFFIX ".a"
  PREFIX "lib"
  OUTPUT_NAME "scrummy"
)

set(CMAKE_LINK_FLAGS "-L.")
add_executable("scrummer" "scrummer.cc")
target_link_libraries("scrummer" "SCRUMA" "fltk" "Xft" "ICE" "Xext" "X11" "boost_filesystem" "boost_system" "boost_iostreams" "curlpp" "Xinerama")
