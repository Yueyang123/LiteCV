#ifndef FB_H
#define FB_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <string>

class Painter 
{
private:
    fb_fix_screeninfo finfo;
    fb_var_screeninfo vinfo;
    char* pfb;
    int fbfd;
    unsigned int color,width,height;
public:
    Painter(char* str);
    ~Painter();
    void print_info();
    void set_color(unsigned int color);
    void Point(unsigned int x, unsigned int y,unsigned int color=0);
    void Char(unsigned short x,unsigned short y,unsigned char num,unsigned char size,unsigned int color=0);
    void Line(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2,unsigned int color=0);
    void Circle(unsigned short x0,unsigned short y0,unsigned char r,unsigned int color=0);
    void String(unsigned short x,unsigned short y,unsigned short width,unsigned short height,unsigned char size,char* str,unsigned int color=0);
    char* at(unsigned int x, unsigned int y);

};



#endif