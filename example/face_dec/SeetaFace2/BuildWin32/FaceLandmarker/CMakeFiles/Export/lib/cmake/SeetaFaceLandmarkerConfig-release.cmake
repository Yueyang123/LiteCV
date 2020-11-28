#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SeetaFace::SeetaFaceLandmarker" for configuration "Release"
set_property(TARGET SeetaFace::SeetaFaceLandmarker APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SeetaFace::SeetaFaceLandmarker PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libSeetaFaceLandmarker.dll.a"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "SeetaFace::SeetaNet"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libSeetaFaceLandmarker.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS SeetaFace::SeetaFaceLandmarker )
list(APPEND _IMPORT_CHECK_FILES_FOR_SeetaFace::SeetaFaceLandmarker "${_IMPORT_PREFIX}/lib/libSeetaFaceLandmarker.dll.a" "${_IMPORT_PREFIX}/bin/libSeetaFaceLandmarker.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
