/*
 * @Descripttion: 图像卷积常见操作
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-24 21:12:04
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "bmp.h"
#include "cv.h"
#include "li_image.h"
#include "li_painter.h"
#include "li_image_proc.h"

int main()
{
     BYTE* ptr=NULL;
     Li_Image* out =Li_Load_Image("./picture/whu_rgb888.bmp",LI_BMP_888);
     Li_Image* sharp=Li_Sharp(out);//图像锐化
     Li_Image* emboss=Li_Emboss(out);//雕版
     
     Li_Image* gray=Li_Convert_Image(out,LI_BMP_888_2_LI_BMP_8);
     Li_Image* bw  =Li_Threshold(gray,127);
     Li_Image* erode=Li_Erode(gray);//图像腐蚀
     Li_Image* dilate=Li_Dilate(gray);//图像膨胀
     Li_Image* add   =Li_Add(out,out);
     Li_Image* minus =Li_Minus(out,out);
     Li_Image* grand =Li_Grandient(gray);
     Li_Image* open  =Li_Mod_Open(gray);
     Li_Image* close =Li_Mod_Close(gray);
     Li_Image* top   =Li_TopHat(gray);
     Li_Image* black =Li_BlackHat(gray);

     Li_Image* noise =Li_Salt_Noise(out,1000);//椒盐噪声
     Li_Image* med =Li_Smooth(noise,Li_MEDIUM);//中值滤波
     Li_Image* conv=Li_Smooth(noise,Li_GAUSS);//高斯滤波
     Li_Image* ave=Li_Smooth(noise,Li_AVERAGE);//均值滤波

     Li_Save_Image("conv.bmp",conv);
     Li_Save_Image("sharp.bmp",sharp);
     Li_Save_Image("emboss.bmp",emboss);   
     Li_Save_Image("erode.bmp",erode); 
     Li_Save_Image("dilate.bmp",dilate);
     Li_Save_Image("gray.bmp",gray);
     Li_Save_Image("med.bmp",med); 
     Li_Save_Image("ave.bmp",ave); 
     Li_Save_Image("noise.bmp",noise);
     Li_Save_Image("add.bmp",add);
     Li_Save_Image("minus.bmp",minus);
     Li_Save_Image("grand.bmp",grand);
     Li_Save_Image("open.bmp",open);
     Li_Save_Image("close.bmp",close);
     Li_Save_Image("top.bmp",top);
     Li_Save_Image("black.bmp",black);
     LILOG("over");
     return 0; 
}

 