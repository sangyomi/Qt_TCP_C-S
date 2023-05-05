#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "camel-tools-optimizer" for configuration ""
set_property(TARGET camel-tools-optimizer APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(camel-tools-optimizer PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libcamel-tools-optimizer.so"
  IMPORTED_SONAME_NOCONFIG "libcamel-tools-optimizer.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS camel-tools-optimizer )
list(APPEND _IMPORT_CHECK_FILES_FOR_camel-tools-optimizer "${_IMPORT_PREFIX}/lib/libcamel-tools-optimizer.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)