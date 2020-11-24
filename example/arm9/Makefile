CXX=arm-none-linux-gnueabi-g++
LD=arm-none-linux-gnueabi-g++

SRCS =./fb/fb.cpp display.cpp
OBJS =$(patsubst %cpp,%o,$(SRCS))
TARGET=display
INCLUDE=-I /home/swann/IMX_283A/Qt/App/LiteCV/Litecv/inc/Core
INCLUDE+=-I ./fb
INCLUDE+=-I /home/swann/SDK/X86/LiteCV/Litecv/inc/Core
INCLUDE+=-I /home/swann/SDK/X86/LiteCV/Litecv/inc/Imgproc
LIB+= /home/swann/SDK/X86/LiteCV/BuildARM/Litecv/liblicvcore.a
LIB+=/home/swann/SDK/X86/LiteCV/Litecv/3rd/arm_3rd_build/jpeg_arm_install/lib/libjpeg.a
LIB+=/home/swann/SDK/X86/LiteCV/Litecv/3rd/arm_3rd_build/png_arm_install/lib/libpng.a
LIB+=/home/swann/SDK/X86/LiteCV/Litecv/3rd/arm_3rd_build/zlib_arm_install/lib/libz.a

.PHONY: all clean
all:$(TARGET)

$(TARGET) :$(OBJS)
	$(LD)  $^  $(INCLUDE)  -o $@  $(LIB)
%.o:%.cpp
	$(CXX) $(INCLUDE) -c $< -o $@ 

clean :
	rm -f $(OBJS) $(TARGET) 
