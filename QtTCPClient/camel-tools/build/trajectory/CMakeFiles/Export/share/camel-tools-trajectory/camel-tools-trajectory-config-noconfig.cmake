#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "camel-tools-trajectory" for configuration ""
set_property(TARGET camel-tools-trajectory APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(camel-tools-trajectory PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libcamel-tools-trajectory.so"
  IMPORTED_SONAME_NOCONFIG "libcamel-tools-trajectory.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS camel-tools-trajectory )
list(APPEND _IMPORT_CHECK_FILES_FOR_camel-tools-trajectory "${_IMPORT_PREFIX}/lib/libcamel-tools-trajectory.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
