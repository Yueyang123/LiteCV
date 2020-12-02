cmake_minimum_required(VERSION 3.2)
project(LICV)
include_directories (Litecv/inc/Core)
include_directories (Litecv/inc/Imgproc)
include_directories (Litecv/inc/QRdec)
aux_source_directory(./ DIR_MAIN)
set(LICV_MAIN ${DIR_MAIN})

#添加编译选项
add_compile_options(-std=c99)

set (ARM_GCC_STR
      "Enable this if you want to CrossCompile" )
set (USE_JPEG_STR
      "Enable this if you want to USE JPEG" )
set (USE_PNG_STR
      "Enable this if you want to USE PNG" )
set (BUILD_EXAMPLE_STR
      "Enable this if you want to BUILD EXAMPLE" )
set (USE_QR_STR
      "Enable this if you want to BUILD QR EXAMPLE" )


#如果想要交叉编译开启这个
option(ARM ${ARM_GCC_STR} OFF)
option(USE_JPEG ${USE_JPEG_STR} ON)
option(USE_PNG ${USE_PNG_STR} ON)
option(BUILD_EXAMPLE ${BUILD_EXAMPLE_STR} ON)
option(USE_QR ${USE_QR_STR} ON)

if(USE_JPEG)
    message(USE JPEG)
    set(JPEG_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Litecv/3rd/win_3rd_lib/jpeg_win_install" CACHE STRING "Prefix to add jpeg")
endif(USE_JPEG)
if(USE_PNG)
    message(USE PNG)
    set(PNG_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Litecv/3rd/win_3rd_lib/png_win_install" CACHE STRING "Prefix to add png")
    set(ZLIB_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Litecv/3rd/win_3rd_lib/zlib_win_install" CACHE STRING "Prefix to add zlib")
endif(USE_PNG)
if(USE_QR)
    message(USE QR)
    set(QR_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Litecv/3rd/win_3rd_lib/qr_win_install" CACHE STRING "Prefix to add qr")
endif(USE_QR)

if(BUILD_EXAMPLE)
message(BUILD EXAMPLE)
endif(BUILD_EXAMPLE)


#确定编译平台
if(ARM)
   message(ARM)
else()
    if (CMAKE_HOST_WIN32)
        message(WINDOWS)
        set(WINDOWS ON)
    elseif (CMAKE_HOST_APPLE)
        message(APPLE)
        set(MACOS   ON)
    elseif (CMAKE_HOST_UNIX)
        message(LINUX)
        set(LINUX   ON)
    endif ()
endif()

add_subdirectory(Litecv)


#如果想要编译示例
if(BUILD_EXAMPLE)

aux_source_directory(./example/basicio DIR_EXP01)
set(LICV_EXP01 ${DIR_EXP01})
aux_source_directory(./example/painter DIR_EXP02)
set(LICV_EXP02 ${DIR_EXP02})
aux_source_directory(./example/conv   DIR_EXP04)
set(LICV_EXP04 ${DIR_EXP04})
aux_source_directory(./example/canny   DIR_EXP05)
set(LICV_EXP05 ${DIR_EXP05})
aux_source_directory(./example/Hist   DIR_EXP06)
set(LICV_EXP06 ${DIR_EXP06})
aux_source_directory(./example/QR   DIR_EXP07)
set(LICV_EXP07 ${DIR_EXP07})

add_executable(${PROJECT_NAME} ${LICV_MAIN})
target_link_libraries(${PROJECT_NAME} licvcore)
target_link_libraries(${PROJECT_NAME} licvimgproc)

add_executable(IO ${LICV_EXP01})
target_link_libraries(IO licvcore)

#绘图测试
add_executable(Painter ${LICV_EXP02})
target_link_libraries(Painter licvcore)

#常见卷积测试
add_executable(conv ${LICV_EXP04})
target_link_libraries(conv licvcore)
target_link_libraries(conv licvimgproc)

#边缘检测测试
add_executable(canny ${LICV_EXP05})
target_link_libraries(canny licvcore)
target_link_libraries(canny licvimgproc)

#灰度直方图测试
add_executable(Hist ${LICV_EXP06})
target_link_libraries(Hist licvcore)
target_link_libraries(Hist licvimgproc)

if(USE_QR)
add_executable(QR ${LICV_EXP07})
target_link_libraries(QR licvcore)
target_link_libraries(QR licvimgproc)
target_link_libraries(QR licvqr)
endif(USE_QR)

endif(BUILD_EXAMPLE)
