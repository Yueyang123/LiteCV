/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-03 00:33:52
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
     BYTE* ptr=NULL;
     Li_Image* out =Li_Load_Image("./picture/whu_rgb888.bmp",LI_BMP_888);
     BYTE* data=li_malloc_arr(2*out->width*out->height);
     Li_CvtColor(out->data,data,out->width,out->height,LI_BGR2YUYV);
     FILE* fd=fopen("2.yuv","wb");
     fwrite(data,2,out->width*out->height,fd);
     Li_CvtColor(data,out->data,out->width,out->height,LI_YUYV2BGR);
     Li_Save_Image("1.bmp",out);

     Li_Image* out1 =Li_Load_Image("./picture/whu_png.png",LI_PNG);
     Li_Save_Image("3.png",out1);

     Li_Image* out2 =Li_Load_Image("./picture/whu_jpg.jpg",LI_JPEG);
     Li_Save_Image("3.jpg",out1);

     LILOG("over");
     return 0; 
}

 