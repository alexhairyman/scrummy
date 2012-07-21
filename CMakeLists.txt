# Nothin Here yet
cmake_minimum_required(VERSION 2.6)
project(scrummy)

#set(CMAKE_CXX_FLAGS "-static")

message("READ THE README!")
list(APPEND
  CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake"
)

set(Boost_USE_STATIC_LIBS "ON")
find_package(X11 REQUIRED COMPONENTS Xinerama Xft Xext X11 ICE)
find_package(Boost REQUIRED COMPONENTS filesystem system iostreams)
find_package(FLTK REQUIRED)
find_package(CURLpp REQUIRED)
find_package(FontConfig REQUIRED)
find_package(Poco REQUIRED COMPONENTS Zip Foundation)
#find_package

add_definitions("-I.." "-I.")
list(APPEND
  BUILTCOMPS
  "scrumcomps.cc" "drupalauth.cc" "unzip.cc" "scrummer2.cc"
)

list(APPEND
  X11_LIBRARIES
  ${X11_Xft_LIB} ${X11_Xext_LIB} ${X11_Xinerama_LIB}
)

#find_library(POCO_FOUNDATION NAMES libPocoFoundation.a HINTS "/usr/local/lib")
#find_library(POCO_ZIP NAMES libPocoZip.a HINTS "/usr/local/lib")

#add_library("SCRUMS" SHARED ${BUILTCOMPS})
add_library("SCRUMA" STATIC ${BUILTCOMPS})

#set_target_properties("SCRUMS"
#  PROPERTIES
#  SUFFIX ".so"
#  PREFIX "lib"
#  OUTPUT_NAME "scrummy"
#)

add_custom_target(incerbincer SOURCES "scrummer2.hh")

set_target_properties("SCRUMA"
  PROPERTIES
  SUFFIX ".a"
  PREFIX "lib"
  OUTPUT_NAME "scrummy"
)


set(CMAKE_LINK_FLAGS "-L.")
add_executable("scrummer" "scrummer.cc")
#target_link_libraries("scrummer" "SCRUMS" "fltk" "Xft" "ICE" "Xext" "X11" "boost_filesystem" "boost_system" "boost_iostreams" "curlpp" "Xinerama")
#target_link_libraries("scrummer" "SCRUMA" ${CURLPP_LIBRARIES} ${Boost_LIBRARIES} ${X11_LIBRARIES} ${FLTK_LIBRARIES} ${FONTCONFIG_LIBRARIES} "PocoFoundation" "PocoZip")
target_link_libraries("scrummer" "SCRUMA" ${CURLPP_LIBRARIES} ${Boost_LIBRARIES} ${X11_LIBRARIES} ${FLTK_LIBRARIES} ${FONTCONFIG_LIBRARIES} ${Poco_LIBRARIES})
