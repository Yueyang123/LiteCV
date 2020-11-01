/*
 * @Descripttion: 绘画测试函数
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-02 00:05:16
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "bmp.h"
#include "cv.h"
#include "li_image.h"
#include "li_painter.h"

int main()
{
     //这里的指针只可以作为左值发生改变
     //也就是说如果内存申请发生在函数里面的话
     //指针实际上上不会发生改变的
     //也就是说这里的指针等于说没有进行内存申请
     //也就是说不要指望通过函数传参的方式为指针赋值


     BYTE* ptr=NULL;
     Li_Image* out =Li_Create_Imgae(300,300,LI_DEP_24U,LI_BMP_888);
     Li_Point(out,0xFF00FF,20,20);
     Li_Circle(out,0xFF0000,100,100,30);
     Li_Line(out,0xFF00FF,20,20,60,60);
     Li_Char(out,0xFF00FF,40,40,'2',LI_FONT_12);
     Li_Char(out,0xFF00FF,40,80,'2',LI_FONT_16);
     Li_String(out,0xFFF00F,50,50,200,32,"321123",LI_FONT_32);


     Li_Save_Image("./picture/1.bmp",out);
     Li_Destroy_Image(out);

     LILOG("over");
     return 0; 
}