cmake_minimum_required(VERSION 3.2)
include_directories(
    inc/Core_inc
)
aux_source_directory(Core DIR_SRCS)
SET(LICV_CORE
${DIR_SRCS}
)

if(LINUX)
    message(STATUS “LINUX_X86”)
    if(USE_JPEG)
    message(STATUS “LINK_JPEG”)
    link_directories("3rd/linux_3rd_lib/jpeg_liunx_install/lib")
    endif(USE_JPEG)
    if(USE_PNG)
    message(STATUS “LINK_PNG”)
    link_directories("3rd/linux_3rd_lib/png_liunx_install/lib")
    link_directories("3rd/linux_3rd_lib/zlib_liunx_install/lib")
    endif(USE_PNG)
elseif(WINDOWS)
    message(STATUS “WIN_X86”)
    if(USE_JPEG)
    message(STATUS “LINK_JPEG”)
    link_directories("3rd/win_3rd_lib/jpeg_win_install/lib")
    endif(USE_JPEG)
    if(USE_PNG)
    message(STATUS “LINK_PNG”)
    link_directories("3rd/win_3rd_lib/png_win_install/lib")
    link_directories("3rd/win_3rd_lib/zlib_win_install/lib")
    endif(USE_PNG)
endif()

add_library(licvcore STATIC  ${LICV_CORE})

if(USE_JPEG)
target_link_libraries( licvcore libjpeg.a )
endif(USE_JPEG)

if(USE_PNG)
target_link_libraries( licvcore libpng16.a)
target_link_libraries( licvcore libz.a )
target_link_libraries( licvcore m)
endif(USE_PNG)