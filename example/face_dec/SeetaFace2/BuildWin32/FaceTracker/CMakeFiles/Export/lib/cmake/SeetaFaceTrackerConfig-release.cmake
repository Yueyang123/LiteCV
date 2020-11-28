#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SeetaFace::SeetaFaceTracker" for configuration "Release"
set_property(TARGET SeetaFace::SeetaFaceTracker APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SeetaFace::SeetaFaceTracker PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libSeetaFaceTracker.dll.a"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "SeetaFace::SeetaFaceDetector"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libSeetaFaceTracker.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS SeetaFace::SeetaFaceTracker )
list(APPEND _IMPORT_CHECK_FILES_FOR_SeetaFace::SeetaFaceTracker "${_IMPORT_PREFIX}/lib/libSeetaFaceTracker.dll.a" "${_IMPORT_PREFIX}/bin/libSeetaFaceTracker.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
