CC=gcc
LD=gcc

SRCS =main.c $(wildcard Litecv/Core/*.c)
OBJS =$(patsubst %c,%o,$(SRCS))
TARGET=./Litecv/bin/licv
INCLUDE=-I ./Litecv/inc/Core_inc
CFLAGS =-lm
.PHONY: all clean
all:$(TARGET)

$(TARGET) :$(OBJS)
	$(LD)  -o $@ $^ $(INCLUDE) $(CFLAGS)
%.o:%.c
	$(CC) $(INCLUDE) -c $< -o $@

clean :
	rm -f $(OBJS) $(TARGET) 
