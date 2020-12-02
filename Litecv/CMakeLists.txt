cmake_minimum_required(VERSION 3.2)
include_directories(
    inc/Core
    inc/Imgproc
    inc/QRdec
)
FILE(GLOB DIR_SRCS  "Core/li_image.c")
FILE(GLOB PROC_SRCS "Imgproc/li_image_proc.c")


SET(LICV_CORE ${DIR_SRCS})
SET(LICV_PROC ${PROC_SRCS})


#根据实际情况修改静态库的绝对路径
#linux中不需要指定库的头文件目录
if(LINUX)
    if(USE_JPEG)
    include_directories(/home/swann/SDK/X86/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/include)
    link_libraries(/home/swann/SDK/X86/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/lib/libjpeg.a)
    endif(USE_JPEG)

    if(USE_PNG)
    include_directories(/home/swann/SDK/X86/LiteCV/Litecv/3rd/linux_3rd_lib/png_linux_install/include/libpng16)
    link_libraries(/home/swann/SDK/X86/LiteCV/Litecv/3rd/linux_3rd_lib/png_linux_install/lib/libpng16.a)
    link_libraries(/home/swann/SDK/X86/LiteCV/Litecv/3rd/linux_3rd_lib/zlib_linux_install/lib/libz.a)
    endif(USE_PNG)

    if(USE_QR)
    include_directories(/home/swann/SDK/X86/LiteCV/Litecv/3rd/linux_3rd_lib/qr_linux_install/include)
    link_libraries(/home/swann/SDK/X86/LiteCV/Litecv/3rd/linux_3rd_lib/qr_linux_install/lib/libqrencode.a)
    endif(USE_QR)


elseif(WINDOWS)
    if(USE_JPEG)
    include_directories(E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/jpeg_win_install/include)
    link_libraries(E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/jpeg_win_install/lib/libjpeg.a )
    endif(USE_JPEG)
    if(USE_PNG)
    include_directories( E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/png_win_install/include)
    link_libraries(  E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/png_win_install/lib/libpng.a)
    link_libraries(  E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/zlib_win_install/lib/libz.a )
    endif(USE_PNG)
    if(USE_QR)
    include_directories(E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/qr_win_install/include)
    link_libraries(E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/qr_win_install/lib/libqrencode.a)
    #include_directories(E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/quirc_win_install/include)
    #link_libraries(E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/quirc_win_install/lib/libquirc.a)
    endif(USE_QR)
elseif(ARM)
    Message(ARM)
    if(USE_JPEG)
    include_directories(/home/swann/SDK/X86/LiteCV/Litecv/3rd/arm_3rd_build/jpeg_arm_install/include)
    link_libraries(/home/swann/SDK/X86/LiteCV/Litecv/3rd/arm_3rd_build/jpeg_arm_install/lib/libjpeg.a)
    endif(USE_JPEG)

    if(USE_PNG)
    include_directories(/home/swann/SDK/X86/LiteCV/Litecv/3rd/arm_3rd_build/png_arm_install/include)
    link_libraries(/home/swann/SDK/X86/LiteCV/Litecv/3rd/arm_3rd_build/png_arm_install/lib/libpng.a)
    link_libraries(/home/swann/SDK/X86/LiteCV/Litecv/3rd/arm_3rd_build/zlib_arm_install/lib/libz.a)
    endif(USE_PNG)

    if(USE_QR)
    include_directories(/home/swann/SDK/X86/LiteCV/Litecv/3rd/arm_3rd_build/qr_linux_install/include)
    link_libraries(/home/swann/SDK/X86/LiteCV/Litecv/3rd/arm_3rd_build/qr_linux_install/lib/libqrencode.a)
    endif(USE_QR)
endif()


link_libraries(m)
add_library(licvcore   STATIC  ${LICV_CORE})
add_library(licvimgproc STATIC  ${LICV_PROC})

if(USE_QR)
    FILE(GLOB QR_SRCS "QRdec/li_qrcode.c")
    SET(LICV_QR ${QR_SRCS})
    add_library(licvqr STATIC  ${LICV_QR})
endif(USE_QR)