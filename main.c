/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-02 17:44:11
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
     Li_Image* img= Li_Create_Imgae(300,300,LI_DEP_32U,LI_PNG);
     Li_Char(img, 0xFF00FF,200,200,'4',32);
     BYTE* ptr =img->at( img,100,100);
     *ptr++=0xFF;
     *ptr++=0x00;
     *ptr++=0xFF;
     Li_Save_Image("1.png",img);

     LILOG("over");
     return 0; 
}

 