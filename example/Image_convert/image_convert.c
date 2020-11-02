/*
 * @Descripttion: 图片格式转换
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-02 16:28:57
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
     //Li_Image* out1 =Li_Convert_Image(out,LI_BMP_888_2_LI_BMP_8);
     Li_Image* out2 =Li_Convert_Image(out,LI_BMP_888_2_LI_BMP32);
     //Li_Save_Image("./picture/1.bmp",out1);
     Li_Save_Image("./picture/3.bmp",out2);
     Li_Image* img1 =Li_Convert_Image(out,LI_BMP_2_JPEG);
     Li_Save_Image("./picture/3.jpg",img1);

     Li_Image* out3 =Li_Load_Image("./picture/whu_gray.bmp",LI_BMP_8);
     Li_Image* out4 =Li_Convert_Image(out3,LI_BMP_8_2_LI_BMP_888);
     Li_Save_Image("./picture/2.bmp",out4);

     Li_Image* out5 =Li_Load_Image("./picture/whu_jpg.jpg",LI_JPEG);
     Li_Image* out6 =Li_Convert_Image(out5,LI_JPEG_2_BMP);
     Li_Save_Image("./picture/5.bmp",out6);

     Li_Image* out9 =Li_Load_Image("./picture/whu_png.png",LI_PNG);
     Li_Image* out10 =Li_Convert_Image(out9,LI_PNG_2_BMP);
     Li_Save_Image("./picture/6.bmp",out10);

     Li_Image* out7 =Li_Load_Image("./picture/whu_rgba.bmp",LI_BMP_32);
     Li_Image* out8 =Li_Convert_Image(out7,LI_BMP_32_2_LI_BMP888);
     Li_Save_Image("./picture/4.bmp",out8);
     Li_Image* img2 =Li_Convert_Image(out7,LI_BMP_2_PNG);
     Li_Save_Image("./picture/3.png",img2);

     BYTE* data=li_malloc_arr(2*out->width*out->height);
     Li_CvtColor(out->data,data,out->width,out->height,LI_BGR2YUYV);
     FILE* fd=fopen("2.yuv","wr");
     fwrite(data,2,out->width*out->height,fd);
     Li_CvtColor(data,out->data,out->width,out->height,LI_YUYV2BGR);
     Li_Save_Image("1.bmp",out);

     LILOG("over");
     return 0; 
}

 