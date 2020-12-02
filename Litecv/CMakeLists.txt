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

if(USE_JPEG)
    include_directories(${JPEG_LIB_DIR}/include)
    link_libraries(${JPEG_LIB_DIR}/lib/libjpeg.a )
endif(USE_JPEG)

if(USE_PNG)
    include_directories(${PNG_LIB_DIR}/include)
    link_libraries(${PNG_LIB_DIR}/lib/libpng.a)
    link_libraries(${ZLIB_LIB_DIR}/lib/libz.a )
endif(USE_PNG)

if(USE_QR)
    include_directories(${QR_LIB_DIR}/include)
    link_libraries(${QR_LIB_DIR}/lib/libqrencode.a)
endif(USE_QR)


link_libraries(m)
add_library(licvcore   STATIC  ${LICV_CORE})
add_library(licvimgproc STATIC  ${LICV_PROC})
if(USE_QR)
    FILE(GLOB QR_SRCS "QRdec/li_qrcode.c")
    SET(LICV_QR ${QR_SRCS})
    add_library(licvqr STATIC  ${LICV_QR})
endif(USE_QR)