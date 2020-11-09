/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 01:42:33
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
     Li_Image* out =Li_Load_Image("./picture/whu_rgba.bmp",LI_BMP_32);
     double data[9]={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
     Li_Kernel* kernel=Li_GetKernel(data,3);
     Li_Image* conv= Li_Convolute(out,kernel);
     Li_Save_Image("conv.bmp",conv);
     LILOG("over");
     return 0; 
}

 