#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "camel-tools-filter" for configuration ""
set_property(TARGET camel-tools-filter APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(camel-tools-filter PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libcamel-tools-filter.so"
  IMPORTED_SONAME_NOCONFIG "libcamel-tools-filter.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS camel-tools-filter )
list(APPEND _IMPORT_CHECK_FILES_FOR_camel-tools-filter "${_IMPORT_PREFIX}/lib/libcamel-tools-filter.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
