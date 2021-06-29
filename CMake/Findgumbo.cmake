#Try to find the debug
find_library(
    GUMBO_LIBRARY_DEBUG
    NAMES
      gumbo
    HINTS
      ${CMAKE_SOURCE_DIR}/lib/installed/x64-windows
    PATH_SUFFIXES
      debug/lib
)
message(${GUMBO_LIBRARY_DEBUG})

#Try to find the release lib
find_library(
    GUMBO_LIBRARY_RELEASE
    NAMES
    gumbo
  HINTS
    ${CMAKE_SOURCE_DIR}/lib/installed/x64-windows
  PATH_SUFFIXES
    lib
)

find_path(GUMBO_INCLUDE_DIR
  NAMES
    gumbo.h
  HINTS
  ${CMAKE_SOURCE_DIR}/lib/installed/x64-windows
  PATH_SUFFIXES
    include
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(gumbo DEFAULT_MSG
GUMBO_LIBRARY_RELEASE
  GUMBO_INCLUDE_DIR)

mark_as_advanced(GUMBO_LIBRARY_RELEASE GUMBO_INCLUDE_DIR)

if(GUMBO_LIBRARY_RELEASE AND NOT TARGET gumbo::gumbo)
  add_library(gumbo::gumbo SHARED IMPORTED)
  set_target_properties(
    gumbo::gumbo
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${GUMBO_INCLUDE_DIR}"
      IMPORTED_LOCATION ${GUMBO_LIBRARY_RELEASE}
      IMPORTED_IMPLIB ${GUMBO_LIBRARY_RELEASE}
      IMPORTED_LOCATION_DEBUG ${GUMBO_LIBRARY_DEBUG}
      IMPORTED_IMPLIB_DEBUG ${GUMBO_LIBRARY_DEBUG}
      )
endif()