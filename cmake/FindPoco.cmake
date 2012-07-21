# finds the PocoProject libraries

set(store_cfls ${CMAKE_FIND_LIBRARY_SUFFIXES})
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".so")

set(Poco_INCLUDE_PREFIX "Poco")
set(Poco_INCLUDE_SEARCHES "Poco.h" "Version.h" "Foundation.h")
find_path(Poco_INCLUDE_DIR NAMES ${Poco_INCLUDE_SEARCHES} PATH_SUFFIXES ${Poco_INCLUDE_PREFIX})

macro(findpocolib LIB)
  set(Poco_FIND_NAMES "libPoco${LIB}" "Poco${LIB}")
  find_library(Poco_${LIB}_LIBRARY NAMES ${Poco_FIND_NAMES} PATHS "/usr/local/lib")
  if("Poco_${LIB}_LIBRARY" STREQUAL "Poco_${LIB}_LIBRARY-NOTFOUND")
    set(Poco_${LIB}_FOUND "false")
    message(FATAL "Poco library ${LIB} Not found!")
  else()
    list(APPEND Poco_LIBRARIES ${Poco_${LIB}_LIBRARY})
  endif()
endmacro(findpocolib)

foreach(COMP ${Poco_FIND_COMPONENTS})
#  string(TOUPPER "${COMP}" UCOMP)
#  set(Poco_${UCOMP}_FOUND "TRUE")
  findpocolib(${COMP})
  list(APPEND CTF "Poco_${COMP}_LIBRARY")
endforeach()

include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(Poco DEFAULT_MSG Poco_LIBRARIES Poco_INCLUDE_DIR ${CTF})

set(CMAKE_FIND_LIBRARY_SUFFIXES "${store_cfls}")
