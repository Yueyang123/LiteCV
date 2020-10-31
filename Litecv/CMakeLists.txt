cmake_minimum_required(VERSION 3.2)
include_directories(
    inc/Core_inc
)
aux_source_directory(Core DIR_SRCS)
SET(LICV_CORE
${DIR_SRCS}
)

#根据实际情况修改静态库的绝对路径
if(LINUX)
    if(USE_JPEG)
    include_directories(/home/swann/X86/opencv/Litecv/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/include)
    link_libraries(  /home/swann/X86/opencv/Litecv/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/lib/libjpeg.a )
    endif(USE_JPEG)

    if(USE_PNG)
    include_directories(/home/swann/X86/opencv/Litecv/Litecv/3rd/linux_3rd_lib/png_linux_install/include)
    link_libraries(  /home/swann/X86/opencv/Litecv/Litecv/3rd/linux_3rd_lib/png_linux_install/lib/libpng.a)
    link_libraries(  /home/swann/X86/opencv/Litecv/Litecv/3rd/linux_3rd_lib/zlib_linux_install/lib/libz.a )
    link_libraries(  m)
    endif(USE_PNG)

elseif(WINDOWS)
    if(USE_JPEG)
    include_directories( E:/WORKPLACE/Litecv/LiteCV/Litecv/3rd/win_3rd_lib/jpeg_win_install/include)
    link_libraries(  E:/WORKPLACE/Litecv/LiteCV/Litecv/3rd/win_3rd_lib/jpeg_win_install/lib/libjpeg.a )
    endif(USE_JPEG)

    if(USE_PNG)
    include_directories( E:/WORKPLACE/Litecv/LiteCV/Litecv/3rd/win_3rd_lib/png_win_install/include)
    link_libraries(  E:/WORKPLACE/Litecv/LiteCV/Litecv/3rd/win_3rd_lib/png_win_install/lib/libpng.a)
    link_libraries(  E:/WORKPLACE/Litecv/LiteCV/Litecv/3rd/win_3rd_lib/zlib_win_install/lib/libz.a )
    link_libraries(  m)
    endif(USE_PNG)
endif()


add_library(licvcore STATIC  ${LICV_CORE})

