/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-02 15:48:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "bmp.h"
#include "cv.h"
#include "li_image.h"
#include "li_painter.h"
	// *y = YMap[2][r]+YMap[1][g]+YMap[0][b];
	// *u = UMap[2][r]+UMap[1][g]+UMap[0][b];
	// *v = VMap[2][r]+VMap[1][g]+VMap[0][b];
int main()
{
     //这里的指针只可以作为左值发生改变
     //也就是说如果内存申请发生在函数里面的话
     //指针实际上上不会发生改变的
     //也就是说这里的指针等于说没有进行内存申请
     //也就是说不要指望通过函数传参的方式为指针赋值


     BYTE* ptr=NULL;
     Li_Image* out =Li_Load_Image("./picture/whu_rgb888.bmp",LI_BMP_888);
     BYTE* data=li_malloc_arr(2*out->width*out->height);
     Li_CvtColor(out->data,data,out->width,out->height,LI_BGR2YUYV);
     FILE* fd=fopen("2.yuv","wr");
     fwrite(data,2,out->width*out->height,fd);


     Li_CvtColor(data,out->data,out->width,out->height,LI_YUYV2BGR);
     Li_Save_Image("1.bmp",out);
     
     LILOG("over");
     return 0; 
}

 