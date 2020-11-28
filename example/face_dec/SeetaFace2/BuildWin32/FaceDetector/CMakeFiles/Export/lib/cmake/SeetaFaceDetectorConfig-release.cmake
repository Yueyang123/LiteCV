#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SeetaFace::SeetaFaceDetector" for configuration "Release"
set_property(TARGET SeetaFace::SeetaFaceDetector APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SeetaFace::SeetaFaceDetector PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libSeetaFaceDetector.dll.a"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "SeetaFace::SeetaNet"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libSeetaFaceDetector.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS SeetaFace::SeetaFaceDetector )
list(APPEND _IMPORT_CHECK_FILES_FOR_SeetaFace::SeetaFaceDetector "${_IMPORT_PREFIX}/lib/libSeetaFaceDetector.dll.a" "${_IMPORT_PREFIX}/bin/libSeetaFaceDetector.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
