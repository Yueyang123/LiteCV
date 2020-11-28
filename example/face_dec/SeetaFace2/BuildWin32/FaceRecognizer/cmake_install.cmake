# Install script for directory: E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/FaceRecognizer

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/BuildWin32/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/MinGW/bin/objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seeta" TYPE FILE FILES "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/BuildWin32/FaceRecognizer/SeetaRecognizerExport.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/BuildWin32/lib/libSeetaFaceRecognizer.dll.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/BuildWin32/bin/libSeetaFaceRecognizer.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSeetaFaceRecognizer.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSeetaFaceRecognizer.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/MinGW/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSeetaFaceRecognizer.dll")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seeta" TYPE FILE FILES
    "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/FaceRecognizer/include/seeta/CStream.h"
    "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/FaceRecognizer/include/seeta/CStruct.h"
    "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/FaceRecognizer/include/seeta/FaceDatabase.h"
    "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/FaceRecognizer/include/seeta/FaceRecognizer.h"
    "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/FaceRecognizer/include/seeta/Stream.h"
    "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/FaceRecognizer/include/seeta/Struct.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SeetaFaceRecognizerConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SeetaFaceRecognizerConfig.cmake"
         "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/BuildWin32/FaceRecognizer/CMakeFiles/Export/lib/cmake/SeetaFaceRecognizerConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SeetaFaceRecognizerConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SeetaFaceRecognizerConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/BuildWin32/FaceRecognizer/CMakeFiles/Export/lib/cmake/SeetaFaceRecognizerConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/BuildWin32/FaceRecognizer/CMakeFiles/Export/lib/cmake/SeetaFaceRecognizerConfig-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/BuildWin32/SeetaFaceRecognizerConfigVersion.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "E:/WORKPLACE/LiteCV/Litecv/3rd/src/SeetaFace2/BuildWin32/SeetaFaceRecognizer.pc")
endif()

