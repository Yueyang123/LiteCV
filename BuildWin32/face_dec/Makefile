CXX=g++
LD=g++

SRCS =./face_dec.cpp
OBJS =$(patsubst %cpp,%o,$(SRCS))
TARGET=face_dec
INCLUDE=-I E:/WORKPLACE/LiteCV/Litecv/inc/Core
INCLUDE+=-I E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/seetaface_win_install/include
LIB+=E:/WORKPLACE/LiteCV/BuildWin32/Litecv/liblicvcore.a
LIB+=E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/jpeg_win_install/lib/libjpeg.a
LIB+=E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/png_win_install/lib/libpng.a
LIB+=E:/WORKPLACE/LiteCV/Litecv/3rd/win_3rd_lib/zlib_win_install/lib/libz.a
SEETLIB+=-L E:/WORKPLACE/LiteCV/BuildWin32/face_dec/bin/ -lSeetaFaceDetector -lSeetaFaceLandmarker -lSeetaFaceRecognizer


.PHONY: all clean
all:$(TARGET)

$(TARGET) :$(OBJS)
	$(LD)  $^  $(INCLUDE) $(SEETLIB) -o $@  $(LIB)
%.o:%.cpp
	$(CXX) $(INCLUDE) $(SEETLIB) -c $< -o $@ 

clean :
	rm -f $(OBJS) $(TARGET) 
