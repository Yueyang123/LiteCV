/*
 * @Descripttion: 图像卷积常见操作
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-12 01:03:44
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
     Li_Image* out =Li_Load_Image("./picture/lena.bmp",LI_BMP_888);
     Li_Image* sharp=Li_Sharp(out);//图像锐化
     Li_Image* emboss=Li_Emboss(out);//雕版

     Li_Image* noise =Li_Salt_Noise(out,1000);//椒盐噪声
     Li_Image* med =Li_Smooth(noise,Li_MEDIUM);//中值滤波
     Li_Image* conv=Li_Smooth(noise,Li_GAUSS);//高斯滤波
     Li_Image* ave=Li_Smooth(noise,Li_AVERAGE);//均值滤波
     Li_Save_Image("conv.jpg",conv);
     Li_Save_Image("sharp.jpg",sharp);
     Li_Save_Image("emboss.jpg",emboss);   
     Li_Save_Image("med.jpg",med); 
     Li_Save_Image("ave.jpg",ave); 
     Li_Save_Image("noise.jpg",noise);
     LILOG("over");
     return 0; 
}

 