cmake_minimum_required(VERSION 3.2)
include_directories(
    inc/Core
    inc/Imgproc
)
aux_source_directory(Core    DIR_SRCS)
aux_source_directory(Imgproc PROC_SRCS)
SET(LICV_CORE ${DIR_SRCS})
SET(LICV_PROC ${PROC_SRCS})

#根据实际情况修改静态库的绝对路径
#linux中不需要指定库的头文件目录
if(LINUX)
    if(USE_JPEG)
    include_directories(/home/swann/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/include)
    #include_directories(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/include)
    #使用编译器自带的jpeg库
    link_libraries(/home/swann/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/lib/libjpeg.a)
    #link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/lib/libjpeg.a)
    #link_libraries(libjpeg.a )
    endif(USE_JPEG)

    if(USE_PNG)

    include_directories(/home/swann/LiteCV/Litecv/3rd/linux_3rd_lib/png_linux_install/include)
    link_libraries(/home/swann/LiteCV/Litecv/3rd/linux_3rd_lib/png_linux_install/lib/libpng16.a)
    link_libraries(/home/swann/LiteCV/Litecv/3rd/linux_3rd_lib/zlib_linux_install/lib/libz.a)

    #include_directories(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/png_arm_install/include)
    #link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/linux_3rd_lib/png_linux_install/lib/libpng.a)
    #link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/linux_3rd_lib/zlib_linux_install/lib/libz.a )
    link_libraries(  m)
    endif(USE_PNG)

elseif(WINDOWS)
    if(USE_JPEG)
    include_directories(E:/LiteCV/Litecv/3rd/win_3rd_lib/jpeg_win_install/include)
    link_libraries(E:/LiteCV/Litecv/3rd/win_3rd_lib/jpeg_win_install/lib/libjpeg.a )
    endif(USE_JPEG)
    if(USE_PNG)
    include_directories( E:/LiteCV/Litecv/3rd/win_3rd_lib/png_win_install/include)
    link_libraries(  E:/LiteCV/Litecv/3rd/win_3rd_lib/png_win_install/lib/libpng.a)
    link_libraries(  E:/LiteCV/Litecv/3rd/win_3rd_lib/zlib_win_install/lib/libz.a )
    link_libraries(  m)
    endif(USE_PNG)

elseif(ARM)
    Message(ARM)
    if(USE_JPEG)
    include_directories(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/jpeg_arm_install/include)
    #使用编译器自带的jpeg库
    link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/jpeg_arm_install/lib/libjpeg.a)
    endif(USE_JPEG)

    if(USE_PNG)
    include_directories(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/png_arm_install/include)
    link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/png_arm_install/lib/libpng.a)
    link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/zlib_arm_install/lib/libz.a)
    link_libraries(  m)
    endif(USE_PNG)

endif()


add_library(licvcore   STATIC  ${LICV_CORE})
add_library(licvimgproc STATIC  ${LICV_PROC})

