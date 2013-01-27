cmake_minimum_required(VERSION 2.6)
project(scrummy)

#set(CMAKE_CXX_FLAGS "-static")

set(CMAKE_CXX_COMPILER "clang++")

message("READ THE README!")
list(APPEND
  CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake"
)

set(Boost_USE_STATIC_LIBS "ON")
find_package(X11 REQUIRED COMPONENTS Xinerama Xft Xext X11 ICE)
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(FLTK REQUIRED)
find_package(CURLpp REQUIRED)
find_package(FontConfig REQUIRED)
#find_package(Poco REQUIRED COMPONENTS Zip Foundation)

add_definitions("-I.." "-I.")
list(APPEND
  BUILTCOMPS
  "scrumcomps.cc" "drupalauth.cc" "unzip.cc" "scrummer2.cc" "config.cc"
)

list(APPEND
  X11_LIBRARIES
  ${X11_Xft_LIB} ${X11_Xext_LIB} ${X11_Xinerama_LIB}
)


#yes, these are here for a reason, If someone wants a shared library, so no getting pissed at me
#add_library("SCRUMS" SHARED ${BUILTCOMPS})
add_library("SCRUMA" STATIC ${BUILTCOMPS})

#set_target_properties("SCRUMS"
#  PROPERTIES
#  SUFFIX ".so"
#  PREFIX "lib"
#  OUTPUT_NAME "scrummy"
#)


configure_file(config.json config.json COPYONLY)
add_custom_target(incerbincer SOURCES "scrummer2.hh")

set_target_properties("SCRUMA"
  PROPERTIES
  SUFFIX ".a"
  PREFIX "lib"
  OUTPUT_NAME "scrummy"
)


set(CMAKE_LINK_FLAGS "-L.")
add_executable("uztest" "test/unziptest.cc")
target_link_libraries("uztest" "archive" "SCRUMA" ${Boost_LIBRARIES})
add_executable("scrummer" "scrummer.cc")
target_link_libraries("scrummer" "SCRUMA" ${CURLPP_LIBRARIES} ${Boost_LIBRARIES} ${X11_LIBRARIES} ${FLTK_LIBRARIES} ${FONTCONFIG_LIBRARIES} "archive")
