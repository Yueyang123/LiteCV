CXX=arm-none-linux-gnueabi-g++
LD=arm-none-linux-gnueabi-g++

SRCS =fb.cpp display.cpp
OBJS =$(patsubst %cpp,%o,$(SRCS))
TARGET=fb
INCLUDE=-I /home/swann/IMX_283A/Qt/App/LiteCV/Litecv/inc/Core
INCLUDE+=-I ./

.PHONY: all clean
all:$(TARGET)

$(TARGET) :$(OBJS)
	$(LD)  $^  $(INCLUDE)  -o $@  /home/swann/IMX_283A/Qt/App/LiteCV/arm_build/Litecv/liblicvcore.a 
%.o:%.cpp
	$(CXX) $(INCLUDE) -c $< -o $@

clean :
	rm -f $(OBJS) $(TARGET) 
