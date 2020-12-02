CXX=g++
LD=g++

SRCS =./face_dec.cpp
OBJS =$(patsubst %cpp,%o,$(SRCS))
TARGET=face_dec
INCLUDE=-I /home/swann/SDK/X86/LiteCV/Litecv/inc/Core
INCLUDE+=-I /home/swann/SDK/X86/LiteCV/BuildLinux/face_dec/include
LIB+=/home/swann/SDK/X86/LiteCV/BuildLinux/Litecv/liblicvcore.a
LIB+=/home/swann/SDK/X86/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/lib/libjpeg.a
LIB+=/home/swann/SDK/X86/LiteCV/Litecv/3rd/linux_3rd_lib/png_linux_install/lib/libpng.a
LIB+=/home/swann/SDK/X86/LiteCV/Litecv/3rd/linux_3rd_lib/zlib_linux_install/lib/libz.a
SEETLIB+=-L /home/swann/SDK/X86/LiteCV/BuildLinux/face_dec/bin -lSeetaFaceDetector -lSeetaFaceLandmarker -lSeetaFaceRecognizer


.PHONY: all clean
all:$(TARGET)

$(TARGET) :$(OBJS)
	$(LD)  $^  $(INCLUDE) $(SEETLIB) -std=c++11 -o $@  $(LIB)
%.o:%.cpp
	$(CXX) $(INCLUDE) $(SEETLIB) -std=c++11 -c $< -o $@

clean :
	rm -f $(OBJS) $(TARGET) 
