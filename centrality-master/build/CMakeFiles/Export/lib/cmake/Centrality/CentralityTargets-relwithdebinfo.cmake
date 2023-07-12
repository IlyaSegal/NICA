#----------------------------------------------------------------
# Generated CMake target import file for configuration "RELWITHDEBINFO".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Centrality" for configuration "RELWITHDEBINFO"
set_property(TARGET Centrality APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Centrality PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libCentrality.so.1.0"
  IMPORTED_SONAME_RELWITHDEBINFO "libCentrality.so.1.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS Centrality )
list(APPEND _IMPORT_CHECK_FILES_FOR_Centrality "${_IMPORT_PREFIX}/lib/libCentrality.so.1.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
