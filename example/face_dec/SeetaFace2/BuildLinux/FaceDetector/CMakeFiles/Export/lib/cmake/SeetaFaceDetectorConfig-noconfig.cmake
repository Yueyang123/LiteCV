#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SeetaFace::SeetaFaceDetector" for configuration ""
set_property(TARGET SeetaFace::SeetaFaceDetector APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(SeetaFace::SeetaFaceDetector PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "SeetaFace::SeetaNet"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libSeetaFaceDetector.so.v2.5.5"
  IMPORTED_SONAME_NOCONFIG "libSeetaFaceDetector.so.v2.5.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS SeetaFace::SeetaFaceDetector )
list(APPEND _IMPORT_CHECK_FILES_FOR_SeetaFace::SeetaFaceDetector "${_IMPORT_PREFIX}/lib/libSeetaFaceDetector.so.v2.5.5" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
